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

#define RAND_0_1		( ((qreal)qrand()) / RAND_MAX )
#define RAND_ARROUND_1	( RAND_0_1 + 0.5 )
#define RAND_ARROUND_0	( RAND_0_1 - 0.5 )
#define SMALL_RANDOM	( RAND_ARROUND_0 / 100000 )


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
