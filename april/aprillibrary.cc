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
#include	<QSettings>

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
	: QObject(parent), MemTrack()
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


#ifdef	APRIL_SIGNALS

#endif	/* APRIL_SIGNALS */

/*  CLASS    =============================================================== */
//
//
//
//
/* ------------------------------------------------------------------------- */
/* ========================================================================= */


