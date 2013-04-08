/* ========================================================================= */
/* ------------------------------------------------------------------------- */
/*!
  \file			actorfactory.cc
  \date			Apr 2013
  \author		TNick

  \brief		Contains the implementation of ActorFactory class


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

#include	"actorfactory.h"
#include	"world.h"
#include	"actor.h"

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
ActorFactory::ActorFactory	( World * w )
	: Factory( w ),
	default_dna_()
{
	APRDBG_CDTOR;
	/* stub */
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
ActorFactory::~ActorFactory	( void )
{
	APRDBG_CDTOR;
	/* stub */
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool				ActorFactory::addMyself			( ID id )
{
	Q_ASSERT( id != InvalidId );
	return world()->addActorFactory( this, id );
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void				ActorFactory::setDNA			( 
	Actor * a, const DNA & dna )
{
	Q_ASSERT( a != NULL );
	a->setDNA( dna );
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void				ActorFactory::initDNA			( 
	DNA & dna, const DNA::InitData & init )
{
	dna.initDNA( init );
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool				ActorFactory::save				( QSettings & stg ) const
{
	bool b = true;
	stg.beginGroup( "april-ActorFactory" );
	
	for (;;)	{
		b = b & Factory::save( stg );
		if ( !b ) break;
		
		b = b & default_dna_.save( stg );
		if ( !b ) break;
		
		break;
	}
	stg.endGroup();
	
	return b;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool				ActorFactory::load				( QSettings & stg )
{
	bool b = true;
	stg.beginGroup( "april-ActorFactory" );
	
	for (;;)	{
		b = b & Factory::load( stg );
		if ( !b ) break;
		
		b = b & default_dna_.load( stg );
		if ( !b ) break;
		
		break;
	}
	
	stg.endGroup();
	
	return b;
}
/* ========================================================================= */

/*  CLASS    =============================================================== */
//
//
//
//
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
