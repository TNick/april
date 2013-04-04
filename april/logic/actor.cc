/* ========================================================================= */
/* ------------------------------------------------------------------------- */
/*!
  \file			actor.cc
  \date			Apr 2013
  \author		TNick

  \brief		Contains the implementation of Actor class


*//*


 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Please read COPYING and README files in root folder
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
//
//
//
//
/*  INCLUDES    ------------------------------------------------------------ */

#include	"actor.h"
#include	"world.h"
#include	"sensor.h"
#include	"actuator.h"
#include	"reflex.h"
#include	"brain.h"

/*  INCLUDES    ============================================================ */
//
//
//
//
/*  DEFINITIONS    --------------------------------------------------------- */

using namespace april;

/*  DEFINITIONS    ========================================================= */
//
//
//
//
/*  DATA    ---------------------------------------------------------------- */

/*  DATA    ================================================================ */
//
//
//
//
/*  CLASS    --------------------------------------------------------------- */

/* ------------------------------------------------------------------------- */
Actor::Actor	( World * w )
	: Component(),
	world_( w ),
	sensors_(),
	actuators_(),
	reflexes_(),
	brains_(),
	dna_(),
	kind_(InvalidId),
	birth_(0),
	death_(0),
	age_(0),
	energy_(0),
	cost_(0),
	alive_(false)
{
	APRDBG_CDTOR;
	Q_ASSERT( w != NULL );
	
	w->addActor( this );
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
Actor::~Actor	( void )
{
	APRDBG_CDTOR;
	
	Sensor * itr_sens = firstSensor_(this);
	Sensor * itr_sens_n;
	while ( itr_sens != NULL )
	{
		itr_sens_n = nextSensor_(itr_sens);
		DEC_REF(itr_sens,this);
		itr_sens = itr_sens_n;
	}
	
	Actuator * itr_act = firstActuator_(this);
	Actuator * itr_act_n;
	while ( itr_act != NULL )
	{
		itr_act_n = nextActuator_(itr_act);
		DEC_REF(itr_act,this);
		itr_act = itr_act_n;
	}
	
	Reflex * itr_refl = firstReflex_(this);
	Reflex * itr_refl_n;
	while ( itr_refl != NULL )
	{
		itr_refl_n = nextReflex_(itr_refl);
		DEC_REF(itr_refl,this);
		itr_refl = itr_refl_n;
	}
	
	Brain * itr_brn = firstBrain_(this);
	Brain * itr_brn_n;
	while ( itr_brn != NULL )
	{
		itr_brn_n = nextBrain_(itr_brn);
		DEC_REF(itr_brn,this);
		itr_brn = itr_brn_n;
	}
	
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
Sensor *		Actor::firstSensor				( void ) const
{
	return firstSensor_(this);
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
Actuator *		Actor::firstActuator			( void ) const
{
	return firstActuator_(this);
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
Reflex *		Actor::firstReflex				( void ) const
{
	return firstReflex_(this);
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
Brain *			Actor::firstBrain				( void ) const
{
	return firstBrain_(this);
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
QString			Actor::kindName					( void ) const
{
	return world_->nameForId( kind_ );
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool			Actor::decodeDNA				( void )
{
	/* cache some values */
	kind_ = dna_.kind();
	cost_ = dna_.cost();
	
	Brain * itr_brain;
	foreach( ID itr, dna_.brains() )
	{
		itr_brain = world()->createBrain( this, itr );
		if ( itr_brain == NULL )
			return false;
		OWN_CREF(itr_brain,this);
	}
	
	Actuator * itr_act;
	foreach( ID itr, dna_.actuators() )
	{
		itr_act = world()->createActuator( this, itr );
		if ( itr_act == NULL )
			return false;
		OWN_CREF(itr_act,this);
	}
	
	Sensor * itr_sens;
	foreach( ID itr, dna_.sensors() )
	{
		itr_sens = world()->createSensor( this, itr );
		if ( itr_sens == NULL )
			return false;
		OWN_CREF(itr_sens,this);
	}
	
	Reflex * itr_refl;
	foreach( ID itr, dna_.reflexes() )
	{
		itr_refl = world()->createReflex( this, itr );
		if ( itr_refl == NULL )
			return false;
		OWN_CREF(itr_refl,this);
	}
	
	return true;
}
/* ========================================================================= */


/* ------------------------------------------------------------------------- */
bool				Actor::addActuator				( Actuator * itm )
{
	if ( actuators_.contains( itm ) )
		return false;
	INC_REF( itm, this );
	actuators_.prepend( itm );
	itm->inserted();
	return true;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool				Actor::addSensor				( Sensor * itm )
{
	if ( sensors_.contains( itm ) )
		return false;
	INC_REF( itm, this );
	sensors_.prepend( itm );
	itm->inserted();
	return true;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool				Actor::addReflex				( Reflex * itm )
{
	if ( reflexes_.contains( itm ) )
		return false;
	INC_REF( itm, this );
	reflexes_.prepend( itm );
	itm->inserted();
	return true;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool				Actor::addBrain					( Brain * itm )
{
	if ( brains_.contains( itm ) )
		return false;
	INC_REF( itm, this );
	brains_.prepend( itm );
	itm->inserted();
	return true;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void				Actor::doSteps					( int steps )
{
	if ( isAlive() == false )
		return;

	/* check if this is it */
	age_ += steps;
	if ( dies() )
	{
		world_->actorDies( this );
		return;
	}
	
	/* do we have energy to live another time unit? */
	if ( energy_ < cost_ )
	{
		world_->actorDies( this );
		return;
	}
	energy_ -= cost_;
	
	/* allow components to do their thing */
	Sensor * itr_sens = firstSensor_(this);
	while ( itr_sens != NULL )
	{
		Q_ASSERT( itr_sens->isValid() );
		itr_sens->doSteps( steps );
		itr_sens = nextSensor_(itr_sens);
	}
	
	Reflex * itr_refl = firstReflex_(this);
	while ( itr_refl != NULL )
	{
		Q_ASSERT( itr_refl->isValid() );
		itr_refl->doSteps( steps );
		itr_refl = nextReflex_(itr_refl);
	}
	
	Brain * itr_brn = firstBrain_(this);
	while ( itr_brn != NULL )
	{
		Q_ASSERT( itr_brn->isValid() );
		itr_brn->doSteps( steps );
		itr_brn = nextBrain_(itr_brn);
	}
	
	Actuator * itr_act = firstActuator_(this);
	while ( itr_act != NULL )
	{
		Q_ASSERT( itr_act->isValid() );
		itr_act->doSteps( steps );
		itr_act = nextActuator_(itr_act);
	}
	
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void				Actor::makeAlive				( void )
{
	if ( alive_ )
		return;
	
	alive_ = true;
	
	cost_ = dna_.cost();
	birth_ = world_->time_;
	quint64 age = dna_.age();
	if ( age == 0 )
		age = 100;
	death_ = birth_ + dna_.age() + RANDINT_0_MAX( age * 16 / 256 );
	age_ = 0;
	
	Sensor * itr_sens = firstSensor_(this);
	while ( itr_sens != NULL )
	{
		cost_ += itr_sens->cost();
		itr_sens = nextSensor_(itr_sens);
	}
	
	Reflex * itr_refl = firstReflex_(this);
	while ( itr_refl != NULL )
	{
		cost_ += itr_refl->cost();
		itr_refl = nextReflex_(itr_refl);
	}
	
	Brain * itr_brn = firstBrain_(this);
	while ( itr_brn != NULL )
	{
		cost_ += itr_brn->cost();
		itr_brn = nextBrain_(itr_brn);
	}
	
	Actuator * itr_act = firstActuator_(this);
	while ( itr_act != NULL )
	{
		cost_ += itr_act->cost();
		itr_act = nextActuator_(itr_act);
	}
	
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
quint64				Actor::totalEnergy				( void )
{
	quint64 ret = energy_;
	Sensor * itr_sens = firstSensor_(this);
	while ( itr_sens != NULL )
	{
		ret += itr_sens->energy();
		itr_sens = nextSensor_(itr_sens);
	}
	
	Reflex * itr_refl = firstReflex_(this);
	while ( itr_refl != NULL )
	{
		ret += itr_refl->energy();
		itr_refl = nextReflex_(itr_refl);
	}
	
	Brain * itr_brn = firstBrain_(this);
	while ( itr_brn != NULL )
	{
		ret += itr_brn->energy();
		itr_brn = nextBrain_(itr_brn);
	}
	
	Actuator * itr_act = firstActuator_(this);
	while ( itr_act != NULL )
	{
		ret += itr_act->energy();
		itr_act = nextActuator_(itr_act);
	}
	return ret;
}
/* ========================================================================= */


/*  CLASS    =============================================================== */
//
//
//
//
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
