/* ========================================================================= */
/* ------------------------------------------------------------------------- */
/*!
  \file			april.h
  \date			November 2012
  \author		TNick

  \brief		Groups all global the definitions for the package

*//*


 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Please read COPYING and README files in root folder
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
#ifndef __APRIL_MAIN_HEADER_INC__
#define __APRIL_MAIN_HEADER_INC__
//
//
//
//
/*  INCLUDES    ------------------------------------------------------------ */

#include	<april/april_config.h>
#include	<april/april_global.h>
#include	<april/april_debug.h>
#include	<april/april_version.h>
#include	<libbbb/1/memtrack.h>
#include    <libbbb/1/refcnt.h>

/*  INCLUDES    ============================================================ */
//
//
//
//
/*  DEFINITIONS    --------------------------------------------------------- */

/*

Object emit signals on certain actions if APRIL_SIGNALS is defined.

#define		LIBDIGIB_SIGNALS		1
#undef		LIBDIGIB_SIGNALS
*/

#define RAND_0_1			( ((qreal)qrand()) / RAND_MAX )
#define RAND_ARROUND_1		( RAND_0_1 + 0.5 )
#define RAND_ARROUND_0		( RAND_0_1 - 0.5 )
#define SMALL_RANDOM		( RAND_ARROUND_0 / 100000 )
#define RANDINT_0_MAX(m)	( qrand() % (m) )


#define firstSensor_(p)	static_cast<Sensor*>(p->sensors_.first())
#define prevSensor_(p)	static_cast<Sensor*>(p->prev())
#define nextSensor_(p)	static_cast<Sensor*>(p->next())

#define firstActor_(p)	static_cast<Actor*>(p->actors_.first())
#define prevActor_(p)	static_cast<Actor*>(p->prev())
#define nextActor_(p)	static_cast<Actor*>(p->next())

#define firstActuator_(p)	static_cast<Actuator*>(p->actuators_.first())
#define prevActuator_(p)	static_cast<Actuator*>(p->prev())
#define nextActuator_(p)	static_cast<Actuator*>(p->next())

#define firstReflex_(p)	static_cast<Reflex*>(p->reflexes_.first())
#define prevReflex_(p)	static_cast<Reflex*>(p->prev())
#define nextReflex_(p)	static_cast<Reflex*>(p->next())

#define firstBrain_(p)	static_cast<Brain*>(p->brains_.first())
#define prevBrain_(p)	static_cast<Brain*>(p->prev())
#define nextBrain_(p)	static_cast<Brain*>(p->next())

#define firstEvent_(p)	static_cast<Event*>(p->events_.first())
#define prevEvent_(p)	static_cast<Event*>(p->prev())
#define nextEvent_(p)	static_cast<Event*>(p->next())

#define firstWorld_(p)	static_cast<World*>(p->worlds_.first())
#define prevWorld_(p)	static_cast<World*>(p->prev())
#define nextWorld_(p)	static_cast<World*>(p->next())




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
/*  FUNCTIONS    ----------------------------------------------------------- */

/*  FUNCTIONS    =========================================================== */
//
//
//
//
#endif // __APRIL_MAIN_HEADER_INC__
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
