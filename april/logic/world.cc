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
#include	"director.h"
#include	"actor.h"
#include	"actorfactory.h"
#include	"eventsource.h"
#include	"eventfactory.h"
#include	"actuator.h"
#include	"actuatorfactory.h"
#include	"sensor.h"
#include	"sensorfactory.h"
#include	"brain.h"
#include	"brainfactory.h"
#include	"reflex.h"
#include	"reflexfactory.h"
#include	"eventline.h"

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
	  sensor_factories_(),
	  event_lines_(),
	  director_( NULL )
{
	APRDBG_CDTOR;
	
	AprilLibrary::addWorld( this );
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
World::~World	( void )
{
	APRDBG_CDTOR;
	
	Actor * a = firstActor_(this);
	Actor * a_n;
	while ( a != NULL )
	{
		a_n = nextActor_( a );
		DEC_REF( a, this );
		a = a_n;
	}
	
	EventSource * e = firstEvent_(this);
	EventSource * e_n;
	while ( e != NULL )
	{
		e_n = nextEvent_( e );
		DEC_REF( e, this );
		e = e_n;
	}
	
	/* ...... */
#	define	discardFactory(f,F) \
	QMap<ID,F*>::ConstIterator itr_##f =f##_factories_.constBegin();\
	QMap<ID,F*>::ConstIterator itr_end_##f = f##_factories_.constEnd();\
	while ( itr_##f != itr_end_##f )	{\
	DEC_REF( itr_##f.value(), this );\
	itr_##f++;\
}
	/* ...... */
	
	discardFactory(actor,ActorFactory);
	discardFactory(actuator,ActuatorFactory);
	discardFactory(brain,BrainFactory);
	discardFactory(sensor,SensorFactory);
	discardFactory(event,EventFactory);
	discardFactory(reflex,ReflexFactory);
	
#	undef	discardFactory
	
	QMap<ID,EventLine*>::ConstIterator itr_event_lines = event_lines_.constBegin();
	QMap<ID,EventLine*>::ConstIterator itr_end_event_lines = event_lines_.constEnd();
	while ( itr_event_lines != itr_end_event_lines )
	{
		DEC_REF( itr_event_lines.value(), this );
		itr_event_lines++;
	}
	
	if ( director_ != NULL )
	{
		DEC_REF( director_, this );
	}
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool				World::setTotEnergy			( quint64 new_val )
{
	if ( isRunning() )
		return false;
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
	
	director_->advance();
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool				World::setDirector			( Director * new_val )
{
	if ( isRunning() )
		return false;
	if ( director_ != NULL )
		DEC_REF(director_,this);
	
	if ( new_val != NULL )
		INC_REF(new_val,this);
	
	director_ = new_val;
	return true;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool				World::addActor				( Actor * act )
{
	Q_ASSERT( actors_.contains( act ) == false );
	Q_ASSERT( act != NULL );
	
	INC_REF( act, this );
	actors_.append( act );
	/* act->inserted(); is called by the method that inserts it */
	return true;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool				World::remActor				( Actor * act )
{
	Q_ASSERT( actors_.contains( act ) == true );
	energy_free_ += act->totalEnergy();
	actors_.remove( act );
	DEC_REF( act, this );
	return true;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool				World::addEventLine			( EventLine * el, ID id  )
{
	if ( el == NULL )
		return false;
	Q_ASSERT( event_lines_.contains( id ) == false );
	
	INC_REF( el, this );
	event_lines_.insert( id, el );
	el->inserted();
	return true;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool				World::remEventLine			( EventLine * el, ID id  )
{
	if ( el == NULL )
		return false;
	QMap<ID,EventLine*>::Iterator itr = event_lines_.find( id );
	if ( itr == event_lines_.end() )
	{
		return false;
	}
	if ( itr.value() != el )
	{
		return false;
	}
	DEC_REF( el, this );
	event_lines_.erase( itr );
	el->inserted();
	return true;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
EventSource*				World::firstEvent			( void ) const
{
	return firstEvent_( this );
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool				World::addEvent				( EventSource * ev )
{
	Q_ASSERT( events_.contains( ev ) == false );
	
	INC_REF( ev, this );
	events_.append( ev );
	ev->inserted();
	return true;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool				World::remEvent				( EventSource * ev )
{
	Q_ASSERT( events_.contains( ev ) == true );
	
	events_.remove( ev );
	DEC_REF( ev, this );
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
			quint64 e = ret->dna().energy();
			if ( e > energy_free_ )
			{
				DEC_REF( ret, ret );
				remActor( ret ); /* was added by the constructor */
				ret = NULL;
			}
			else
			{
				ret->setEnergy( e );
				ret->makeAlive();
				ret->inserted();
			}
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
void				World::actorDies			( Actor * actor )
{
	/* may decide to keep it arround */
	remActor( actor );
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
EventSource *				World::createEvent			( ID id )
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

/* ------------------------------------------------------------------------- */
bool				World::setEnergy			(
		ActorComp * comp, quint64 energy, quint64 cost )
{
	Q_ASSERT( comp != NULL );
	if ( energy_free_ < energy )
	{
		return false;
	}
	comp->setCost( cost );
	comp->setEnergy( energy );
	return true;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool				World::start			( void )
{
	if ( director_ == NULL )
	{
		director_ = new Director( this );
		OWN_CREF(director_,this);
	}
	b_running_ = director_->start();
	return b_running_;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void				World::stop				( void )
{
	director_->stop();
	b_running_ = false;
}
/* ========================================================================= */

/*  CLASS    =============================================================== */
//
//
//
//
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
