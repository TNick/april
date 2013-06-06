/* ========================================================================= */
/* ------------------------------------------------------------------------- */
/*!
  \file			april_debug.cc
  \date			November 2012
  \author		TNick

  \brief		Contains definitions for debugging april package

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

#include	<april/april.h>

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

static const char * debug_names[] = {
	"CTORDTOR",
	"V_CTORDTOR",
	"LIBRARY",
	"MW",

	"Factory",
	"Actor",
	"FactActor",
	"ActorComponent",
	"Actuator",
	"FactActuator",
	"Brain",
	"FactBrain",
	"Component",
	"Director",
	"DNA",
	"DNAView",
	"EventData",
	"EventLine",
	"EventSource",
	"FactEventSrc",
	"Reflex",
	"FactReflex",
	"Sensor",
	"FactSensor",
	"World",
	"FactWorld",
	"UID",

	0
};



/*  DATA    ================================================================ */
//
//
//
//
/*  FUNCTIONS    ----------------------------------------------------------- */

APRILSHARED_EXPORT	const char *		april::debugName			( int i )
{
	Q_ASSERT( i >= APRDBG_CTORDTOR );
	Q_ASSERT( i < APRDBG_MAX );
	return debug_names[i];
}

APRILSHARED_EXPORT	bool				april::filterDebug			( int i )
{
	Q_ASSERT( i >= APRDBG_CTORDTOR );
	Q_ASSERT( i < APRDBG_MAX );
	Q_UNUSED( i );
	
	
	return false;
}

/*  FUNCTIONS    =========================================================== */
//
//
//
//
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
