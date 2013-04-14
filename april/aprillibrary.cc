/* ========================================================================= */
/* ------------------------------------------------------------------------- */
/*!
  \file			aprillibrary.cc
  \date			Jan 2013
  \author		TNick
  
  \brief		Contains the implementation of AprilLibrary class
  
  
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

#include	"aprillibrary.h"

#include	<libbbb/bbblibrary.h>
#include	<april/plugins/aprilplugininterf.h>
#include	<QSettings>
#include	<QPluginLoader>
#include	<QDir>
#include	<QDebug>

#include	<april/logic/world.h>
#include	<april/logic/worldfactory.h>
#include	<april/logic/actor.h>
#include	<april/logic/actorfactory.h>
#include	<april/logic/genericactorfactory.h>
#include	<april/logic/brain.h>
#include	<april/logic/brainfactory.h>
#include	<april/logic/actuator.h>
#include	<april/logic/actuatorfactory.h>
#include	<april/logic/reflex.h>
#include	<april/logic/reflexfactory.h>
#include	<april/logic/sensor.h>
#include	<april/logic/sensorfactory.h>
#include	<april/logic/eventsource.h>
#include	<april/logic/eventfactory.h>

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

AprilLibrary *	AprilLibrary::uniq_ = NULL;

static const char *	name_deffact_world = "World.Factory.Default";
static const char *	name_deffact_actor = "Actor.Factory.Default";
static const char *	name_genfact_actor = "Actor.Factory.Generic";
static const char *	name_deffact_sensor = "Sensor.Factory.Default";
static const char *	name_deffact_actuator = "Actuator.Factory.Default";
static const char *	name_deffact_brain = "Brain.Factory.Default";
static const char *	name_deffact_reflex = "Reflex.Factory.Default";
static const char *	name_deffact_event = "Event.Factory.Default";

/*  DATA    ================================================================ */
//
//
//
//
/*  CLASS    --------------------------------------------------------------- */

