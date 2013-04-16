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
#include	"worldfactory.h"
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
#include	<QFile>

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
#define	_LG_(t)			APRDBG(APRDBG_W,t)
#define	FUNC_ENTRY		APRDBG_FUNC(APRDBG_W)
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
World::World	( const QString & name, quint64 tot_energ )
	: Component(),
	  b_running_( false ),
	  s_name_(name),
	  s_file_(),
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
#include <QDir>
/* ------------------------------------------------------------------------- */
World *			World::fromStg			( 
		const QString & s_file, QString & s_err )
{ FUNC_ENTRY;
	
	QFile f( s_file );
	QDir d( s_file );
	
	if ( ( f.exists() == false ) || d.exists() )
	{
		s_err = QObject::tr( "Can't load the world. The file does not exists." );
		return NULL;
	}
	QSettings	stg( s_file, QSettings::IniFormat );
	World * w = fromStg( stg );	
	if (  w != NULL )
	{
		w->setAssociatedFile( s_file );
	}
	return w;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
World *			World::fromStg			( QSettings & stg )
{ FUNC_ENTRY;
	stg.beginGroup( "april-World" );
	QString factory_name = stg.value( "factory_name" ).toString();
	_LG2_("  factory: ",factory_name);
	Factory * f = AprilLibrary::factoryForString( NULL, factory_name );
	WorldFactory * wf;
	if ( f == NULL )
	{
		stg.endGroup();
		_LG_("  could not find factory");
		return NULL;
	}
	else if ( f->factoryType() != FTyWorld )
	{
		DEC_REF(f,f);
		stg.endGroup();
		_LG_("  Wrong kind of factory");
		return NULL;
	}
	stg.endGroup();
	wf = static_cast<WorldFactory*>(f);
	World * world = wf->create( stg );
	DEC_REF(f,f);
	
	return world;
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
	/// @cond internal
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
	/// @endcond
	
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
{ FUNC_ENTRY;
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
Actor *				World::actorAt				( int i ) const
{
	return static_cast<Actor*>( actors_.item( i ) );
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool				World::killActor			( Actor * a )
{ FUNC_ENTRY;
	if ( a == NULL )
		return false;
	a->killMe();
	return true;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void				World::advance				( void )
{ FUNC_ENTRY;
	if  ( b_running_ == false )
		return;
	
	director_->advance();
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
QString				World::factoryName			( void ) const
{
	return AprilLibrary::defaultWorldFactoryName();
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool				World::setDirector			( Director * new_val )
{ FUNC_ENTRY;
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
{ FUNC_ENTRY;
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
{ FUNC_ENTRY;
	Q_ASSERT( actors_.contains( act ) == true );
	energy_free_ += act->totalEnergy();
	actors_.remove( act );
	DEC_REF( act, this );
	return true;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool				World::addEventLine			( EventLine * el, ID id  )
{ FUNC_ENTRY;
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
{ FUNC_ENTRY;
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
{ FUNC_ENTRY;
	Q_ASSERT( events_.contains( ev ) == false );
	
	INC_REF( ev, this );
	events_.append( ev );
	ev->inserted();
	return true;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool				World::remEvent				( EventSource * ev )
{ FUNC_ENTRY;
	Q_ASSERT( events_.contains( ev ) == true );
	
	events_.remove( ev );
	DEC_REF( ev, this );
	return true;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool				World::addActorFactory		( ActorFactory * factory, ID id )
{ FUNC_ENTRY;
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
{ FUNC_ENTRY;
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
{ FUNC_ENTRY;
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
{ FUNC_ENTRY;
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
{ FUNC_ENTRY;
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
{ FUNC_ENTRY;
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
{ FUNC_ENTRY;
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
{ FUNC_ENTRY;
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
{ FUNC_ENTRY;
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
{ FUNC_ENTRY;
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
{ FUNC_ENTRY;
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
{ FUNC_ENTRY;
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
{ FUNC_ENTRY;
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
			quint64 e = ret->totalEnergy();
			if ( e > energy_free_ )
			{
				DEC_REF( ret, ret );
				remActor( ret ); /* was added by the constructor */
				ret = NULL;
			}
			else
			{
				energy_free_ -= e;
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
{ FUNC_ENTRY;
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
{ FUNC_ENTRY;
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
{ FUNC_ENTRY;
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
{ FUNC_ENTRY;
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
{ FUNC_ENTRY;
	
	/* get any energy left inside and transfer it to the world */
	energy_free_ += actor->energy();
	actor->setEnergy( 0 );
	
	
	/// @cond internal
	
#define harvestEnergyX(X)	           \
	X * X##_itr = actor->first##X();   \
	while ( X##_itr != NULL ) {        \
	energy_free_ += X##_itr->energy(); \
	X##_itr->setEnergy( 0 );           \
	X##_itr = next##X##_(X##_itr);     \
}
	
	/* same for all its components */
	harvestEnergyX(Sensor);
	harvestEnergyX(Actuator);
	harvestEnergyX(Reflex);
	harvestEnergyX(Brain);
	
#undef harvestEnergyX
	/// @endcond
	
	/* may decide to keep it arround */
	remActor( actor );
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
EventSource *				World::createEvent			( ID id )
{ FUNC_ENTRY;
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
{ FUNC_ENTRY;
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
{ FUNC_ENTRY;
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
{ FUNC_ENTRY;
	director_->stop();
	b_running_ = false;
}
/* ========================================================================= */

/// @cond internal
#define saveFactory(f,F)	                                          \
	stg.beginWriteArray( stringify(f) "_factories_" );				  \
	i_cnt = 0;														  \
	QMap<ID,F*>::ConstIterator itr_##f =                              \
	f##_factories_.constBegin();                                      \
	QMap<ID,F*>::ConstIterator itr_end_##f =                          \
	f##_factories_.constEnd();                                        \
	while ( itr_##f != itr_end_##f )	{                             \
	stg.setArrayIndex( i_cnt );                                       \
	stg.setValue( "factory_name", itr_##f.value()->factoryName() );   \
	stg.setValue( "factory_id", itr_##f.key() );                      \
	b = b & itr_##f.value()->save( stg );                             \
	itr_##f++;                                                        \
	i_cnt++;                                                          \
	}                                                                 \
	stg.endArray();                                                   \
	if ( !b ) { _LG_( stringify(f) " factory fails"); break; }
/// @endcond

/* ------------------------------------------------------------------------- */
bool				World::save				( QSettings & stg ) const
{ FUNC_ENTRY;
	if ( isRunning() )
		return false;
	int		i_cnt;
	bool	b = true;
	
	stg.beginGroup( "april-World" );
	stg.setValue( "factory_name", factoryName() );
	
	for (;;)	{
		
		stg.setValue( "s_name_", s_name_ );
		stg.setValue( "time_", time_ );
		stg.setValue( "energy_all_", energy_all_ );
		stg.setValue( "energy_free_", energy_free_ );
		
		b = b & uid_.save( stg );
		if ( !b ) { _LG_("  uid_ fails"); break; }
		
		saveFactory(actor,ActorFactory);
		saveFactory(actuator,ActuatorFactory);
		saveFactory(brain,BrainFactory);
		saveFactory(sensor,SensorFactory);
		saveFactory(event,EventFactory);
		saveFactory(reflex,ReflexFactory);
		
		stg.beginWriteArray( "actors_", actors_.count() );
		i_cnt = 0;
		Actor * a = firstActor_(this);
		while ( a != NULL )
		{
			stg.setArrayIndex( i_cnt );
			b = b & a->save( stg );
			a = nextActor_( a );
			i_cnt++;
		}
		stg.endArray();
		if ( !b ) { _LG_("  actors_ failed"); break; }
		
		stg.beginWriteArray( "events_", events_.count() );
		i_cnt = 0;
		EventSource * e = firstEvent_(this);
		while ( e != NULL )
		{
			stg.setArrayIndex( i_cnt );
			b = b & e->save( stg );
			e = nextEvent_( e );
			i_cnt++;
		}
		stg.endArray();
		if ( !b ) { _LG_("  events_ failed"); break; }
		
		stg.beginWriteArray( "event_lines_", event_lines_.count() );
		i_cnt = 0;
		QMap<ID,EventLine*>::ConstIterator itr_event_lines = event_lines_.constBegin();
		QMap<ID,EventLine*>::ConstIterator itr_end_event_lines = event_lines_.constEnd();
		while ( itr_event_lines != itr_end_event_lines )
		{
			stg.setArrayIndex( i_cnt );
			b = b & itr_event_lines.value()->save( stg );
			itr_event_lines++;
			i_cnt++;
		}
		stg.endArray();
		if ( !b ) { _LG_("  event_lines_ failed"); break; }
		
		if ( director_ != NULL )
		{
			b = b & director_->save( stg );
			_LG2_("  director: ",b);
		}
		
		b = b & Component::save( stg );
		_LG2_("  component: ",b);
		break;
	}
	
	stg.endGroup();
	return b;
	
#	undef	saveFactory
	
}
/* ========================================================================= */

/// @cond internal
#	define	loadFactory(f,F,ty)												\
	i_cnt = stg.beginReadArray( stringify(f) "_factories_" ); 				\
	for ( int i = 0; i < i_cnt; i++ ) {							            \
	stg.setArrayIndex( i );							                        \
	factory_name = stg.value( "factory_name" ).toString();					\
	id = stg.value( "factory_id" ).toULongLong( &b );						\
	if ( !b ) break;							                            \
	factory = AprilLibrary::factoryForString( this, factory_name );			\
	if ( factory == NULL ) { b = false; break; }							\
	else if ( factory->factoryType() != ty ){ DEC_REF(factory,factory); b = false; break; }	\
	F * af = static_cast<F*>(factory);										\
	add##F( af, id );														\
	DEC_REF(factory,factory);												\
	b = b & af->load( stg );												\
	}																		\
	stg.endArray();															\
	if ( !b ) { _LG_( stringify(f) " factory fails"); break; }
/// @endcond



/* ------------------------------------------------------------------------- */
bool				World::load				( QSettings & stg )
{ FUNC_ENTRY;
	bool			b = true;
	int				i_cnt;
	QString			factory_name;
	Factory *		factory;
	ID				id;
	if ( isRunning() )
		return false;
	
	
	stg.beginGroup( "april-World" );
	for(;;)		{
		b = b & Component::load( stg );
		
		s_name_ = stg.value( "s_name_" ).toString();
		time_ = stg.value( "time_" ).toULongLong( &b );
		if ( !b ) break;
		energy_all_ = stg.value( "energy_all_" ).toULongLong( &b );
		if ( !b ) break;
		energy_free_ = stg.value( "energy_free_" ).toULongLong( &b );
		if ( !b ) break;
		
		b = b & uid_.load( stg );
		if ( !b ) break;
		
		//		i_cnt = stg.beginReadArray( "actor_factories_" ); 
		//		for ( int i = 0; i < i_cnt; i++ ) {
		//			stg.setArrayIndex( i );
		//			factory_name = stg.value( "factory_name" ).toString();
		//			id = stg.value( "factory_id" ).toULongLong( &b );
		//			if ( !b ) break;
		//			f = AprilLibrary::factoryForString( this, factory_name );
		//			if ( f == NULL )
		//			{ b = false; break; }
		//			else if ( f->factoryType() != FTyActor )
		//			{ DEC_REF(f,f); b = false; break; }
		//			af = static_cast<ActorFactory*>(f);
		//			addActorFactory( af, id );
		//			DEC_REF(f,f);
		//			b = b & af->load( stg );
		//			if ( !b ) break;
		//		}
		//		stg.endArray();
		//		if ( !b ) break;
		
		loadFactory(actor,ActorFactory,FTyActor);
		loadFactory(actuator,ActuatorFactory,FTyActuator);
		loadFactory(brain,BrainFactory,FTyBrain);
		loadFactory(sensor,SensorFactory,FTySensor);
		loadFactory(event,EventFactory,FTyEvent);
		loadFactory(reflex,ReflexFactory,FTyReflex);
		
		i_cnt = stg.beginReadArray( "actors_" );
		for ( int i = 0; i < i_cnt; i++ )
		{
			stg.setArrayIndex( i );
			Actor * act = Actor::fromStg( this, stg );
			if ( act == NULL )
			{
				b = false;
				_LG2_("  actor fails: ",i);
				break;
			}
			DEC_REF(act,act);
		}
		stg.endArray();
		if ( !b ) break;
		// EventSource::fromStg()
		
		break;
	}
	stg.endGroup();
	return b;
	
#	undef	loadFactory
	
	
	for(;;)		{
		
		Actor * ret_a;
		i_cnt = stg.beginReadArray( "actors_" );
		for ( int i = 0; i < i_cnt; i++ )
		{
			stg.setArrayIndex( i );
			ret_a = Actor::fromStg( this, stg );
			if ( ret_a == NULL )
			{
				b = false;
				break;
			}
			DEC_REF(ret_a,ret_a);
		}
		stg.endArray();
		if ( !b ) break;
		
		
		EventSource * ret_es;
		i_cnt = stg.beginReadArray( "events_" );
		for ( int i = 0; i < i_cnt; i++ )
		{
			stg.setArrayIndex( i );
			ret_es = EventSource::fromStg( this, stg );
			if ( ret_es == NULL )
			{
				b = false;
				break;
			}
			DEC_REF(ret_es,ret_es);
		}
		stg.endArray();
		if ( !b ) break;
		
		
		EventLine * ret_el;
		i_cnt = stg.beginReadArray( "event_lines_" );
		for ( int i = 0; i < i_cnt; i++ )
		{
			stg.setArrayIndex( i );
			ret_el = EventLine::fromStg( this, stg );
			if ( ret_el == NULL )
			{
				b = false;
				break;
			}
			DEC_REF(ret_el,ret_el);
		}
		stg.endArray();
		if ( !b ) break;
		
		
		if ( director_ == NULL )
		{
			director_ = new Director( this );
		}
		b = b & director_->load( stg );
	}
	stg.endGroup();
	return b;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool		World::saveAsStg			( 
		const QString & s_file, QString & s_err ) const
{
	QSettings	stg( s_file, QSettings::IniFormat );
	if ( stg.isWritable() == false )
	{
		s_err = QObject::tr( "Can't write to file." );
		return false;
	}
	return save( stg );
}
/* ========================================================================= */


/// @cond internal
#define findFactory(ty,var)	\
	ty##Factory*	World::find##ty##Factory	( const QString & s_name ) {             \
	QMap<ID,ty##Factory*>::ConstIterator	itr = var.constBegin();                  \
	QMap<ID,ty##Factory*>::ConstIterator	itr_e = var.constEnd();                  \
	while ( itr != itr_e )                                                           \
{ if ( itr.value()->factoryName() == s_name ) return itr.value(); itr++; }           \
	return NULL; }

findFactory(Actor,actor_factories_)
findFactory(Actuator,actuator_factories_)
findFactory(Brain,brain_factories_)
findFactory(Sensor,sensor_factories_)
findFactory(Event,event_factories_)
findFactory(Reflex,reflex_factories_)
/// @endcond

/*  CLASS    =============================================================== */
//
//
//
//
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
