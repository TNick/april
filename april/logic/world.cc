/* ========================================================================= */
/* ------------------------------------------------------------------------- */
/*!
  \file			world.cc
  \date			Apr 2013
  \author		TNick
  
  \brief		Contains the implementation of World class
  
  
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

#include	"world.h"
#include	"actor.h"
#include	"actorfactory.h"
#include	"event.h"
#include	"eventfactory.h"
#include	"actuator.h"
#include	"actuatorfactory.h"
#include	"sensor.h"
#include	"sensorfactory.h"
#include	"brain.h"
#include	"brainfactory.h"
#include	"reflex.h"
#include	"reflexfactory.h"

#include	<april/aprillibrary.h>

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
World::World	( const QString & name, quint64 tot_energ )
	: Component(),
	  b_running_( false ),
	  s_name_(name),
	  time_(0),
	  energy_all_(tot_energ),
	  energy_free_(tot_energ),
	  actors_(),
	  uid_(name),
	  actor_factories_(),
	  actuator_factories_(),
	  brain_factories_(),
	  sensor_factories_()
{
	APRDBG_CDTOR;
	
	AprilLibrary::addWorld( this );
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
World::~World	( void )
{
	APRDBG_CDTOR;
	AprilLibrary::remWorld( this );
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool				World::setTotEnergy			( quint64 new_val )
{
	if ( energy_free_ > new_val )
		return false;
	energy_all_ = new_val;
	return true;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
Actor *				World::firstActor			( void ) const
{
	return firstActor_(this);
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void				World::advance				( void )
{
	if  ( b_running_ == false )
		return;
	
	time_++;
	
	
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool				World::addActor				( Actor * act )
{
	Q_ASSERT( actors_.contains( act ) == false );
	Q_ASSERT( act != NULL );
	
	INC_REF( act, this );
	actors_.append( act );
	return true;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool				World::remActor				( Actor * act )
{
	Q_ASSERT( actors_.contains( act ) == true );
	
	actors_.remove( act );
	DEC_REF( act, this );
	return true;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
Event*				World::firstEvent			( void ) const
{
	return firstEvent_( this );
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool				World::addEvent				( Event * ev )
{
	Q_ASSERT( events_.contains( ev ) == false );
	
	events_.append( ev );
	return true;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool				World::remEvent				( Event * ev )
{
	Q_ASSERT( events_.contains( ev ) == true );
	
	events_.remove( ev );
	return true;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool				World::addActorFactory		( ActorFactory * factory, ID id )
{
	if ( factory == NULL )
		return false;
	if ( actor_factories_.contains( id ) )
		return false;
	INC_REF( factory, this );
	actor_factories_.insert( id, factory );
	return true;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool				World::addActuatorFactory	( ActuatorFactory * factory, ID id )
{
	if ( factory == NULL )
		return false;
	if ( actuator_factories_.contains( id ) )
		return false;
	INC_REF( factory, this );
	actuator_factories_.insert( id, factory );
	return true;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool				World::addSensorFactory		( SensorFactory * factory, ID id )
{
	if ( factory == NULL )
		return false;
	if ( sensor_factories_.contains( id ) )
		return false;
	INC_REF( factory, this );
	sensor_factories_.insert( id, factory );
	return true;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool				World::addBrainFactory		( BrainFactory * factory, ID id )
{
	if ( factory == NULL )
		return false;
	if ( brain_factories_.contains( id ) )
		return false;
	INC_REF( factory, this );
	brain_factories_.insert( id, factory );
	return true;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool				World::addEventFactory		( EventFactory * factory, ID id )
{
	if ( factory == NULL )
		return false;
	if ( event_factories_.contains( id ) )
		return false;
	INC_REF( factory, this );
	event_factories_.insert( id, factory );
	return true;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool				World::addReflexFactory		( ReflexFactory * factory, ID id )
{
	if ( factory == NULL )
		return false;
	if ( reflex_factories_.contains( id ) )
		return false;
	INC_REF( factory, this );
	reflex_factories_.insert( id, factory );
	return true;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool				World::remActorFactory		( ActorFactory * factory, ID id )
{
	if ( factory == NULL )
		return false;
	QMap<ID,ActorFactory*>::Iterator itr = actor_factories_.find( id );
	if ( itr == actor_factories_.end() )
	{
		return false;
	}
	if ( itr.value() != factory )
	{
		return false;
	}
	actor_factories_.erase( itr );
	return true;	
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool				World::remActuatorFactory	( ActuatorFactory * factory, ID id )
{
	if ( factory == NULL )
		return false;
	QMap<ID,ActuatorFactory*>::Iterator itr = actuator_factories_.find( id );
	if ( itr == actuator_factories_.end() )
	{
		return false;
	}
	if ( itr.value() != factory )
	{
		return false;
	}
	actuator_factories_.erase( itr );
	return true;	
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool				World::remSensorFactory		( SensorFactory * factory, ID id )
{
	if ( factory == NULL )
		return false;
	QMap<ID,SensorFactory*>::Iterator itr = sensor_factories_.find( id );
	if ( itr == sensor_factories_.end() )
	{
		return false;
	}
	if ( itr.value() != factory )
	{
		return false;
	}
	sensor_factories_.erase( itr );
	return true;	
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool				World::remBrainFactory		( BrainFactory * factory, ID id )
{
	if ( factory == NULL )
		return false;
	QMap<ID,BrainFactory*>::Iterator itr = brain_factories_.find( id );
	if ( itr == brain_factories_.end() )
	{
		return false;
	}
	if ( itr.value() != factory )
	{
		return false;
	}
	brain_factories_.erase( itr );
	return true;	
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool				World::remEventFactory		( EventFactory * factory, ID id )
{
	if ( factory == NULL )
		return false;
	QMap<ID,EventFactory*>::Iterator itr = event_factories_.find( id );
	if ( itr == event_factories_.end() )
	{
		return false;
	}
	if ( itr.value() != factory )
	{
		return false;
	}
	event_factories_.erase( itr );
	return true;	
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool				World::remReflexFactory		( ReflexFactory * factory, ID id )
{
	if ( factory == NULL )
		return false;
	QMap<ID,ReflexFactory*>::Iterator itr = reflex_factories_.find( id );
	if ( itr == reflex_factories_.end() )
	{
		return false;
	}
	if ( itr.value() != factory )
	{
		return false;
	}
	reflex_factories_.erase( itr );
	return true;	
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
Actor *				World::createActor			( ID id_kind )
{
	Actor * ret;
	QMap<ID,ActorFactory*>::Iterator itr = actor_factories_.find( id_kind );
	if ( itr == actor_factories_.end() )
	{
		return NULL;
	}
	Q_ASSERT( itr.value() != NULL );
	
	/*	create the instance; this allocates memory for
	*	an Actor and copies the default DNA inside
	*/
	ret = itr.value()->create( id_kind );
	if ( ret != NULL )
	{ /* by decoding the DNA we're creating all the componets */
		if ( ret->decodeDNA() == false )
		{ /* if the DNA can't be decoded then die at birth */
			DEC_REF( ret, ret );
			remActor( ret ); /* was added by the constructor */
			ret = NULL;
		}
		else
		{ /* we have a proper actor */
			
		}
	}
	
	return ret;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