/* ------------------------------------------------------------------------- */
AprilLibrary::AprilLibrary	( QObject * parent )
	: QObject(parent), MemTrack(),
	  props_(),
	  worlds_(),
	  plugins_(),
	  def_world_(NULL)
{
	APRDBG_CDTOR;
	Q_ASSERT( uniq_ == NULL );
	uniq_ = this;
	
	loadProps();
	
	/* create the factory for the default World */
	WorldFactory * wf = new WorldFactory( name_deffact_world );
	DEC_REF(wf,wf);
	registerFactoryCreators();
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
AprilLibrary::~AprilLibrary	( void )
{
	APRDBG_CDTOR;
	
	AprilPluginLoader * itr = firstPlugin_(unique());
	AprilPluginLoader * itr_n;
	while ( itr != NULL )
	{
		itr_n = nextPlugin_( itr );
		AprilPluginInterf * plg = static_cast<AprilPluginInterf*>( 
					itr->instance() );
		plg->unloading();
		itr->unload();
		unique()->plugins_.remove( itr );
		itr->deleteLater();
		
		itr = itr_n;
	}
	
	World * itr_w = firstWorld_( this );
	World * itr_w_n;
	while ( itr_w != NULL )
	{
		itr_w_n = nextWorld_(itr_w);
		DEC_REF(itr_w,this);
		itr_w = itr_w_n;
	}
	
	if ( def_world_ != NULL )
	{
		DEC_REF(def_world_,this);
	}
	
	Q_ASSERT( uniq_ == this );
	uniq_ = NULL;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void		AprilLibrary::loadProps		( void )
{
	QSettings		s;
	s.beginGroup( "AprilLibrary" );
	props_.load( s );
	s.endGroup();
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void		AprilLibrary::saveProps		( void )
{
	QSettings		s;
	s.beginGroup( "AprilLibrary" );
	props_.save( s );
	s.endGroup();
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
APRILSHARED_EXPORT bool	initAprilLibrary			( void )
{
	APRDBG_FUNC(APRDBG_LIBRARY);
	if ( AprilLibrary::unique() == NULL )
	{
		initBbbLibrary();
		new AprilLibrary();
	}
	return true;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
APRILSHARED_EXPORT void	endAprilLibrary			( void )
{
	APRDBG_FUNC(APRDBG_LIBRARY);
	if ( AprilLibrary::unique() != NULL )
	{
		delete AprilLibrary::unique();
		endBbbLibrary();
	}
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void			AprilLibrary::LibProps::save			( QSettings & s )
{
	s.beginGroup( "LibProps" );
	
	s.endGroup();
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void			AprilLibrary::LibProps::load			( QSettings & s )
{
	s.beginGroup( "LibProps" );
	
	s.endGroup();
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void			AprilLibrary::addWorld					( World * world )
{
	Q_ASSERT( uniq_ != NULL );
	APRDBG_FUNC(APRDBG_LIBRARY);
	Q_ASSERT( world != NULL );
	if ( uniq_->worlds_.contains( world ) )
		return;
	uniq_->internalAddWorld( world );
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void			AprilLibrary::internalAddWorld			( World * world )
{
	APRDBG_FUNC(APRDBG_LIBRARY);
	uniq_->worlds_.prepend( world );
	INC_REF( world, this );
	if ( def_world_ == NULL )
	{
		setCrtWorld( world );
	}
	world->inserted();
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void			AprilLibrary::remWorld					( World * world )
{
	Q_ASSERT( uniq_ != NULL );
	APRDBG_FUNC(APRDBG_LIBRARY);
	if ( uniq_ == NULL )
		return;
	Q_ASSERT( world != NULL );
	if ( uniq_->worlds_.contains( world ) )
	{
		uniq_->internalRemWorld( world );
	}
	else
	{
		APRDBG2(APRDBG_LIBRARY,"The world does not exists in list ",
				(quint64)world );
	}
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
World *			AprilLibrary::firstWorld				( void )
{
	return firstWorld_(uniq_);
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
QString			AprilLibrary::uniqueWorldName			( const QString & pattern )
{
	QString s_ret;
	bool b_match;
	World * iter;
	for ( int i = 1; i < INT_MAX; i++ )
	{
		b_match = false;
		s_ret = pattern.arg( i );
		iter = firstWorld_(uniq_);
		while ( iter != NULL )
		{
			if ( iter->name() == s_ret )
			{
				b_match = true;
				break;
			}
			iter = nextWorld_(iter);
		}
		if ( b_match == false )
			break;
	}
	return s_ret;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
World *			AprilLibrary::findWorld					(
		const QString & s_name )
{
	World * iter = firstWorld_(uniq_);
	while ( iter != NULL )
	{
		if ( iter->name() == s_name )
			return iter;
		iter = nextWorld_(iter);
	}
	return NULL;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
World *			AprilLibrary::worldAt					( int i )
{
	if ( i < 0 )
		return NULL;
	World * iter = firstWorld_(uniq_);
	while ( iter != NULL )
	{
		if ( i == 0 )
			return iter;
		iter = nextWorld_(iter);
		i--;
	}
	return NULL;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool			AprilLibrary::setCrtWorld				( World * new_crt )
{
	Q_ASSERT( ( new_crt == NULL ) || uniq_->worlds_.contains( new_crt ) );
	if ( uniq_->def_world_ != NULL )
	{
		DEC_REF(uniq_->def_world_,uniq_);
	}
	uniq_->def_world_ = new_crt;
	if ( uniq_->def_world_ != NULL )
	{
		INC_REF(uniq_->def_world_,uniq_);
	}
	return true;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void			AprilLibrary::internalRemWorld			( World * world )
{
	if ( world->isRunning() )
	{
		world->stop();
	}
	
	if ( def_world_ == world )
	{
		if ( worlds_.count() == 1 )
		{
			setCrtWorld( NULL );
		}
		else
		{
			World * dw = prevWorld_(world);
			if ( dw == NULL )
			{
				dw = nextWorld_(world);
			}
			setCrtWorld( dw );
		}
	}
	worlds_.remove( world );
	DEC_REF( world, this );
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool			AprilLibrary::hasWorld						( World * world )
{
	Q_ASSERT( uniq_ != NULL );
	return uniq_->worlds_.contains( world );
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
AprilPluginInterf *	AprilLibrary::loadPlugIn		( const QString & s )
{
	QString s_file = QDir().absoluteFilePath( s );
	AprilPluginInterf * ret = findPlugIn( s_file );
	if ( ret  != NULL )
	{
		return ret;
	}
	AprilPluginLoader * ldr = new AprilPluginLoader( s_file );
	ret = static_cast<AprilPluginInterf*>( ldr->instance() );
	if ( ( ret == NULL ) || ( ret->initialised() == false ) )
	{
		qDebug() << ldr->errorString();
		ldr->deleteLater();
		return NULL;
	}
	
	unique()->plugins_.prepend( ldr );
	return ret;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool				AprilLibrary::unloadPlugIn		( const QString & s )
{
	QString s_file = QDir().absoluteFilePath( s );
	AprilPluginLoader * itr = firstPlugin_(unique());
	while ( itr != NULL )
	{
		if ( QString::compare( itr->fileName(), s_file, Qt::CaseInsensitive ) == 0 )
		{
			AprilPluginInterf * plg = static_cast<AprilPluginInterf*>(
						itr->instance() );
			plg->unloading();
			itr->unload();
			unique()->plugins_.remove( itr );
			itr->deleteLater();
			return true;
		}
		itr = nextPlugin_( itr );
	}
	return false;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool				AprilLibrary::unloadPlugIn		( AprilPluginLoader * pld )
{
	if ( unique()->plugins_.contains( pld ) == false )
		return false;
		
	AprilPluginInterf * plg = static_cast<AprilPluginInterf*>( 
				pld->instance() );
	if ( plg != NULL )
	{
		plg->unloading();		
	}
	
	pld->unload();
	unique()->plugins_.remove( pld );
	pld->deleteLater();
	return true;	
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool				AprilLibrary::unloadPlugIn		( AprilPluginInterf * p )
{
	AprilPluginLoader * itr = firstPlugin_(unique());
	while ( itr != NULL )
	{
		AprilPluginInterf * plg = static_cast<AprilPluginInterf*>( 
					itr->instance() );
		if ( plg == p )
		{
			plg->unloading();
			itr->unload();
			unique()->plugins_.remove( itr );
			itr->deleteLater();
			return true;
		}
		itr = nextPlugin_( itr );
	}
	return false;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
AprilPluginInterf *	AprilLibrary::findPlugIn		( const QString & s )
{
	AprilPluginLoader * itr = firstPlugin_(unique());
	while ( itr != NULL )
	{
		if ( QString::compare( itr->fileName(), s, Qt::CaseInsensitive ) == 0 )
		{
			return static_cast<AprilPluginInterf*>( itr->instance() );
		}
		itr = nextPlugin_( itr );
	}
	return NULL;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
AprilPluginLoader *	AprilLibrary::findPlugInLoader		( const QString & s )
{
	AprilPluginLoader * itr = firstPlugin_(unique());
	while ( itr != NULL )
	{
		if ( QString::compare( itr->fileName(), s, Qt::CaseInsensitive ) == 0 )
		{
			return itr;
		}
		itr = nextPlugin_( itr );
	}
	return NULL;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
AprilPluginInterf *	AprilLibrary::findPlugInRel		( const QString & s )
{
	QString s_file = QDir().absoluteFilePath( s );
	return findPlugIn( s_file );
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
AprilPluginLoader *	AprilLibrary::findPlugInLoaderRel( const QString & s )
{
	QString s_file = QDir().absoluteFilePath( s );
	return findPlugInLoader( s_file );
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
AprilPluginLoader *	AprilLibrary::firstPlugin		( void )
{
	return firstPlugin_( unique() );
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
AprilPluginLoader *	AprilLibrary::pluginAt			( int i )
{
	if ( i < 0 )
		return NULL;
	AprilPluginLoader * iter = firstPlugin_(uniq_);
	while ( iter != NULL )
	{
		if ( i == 0 )
			return iter;
		iter = nextPlugin_(iter);
		i--;
	}
	return NULL;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool				AprilLibrary::registerFactory	(
		const QString & s_name, FactoryCreator callback )
{
	if ( uniq_->factories_src_.contains( s_name ) )
	{
		return false;
	}
	uniq_->factories_src_.insert( s_name, callback );
	return true;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool				AprilLibrary::unregisterFactory	(
		const QString & s_name, FactoryCreator callback )
{
	if ( s_name.isEmpty() )
		return false;
	QMap<QString,FactoryCreator>::Iterator itr = uniq_->factories_src_.find( s_name );
	if ( itr == uniq_->factories_src_.end() )
	{
		return false;
	}
	if ( itr.value() != callback )
	{
		return false;
	}
	uniq_->factories_src_.erase( itr );
	return true;	
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool				AprilLibrary::remWorldFactory	( 
		const QString & s, WorldFactory * inst )
{
	if ( s.isEmpty() )
		return false;
	QMap<QString,WorldFactory*>::Iterator itr = uniq_->world_factories_.find( s );
	if ( itr == uniq_->world_factories_.end() )
	{
		return false;
	}
	if ( itr.value() != inst )
	{
		return false;
	}
	uniq_->world_factories_.erase( itr );
	return true;	
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
Factory *			AprilLibrary::defaultWorldFactoryCreator	( World * w, const QString & s_name )
{
	Q_UNUSED( s_name );
	Q_UNUSED( w );
	
	/* we don't need to create one because the default factory creator is always there */
	WorldFactory * ret = uniq_->world_factories_.value( name_deffact_world );
	if ( ret == NULL )
	{
		Q_ASSERT( false );
		return NULL;
	}
	INC_REF(ret,ret);
	return ret;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool				AprilLibrary::addWorldFactory	( 
		const QString & s, WorldFactory * inst )
{
	if ( uniq_->world_factories_.contains( s ) )
	{
		return false;
	}
	INC_REF(inst,uniq_);
	uniq_->world_factories_.insert( s, inst );
	return true;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
QString				AprilLibrary::defaultWorldFactoryName		( void )
{
	return name_deffact_world;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
Factory *			AprilLibrary::factoryForString				( 
		World * w, const QString & s_name )
{
	FactoryCreator fc = uniq_->factories_src_.value( s_name );
	if ( fc == NULL )
		return NULL;
	Factory * ret = fc( w, s_name );
	return ret;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
WorldFactory *		AprilLibrary::findWorldFactory		( const QString & s )
{
	return uniq_->world_factories_.value( s );
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
static Factory *		factoryCreatorActor			(
		World * w, const QString & s_name )
{
	ActorFactory * f = w->findActorFactory( s_name );
	if ( f == NULL )
	{
		f = new ActorFactory(w);
	}
	return f;
}
static Factory *		factoryCreatorGenericActor	(
		World * w, const QString & s_name )
{
	ActorFactory * f = w->findActorFactory( s_name );
	if ( f == NULL )
	{
		f = new GenericActorFactory(w);
	}
	return f;
}
static Factory *		factoryCreatorEventSource	(
		World * w, const QString & s_name )
{
	EventFactory * f = w->findEventFactory( s_name );
	if ( f == NULL )
	{
		f = new EventFactory(w);
	}
	return f;
}
static Factory *		factoryCreatorSensor		(
		World * w, const QString & s_name )
{
	SensorFactory * f = w->findSensorFactory( s_name );
	if ( f == NULL )
	{
		f = new SensorFactory(w);
	}
	return f;
}
static Factory *		factoryCreatorActuator		(
		World * w, const QString & s_name )
{
	ActuatorFactory * f = w->findActuatorFactory( s_name );
	if ( f == NULL )
	{
		f = new ActuatorFactory(w);
	}
	return f;
}
static Factory *		factoryCreatorReflex		(
		World * w, const QString & s_name )
{
	ReflexFactory * f = w->findReflexFactory( s_name );
	if ( f == NULL )
	{
		f = new ReflexFactory(w);
	}
	return f;
}
static Factory *		factoryCreatorBrain			(
		World * w, const QString & s_name )
{
	BrainFactory * f = w->findBrainFactory( s_name );
	if ( f == NULL )
	{
		f = new BrainFactory(w);
	}
	return f;
}
void		AprilLibrary::registerFactoryCreators		( void )
{
	AprilLibrary::registerFactory( 
				name_deffact_world, 
				AprilLibrary::defaultWorldFactoryCreator );
	AprilLibrary::registerFactory( 
				name_deffact_actor, 
				factoryCreatorActor );
	AprilLibrary::registerFactory( 
				name_genfact_actor, 
				factoryCreatorGenericActor );
	AprilLibrary::registerFactory( 
				name_deffact_event, 
				factoryCreatorEventSource );
	AprilLibrary::registerFactory( 
				name_deffact_sensor, 
				factoryCreatorSensor );
	AprilLibrary::registerFactory( 
				name_deffact_actuator, 
				factoryCreatorActuator );
	AprilLibrary::registerFactory( 
				name_deffact_reflex, 
				factoryCreatorReflex );
	AprilLibrary::registerFactory( 
				name_deffact_brain, 
				factoryCreatorBrain );
}
/* ========================================================================= */

#ifdef	APRIL_SIGNALS

#endif	/* APRIL_SIGNALS */

/*  CLASS    =============================================================== */
//
//
//
//
/* ------------------------------------------------------------------------- */
/* ========================================================================= */


