/* ========================================================================= */
/* ------------------------------------------------------------------------- */
/*!
  \file			reflexfactory.cc
  \date			Apr 2013
  \author		TNick

  \brief		Contains the implementation of ReflexFactory class


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

#include	"reflex.h"
#include	"reflexfactory.h"
#include	"world.h"
#include	<QSettings>

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
#define	_LG_(t)		APRDBG(APRDBG_FR,t)
#define	FUNC_ENTRY	APRDBG_FUNC(APRDBG_FR)
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
ReflexFactory::ReflexFactory	( World * w )
	: Factory( w )
{
	APRDBG_CDTOR;
	/* stub */
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
ReflexFactory::~ReflexFactory	( void )
{
	APRDBG_CDTOR;
	/* stub */
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
Reflex *			ReflexFactory::create				( Actor * ag, ID id )
{
	Q_UNUSED( id );
	if ( world() == NULL )
		return NULL;
	
	Reflex * ret = new Reflex( ag, 1, 10 );
	return ret;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool				ReflexFactory::addMyself			( ID id )
{ FUNC_ENTRY;
	Q_ASSERT( id != InvalidId );
	return world()->addReflexFactory( this, id );
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool				ReflexFactory::save				( QSettings & stg ) const
{ FUNC_ENTRY;
	bool b = true;
	stg.beginGroup( "april-ReflexFactory" );
	
	for (;;)	{
		b = b & Factory::save( stg );
		if ( !b ) break;
		
		break;
	}
	stg.endGroup();
	
	return b;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool				ReflexFactory::load				( QSettings & stg )
{ FUNC_ENTRY;
	bool b = true;
	stg.beginGroup( "april-ReflexFactory" );
	
	for (;;)	{
		b = b & Factory::load( stg );
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
