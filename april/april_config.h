/* ========================================================================= */
/* ------------------------------------------------------------------------- */
/*!
  \file			april_config.h
  \date			November 2012
  \author		TNick

  \brief		Contains definitions for configuring the package

*//*

 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Please read COPYING and README files in root folder
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
#ifndef __APRIL_CONFIG_INC__
#define __APRIL_CONFIG_INC__
//
//
//
//
/*  INCLUDES    ------------------------------------------------------------ */


/*  INCLUDES    ============================================================ */
//
//
//
//
/*  DEFINITIONS    --------------------------------------------------------- */

#ifdef	QT_NO_DEBUG
/*
*	filters what messages are send to debug output; to disable all messages use
*/
#define	IS_DEBUG_ID_ALLOWED( id ) ( false )

#else
/*
*	or use the ENABLE_LOGGING macro below.
*/
#define IS_DEBUG_ID_ALLOWED( id )	(	\
	true \
)
#endif

/*
*	We may define ENABLE_LOGGING here with either 0 or 1 to override the
*	default logging behaviour from april_debug.h
*
*	#define ENABLE_LOGGING		0
*	#define ENABLE_LOGGING		1
*/

/*
*	Define BB_MEMTRACK to track memory usage. If this constant is not defined
*	the components are complet6ly removed from output.
*
*	#define	BB_MEMTRACK			1
*	#undef	BB_MEMTRACK
*/



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
#endif // __APRIL_CONFIG_INC__
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
