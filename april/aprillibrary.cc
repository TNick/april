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
	if ( def_world_ == NULL )
	{
		def_world_ = world;
	}
	uniq_->worlds_.prepend( world );
	INC_REF( world, this );
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
void			AprilLibrary::internalRemWorld			( World * world )
{
	if ( world->isRunning() )
	{
		world->stop();
	}
	
	if ( def_world_ == world )
	{
		if ( worlds_.count() == 1 )
			def_world_ = NULL;
		else
		{
			def_world_ = prevWorld_(world);
			if ( def_world_ == NULL )
			{
				def_world_ = nextWorld_(world);
			}
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
AprilPluginInterf *	AprilLibrary::findPlugInRel		( const QString & s )
{
	QString s_file = QDir().absoluteFilePath( s );
	return findPlugIn( s_file );
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
AprilPluginLoader *	AprilLibrary::firstPlugin		( void )
{
	return firstPlugin_( unique() );
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
	Q_UNUSED( s_name );
	return new ActorFactory(w);
}
static Factory *		factoryCreatorEventSource	(
	World * w, const QString & s_name )
{
	Q_UNUSED( s_name );
	return new EventFactory(w);
}
static Factory *		factoryCreatorSensor		(
	World * w, const QString & s_name )
{
	Q_UNUSED( s_name );
	return new SensorFactory(w);
}
static Factory *		factoryCreatorActuator		(
	World * w, const QString & s_name )
{
	Q_UNUSED( s_name );
	return new ActuatorFactory(w);
}
static Factory *		factoryCreatorReflex		(
	World * w, const QString & s_name )
{
	Q_UNUSED( s_name );
	return new ReflexFactory(w);
}
static Factory *		factoryCreatorBrain			(
	World * w, const QString & s_name )
{
	Q_UNUSED( s_name );
	return new BrainFactory(w);
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


