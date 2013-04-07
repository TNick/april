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
#include	<april/logic/world.h>
#include	<april/plugins/aprilplugininterf.h>
#include	<QSettings>
#include	<QPluginLoader>
#include	<QDir>
#include	<QDebug>

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

#ifdef	APRIL_SIGNALS

#endif	/* APRIL_SIGNALS */

/*  CLASS    =============================================================== */
//
//
//
//
/* ------------------------------------------------------------------------- */
/* ========================================================================= */


