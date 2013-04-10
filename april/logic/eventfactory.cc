/* ========================================================================= */
/* ------------------------------------------------------------------------- */
/*!
  \file			eventfactory.cc
  \date			Apr 2013
  \author		TNick

  \brief		Contains the implementation of EventFactory class


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

#include	"eventfactory.h"
#include	"world.h"
#include	<QSettings>

/*  INCLUDES    ============================================================ */
//
//
//
//
/*  DEFINITIONS    --------------------------------------------------------- */

using namespace april;


#define	_LG2_(t1,t2)	APRDBG2(APRDBG_W,t1,t2)
#define	_LG3_(t1,t2,t3)	APRDBG3(APRDBG_W,t1,t2,t3)
#define	_LG_(t)		APRDBG(APRDBG_FES,t)
#define	FUNC_ENTRY	APRDBG_FUNC(APRDBG_FES)

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
EventFactory::EventFactory	( World * w )
	: Factory( w )
{
	APRDBG_CDTOR;
	/* stub */
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
EventFactory::~EventFactory	( void )
{
	APRDBG_CDTOR;
	/* stub */
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool				EventFactory::addMyself			( ID id )
{ FUNC_ENTRY;
	Q_ASSERT( id != InvalidId );
	return world()->addEventFactory( this, id );
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool				EventFactory::save				( QSettings & stg ) const
{ FUNC_ENTRY;
	bool b = true;
	stg.beginGroup( "april-EventFactory" );
	
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
bool				EventFactory::load				( QSettings & stg )
{ FUNC_ENTRY;
	bool b = true;
	stg.beginGroup( "april-EventFactory" );
	
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
