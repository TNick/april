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
#include	"actorfactory.h"
#include	"world.h"
#include	"sensor.h"
#include	"actuator.h"
#include	"reflex.h"
#include	"brain.h"
#include	"factory.h"
#include	<april/aprillibrary.h>


/*  INCLUDES    ============================================================ */
//
//
//
//
/*  DEFINITIONS    --------------------------------------------------------- */

using namespace april;

//! @cond internal

#define	_LG2_(t1,t2)	APRDBG2(APRDBG_W,t1,t2)
#define	_LG3_(t1,t2,t3)	APRDBG3(APRDBG_W,t1,t2,t3)
#define	_LG_(t)		APRDBG(APRDBG_A,t)
#define	FUNC_ENTRY	APRDBG_FUNC(APRDBG_A)

//! @endcond

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
Actor *		Actor::fromStg		( World * w, QSettings & stg )
{ FUNC_ENTRY;
	QString			factory_name;
	Factory *		f;
	ID				id;
	ActorFactory *	actor_factory;
	Actor *			actor;
	bool			b;
	
	stg.beginGroup( "april-Actor" );
	factory_name = stg.value( "factory_name" ).toString();
	id = stg.value( "factory_id" ).toULongLong( &b );
	stg.endGroup();
	if ( !b ) return NULL;
	
	f = AprilLibrary::factoryForString( w, factory_name );
	if ( f == NULL )
	{
		return NULL;
	}
	else if ( f->factoryType() != FTyActor )
	{
		DEC_REF(f,f);
		return NULL;
	}
	actor_factory = static_cast<ActorFactory*>(f);
	actor = actor_factory->create( id );
	if ( actor )
	{
		if ( actor->load( stg ) == false )
		{
			w->remActor( actor );
			DEC_REF(actor,actor);
			actor = NULL;
		}
	}
	DEC_REF(f,f);
	return actor;
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
{ FUNC_ENTRY;
	/* cache some values */
	kind_ = dna_.kind();
	cost_ = dna_.cost();
	energy_ = dna_.energy();
	
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
{ FUNC_ENTRY;
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
{ FUNC_ENTRY;
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
{ FUNC_ENTRY;
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
{ FUNC_ENTRY;
	if ( brains_.contains( itm ) )
		return false;
	INC_REF( itm, this );
	brains_.prepend( itm );
	itm->inserted();
	return true;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool				Actor::remActuator				( Actuator * act )
{ FUNC_ENTRY;
	
	if ( actuators_.contains( act ) )
		return false;
	actuators_.remove( act );
	DEC_REF( act, this );
	return true;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool				Actor::remSensor				( Sensor * sns )
{ FUNC_ENTRY;
	
	if ( sensors_.contains( sns ) )
		return false;
	sensors_.remove( sns );
	DEC_REF( sns, this );
	return true;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool				Actor::remReflex				( Reflex * r )
{ FUNC_ENTRY;
	
	if ( reflexes_.contains( r ) )
		return false;
	reflexes_.remove( r );
	DEC_REF( r, this );
	return true;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool				Actor::remBrain				( Brain * b )
{ FUNC_ENTRY;
	
	if ( brains_.contains( b ) )
		return false;
	brains_.remove( b );
	DEC_REF( b, this );
	return true;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void				Actor::doSteps					( int steps )
{ FUNC_ENTRY;
	if ( isAlive() == false )
		return;
	
	/* check if this is it */
	age_ += steps;
	if ( dies() )
	{
		killMe();
		return;
	}
	
	/* do we have energy to live another time unit? */
	if ( energy_ < cost_ )
	{
		world_->actorDies( this );
		alive_ = false;
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
{ FUNC_ENTRY;
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
quint64				Actor::totalEnergy				( void ) const
{ FUNC_ENTRY;
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

/* ------------------------------------------------------------------------- */
Sensor *			Actor::findSensor				( ID id ) const
{ FUNC_ENTRY;
	Sensor * iter = firstSensor_(this);
	while ( iter != NULL )
	{
		if  ( iter->identificator() == id )
		{
			return iter;
		}
		iter = nextSensor_(iter);
	}
	return NULL;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
Actuator *			Actor::findActuator				( ID id ) const
{ FUNC_ENTRY;
	Actuator * iter = firstActuator_(this);
	while ( iter != NULL )
	{
		if  ( iter->identificator() == id )
		{
			return iter;
		}
		iter = nextActuator_(iter);
	}
	return NULL;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
Reflex *			Actor::findReflex				( ID id ) const
{ FUNC_ENTRY;
	Reflex * iter = firstReflex_(this);
	while ( iter != NULL )
	{
		if  ( iter->identificator() == id )
		{
			return iter;
		}
		iter = nextReflex_(iter);
	}
	return NULL;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
Brain *				Actor::findBrain				( ID id ) const
{ FUNC_ENTRY;
	Brain * iter = firstBrain_(this);
	while ( iter != NULL )
	{
		if  ( iter->identificator() == id )
		{
			return iter;
		}
		iter = nextBrain_(iter);
	}
	return NULL;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool				Actor::save						( QSettings & stg ) const
{ FUNC_ENTRY;
	bool b = true;
	int i = 0;
	stg.beginGroup( "april-Actor" );
	Factory * f = factory();
	if ( f == NULL )
	{
		stg.setValue( "factory_name", QString() );
		_LG_("  no factory set for actor");
	}
	else
	{
		stg.setValue( "factory_name", f->factoryName() );
		_LG2_("  factory for actor: ", f->factoryName() );
	}
	stg.setValue( "factory_id", identificator() );
	_LG2_("  factory id: ", identificator() );
	
	for (;;)	{
		
		b = b & dna_.save( stg );
		if ( !b ) { _LG_("  dna_ fails"); break; }
		
		/// @cond internal
		
#define saveActorComp(slist,cls)								    \
	stg.beginWriteArray( stringify(slist), slist.count() );     \
	cls * itr_##cls = first##cls##_(this);                       \
	i = 0;                                                      \
	while ( itr_##cls != NULL ) {                                \
	stg.setArrayIndex( i );                                 \
	b = b & itr_##cls->save( stg );                          \
	itr_##cls = next##cls##_(itr_##cls);                      \
	i++;                                                    \
	}                                                           \
	stg.endArray();                                             \
	if ( !b ) break
		
		saveActorComp(sensors_,Sensor);
		saveActorComp(actuators_,Actuator);
		saveActorComp(reflexes_,Reflex);
		saveActorComp(brains_,Brain);
#undef	saveActorComp
		
		/// @endcond
		
		stg.setValue( "birth_", birth_ );
		stg.setValue( "death_", death_ );
		stg.setValue( "age_", age_ );
		stg.setValue( "energy_", energy_ );
		stg.setValue( "alive_", alive_ );
		// the kind is present in DNA
		// the cost is present in DNA
		
		b = b & Component::save( stg );
		_LG2_("  Component: ",b);
		
		break;
	}
	stg.endGroup();
	
	return b;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool				Actor::load						( QSettings & stg )
{ FUNC_ENTRY;
	bool b = true;
	int i_cnt;
	stg.beginGroup( "april-Actor" );
	
	for (;;)	{
		b = b & Component::load( stg );
		_LG2_("  Component: ",b);
		
		b = b & dna_.load( stg );
		if ( !b ) { _LG_("  dna_ fails"); break; }
		
		birth_ = stg.value( "birth_" ).toULongLong( &b );
		if ( !b ) { _LG_("  birth_ fails"); break; }
		death_ = stg.value( "death_" ).toULongLong( &b );
		if ( !b ) { _LG_("  death_ fails"); break; }
		age_ = stg.value( "age_" ).toULongLong( &b );
		if ( !b ) { _LG_("  age_ fails"); break; }
		energy_ = stg.value( "energy_" ).toULongLong( &b );
		if ( !b ) { _LG_("  energy_ fails"); break; }
		alive_ = stg.value( "alive_" ).toBool();
		
		kind_ = dna_.kind(); // the kind is present in DNA
		cost_ = dna_.cost(); // the cost is present in DNA
		
		/// @cond internal
		
#define loadActorComp(slist,cls)                        \
	i_cnt = stg.beginReadArray( stringify(slist) );	    \
	for ( int i = 0; i < i_cnt; i++ ) {                 \
	stg.setArrayIndex( i );                             \
	cls * act = cls::fromStg( this, stg );              \
	if ( act == NULL ) {                                \
	b = false;                                          \
	_LG2_( "  " stringify(slist) " fails: ",i);         \
	break;                                              \
	}                                                   \
	DEC_REF(act,act);                                   \
	}                                                   \
	stg.endArray();                                     \
	if ( !b ) break
		
		loadActorComp(sensors_,Sensor);
		loadActorComp(actuators_,Actuator);
		loadActorComp(reflexes_,Reflex);
		loadActorComp(brains_,Brain);
#undef	loadActorComp
		
		/// @endcond
		
		//		i_cnt = stg.beginReadArray( "sensors_" );
		//		for ( int i = 0; i < i_cnt; i++ )
		//		{
		//			stg.setArrayIndex( i );
		//			Sensor * act = Sensor::fromStg( this, stg );
		//			if ( act == NULL )
		//			{
		//				b = false;
		//				_LG2_("  sensor fails: ",i);
		//				break;
		//			}
		//			DEC_REF(act,act);
		//		}
		//		stg.endArray();
		//		if ( !b ) break;
		
		
		break;
	}
	
	stg.endGroup();
	
	return b;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
Factory *			Actor::factory				( void ) const
{
	World * w = world();
	if ( w == NULL )
	{
		return NULL;
	}
	return w->actorFactories().value( kind() );
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void				Actor::killMe				( void )
{
	world_->actorDies( this );
	alive_ = false;
}
/* ========================================================================= */

/*  CLASS    =============================================================== */
//
//
//
//
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
