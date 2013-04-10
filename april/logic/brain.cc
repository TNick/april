/* ========================================================================= */
/* ------------------------------------------------------------------------- */
/*!
  \file			brain.cc
  \date			Apr 2013
  \author		TNick

  \brief		Contains the implementation of Brain class


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

#include	"brain.h"
#include	"actor.h"


/*  INCLUDES    ============================================================ */
//
//
//
//
/*  DEFINITIONS    --------------------------------------------------------- */

using namespace april;


#define	_LG2_(t1,t2)	APRDBG2(APRDBG_W,t1,t2)
#define	_LG3_(t1,t2,t3)	APRDBG3(APRDBG_W,t1,t2,t3)
#define	_LG_(t)		APRDBG(APRDBG_B,t)
#define	FUNC_ENTRY	APRDBG_FUNC(APRDBG_B)

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
Brain::Brain	( Actor * actor )
	: ActorComp( actor )
{
	APRDBG_CDTOR;
	actor->addBrain( this );
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
Brain::Brain	( Actor * actor, quint64 cost, quint64 energy )
	: ActorComp( actor, cost, energy )
{
	APRDBG_CDTOR;
	actor->addBrain( this );
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
Brain::~Brain	( void )
{
	APRDBG_CDTOR;
	/* stub */
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool				Brain::save				( QSettings & stg ) const
{ FUNC_ENTRY;
	bool b = true;
	stg.beginGroup( "april-Brain" );

	b = b & ActorComp::save( stg );
	
	stg.endGroup();
	return b;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool				Brain::load				( QSettings & stg )
{ FUNC_ENTRY;
	bool b = true;
	stg.beginGroup( "april-Brain" );

	b = b & ActorComp::load( stg );
	
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
