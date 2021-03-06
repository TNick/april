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

//! @cond internal

#define	_LG2_(t1,t2)	APRDBG2(APRDBG_W,t1,t2)
#define	_LG3_(t1,t2,t3)	APRDBG3(APRDBG_W,t1,t2,t3)
#define	_LG_(t)		APRDBG(APRDBG_FA,t)
#define	FUNC_ENTRY	APRDBG_FUNC(APRDBG_FA)
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
Actor *				ActorFactory::create			( ID id )
{ FUNC_ENTRY;
	if ( world() == NULL )
		return NULL;
	if ( default_dna_.isValid() == false )
	{
		DNA::InitData	idata;
		idata.kind_ = id;
		idata.cost_ = 1;
		idata.age_= 100;
		idata.energy_= 100;
		initDNA( idata );
	}
	else
	{
		if ( default_dna_.kind() != id )
			return NULL;
	}
	Actor * ret = new Actor( world() );
	setDNA( ret );
	if ( ret->decodeDNA() == false )
	{
		DEC_REF(ret,ret);
		world()->remActor( ret );
		ret = NULL;
	}
	return ret;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool				ActorFactory::addMyself			( ID id )
{ FUNC_ENTRY;
	Q_ASSERT( id != InvalidId );
	return world()->addActorFactory( this, id );
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void				ActorFactory::setDNA			( 
	Actor * a, const DNA & dna )
{ FUNC_ENTRY;
	Q_ASSERT( a != NULL );
	a->setDNA( dna );
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void				ActorFactory::initDNA			( 
	DNA & dna, const DNA::InitData & init )
{ FUNC_ENTRY;
	dna.initDNA( init );
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool				ActorFactory::save				( QSettings & stg ) const
{ FUNC_ENTRY;
	bool b = true;
	stg.beginGroup( "april-ActorFactory" );
	
	for (;;)	{
		b = b & Factory::save( stg );
		if ( !b ) break;
		
		if ( default_dna_.isValid() )
		{
			b = b & default_dna_.save( stg );
			if ( !b ) break;
		}
		
		break;
	}
	stg.endGroup();
	
	return b;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool				ActorFactory::load				( QSettings & stg )
{ FUNC_ENTRY;
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
