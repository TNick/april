/* ========================================================================= */
/* ------------------------------------------------------------------------- */
/*!
  \file			reflex.cc
  \date			Apr 2013
  \author		TNick

  \brief		Contains the implementation of Reflex class


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
Reflex::Reflex	( Actor * actor )
	: ActorComp( actor )
{
	APRDBG_CDTOR;
	actor->addReflex( this );
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
Reflex::Reflex	( Actor * actor, quint64 cost, quint64 energy )
	: ActorComp( actor, cost, energy )
{
	APRDBG_CDTOR;
	actor->addReflex( this );
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
Reflex::~Reflex	( void )
{
	APRDBG_CDTOR;
	/* stub */
}
/* ========================================================================= */

/*  CLASS    =============================================================== */
//
//
//
//
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