Actuator *			World::createActuator		( Actor * actor, ID id )
{
	QMap<ID,ActuatorFactory*>::Iterator itr = actuator_factories_.find( id );
	if ( itr == actuator_factories_.end() )
	{
		return NULL;
	}
	Q_ASSERT( itr.value() != NULL );
	return itr.value()->create( actor, id );
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
Brain *				World::createBrain			( Actor * actor, ID id )
{
	QMap<ID,BrainFactory*>::Iterator itr = brain_factories_.find( id );
	if ( itr == brain_factories_.end() )
	{
		return NULL;
	}
	Q_ASSERT( itr.value() != NULL );
	return itr.value()->create( actor, id );
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
Sensor *			World::createSensor			( Actor * actor, ID id )
{
	QMap<ID,SensorFactory*>::Iterator itr = sensor_factories_.find( id );
	if ( itr == sensor_factories_.end() )
	{
		return NULL;
	}
	Q_ASSERT( itr.value() != NULL );
	return itr.value()->create( actor, id );
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
Reflex *			World::createReflex			( Actor * actor, ID id )
{
	QMap<ID,ReflexFactory*>::Iterator itr = reflex_factories_.find( id );
	if ( itr == reflex_factories_.end() )
	{
		return NULL;
	}
	Q_ASSERT( itr.value() != NULL );
	return itr.value()->create( actor, id );
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
Event *				World::createEvent			( ID id )
{
	QMap<ID,EventFactory*>::Iterator itr = event_factories_.find( id );
	if ( itr == event_factories_.end() )
	{
		return NULL;
	}
	Q_ASSERT( itr.value() != NULL );
	return itr.value()->create( id );
}
/* ========================================================================= */


/*  CLASS    =============================================================== */
//
//
//
//
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
