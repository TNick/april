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
		itr_refl_n = nextReflex_(itr_act);
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
	Q_ASSERT( kind_ == dna_.kind() );
	
	cost_ = dna_.cost();
	Brain * itr_brain;
	foreach( ID itr, dna_.brains() )
	{
		itr_brain = world()->createBrain( this, itr );
		if ( itr_brain == NULL )
			return false;
		brains_.prepend( itr_brain );
		OWN_CREF(itr_brain,this);
	}
	
	Actuator * itr_act;
	foreach( ID itr, dna_.actuators() )
	{
		itr_act = world()->createActuator( this, itr );
		if ( itr_act == NULL )
			return false;
		actuators_.prepend( itr_act );
		OWN_CREF(itr_act,this);
	}
	
	Sensor * itr_sens;
	foreach( ID itr, dna_.sensors() )
	{
		itr_sens = world()->createSensor( this, itr );
		if ( itr_sens == NULL )
			return false;
		sensors_.prepend( itr_sens );
		OWN_CREF(itr_sens,this);
	}
	
	Reflex * itr_refl;
	foreach( ID itr, dna_.reflexes() )
	{
		itr_refl = world()->createReflex( this, itr );
		if ( itr_refl == NULL )
			return false;
		reflexes_.prepend( itr_refl );
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
	return true;
}
/* ========================================================================= */

/*  CLASS    =============================================================== */
//
//
//
//
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
