/* ========================================================================= */
/* ------------------------------------------------------------------------- */
/*!
  \file			april_debug.h
  \date			November 2012
  \author		TNick

  \brief		Contains definitions for debugging bbb package

*//*


 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Please read COPYING and README files in root folder
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
#ifndef __APRIL_DEBUG_INC__
#define __APRIL_DEBUG_INC__
//
//
//
//
/*  INCLUDES    ------------------------------------------------------------ */

/* we make sure we have the user settings before this file */
#include	<april/april_global.h>
#include	<april/april_config.h>

/*  INCLUDES    ============================================================ */
//
//
//
//
/*  DEFINITIONS    --------------------------------------------------------- */


/**
*	@brief The APRDBG_Codes enum defines codes that may be used to debug the library
*
*	Each value may be used with the IS_APRIL_DEBUG_ID_ALLOWED in april_config.h to
*	enable or disable presenting messages tagged with that code.
*
*	At run time (when QT_NO_DEBUG is defined) these messages are removed
*	entierly from the output (notice the APRDBG... group of macros).
*/
enum	APRDBG_Codes		{
	APRDBG_CTORDTOR,	/* all constructors and destructors */
	APRDBG_V_CTORDTOR,	/* constructors and destructors called a lot */
	APRDBG_LIBRARY,		/* library in general */
	APRDBG_MW,			/* main window of an application */

	APRDBG_F,			/* factory */
	APRDBG_A,			/* actor */
	APRDBG_FA,			/* actor factory */
	APRDBG_ACMP,		/* actor component */
	APRDBG_AT,			/* actuator */
	APRDBG_FAT,			/* actuator factory */
	APRDBG_B,			/* brain */
	APRDBG_FB,			/* brain factory */
	APRDBG_COMP,		/* component */
	APRDBG_DIR,			/* director */
	APRDBG_DNA,			/* DNA */
	APRDBG_DNAV,		/* DNA View*/
	APRDBG_ED,			/* event data */
	APRDBG_EL,			/* event line */
	APRDBG_ES,			/* event source */
	APRDBG_FES,			/* event source factory */
	APRDBG_R,			/* reflex */
	APRDBG_FR,			/* reflex factory */
	APRDBG_S,			/* sensor */
	APRDBG_FS,			/* sensor factory */
	APRDBG_W,			/* world */
	APRDBG_FW,			/* world factory */
	APRDBG_UID,			/* unique id */

	APRDBG_MAX
};


#ifndef	ENABLE_LOGGING
#	ifndef QT_NO_DEBUG

//! logging is enabled
#		define	ENABLE_LOGGING	1

#	else

//! logging is disabled
#		define	ENABLE_LOGGING	0

#	endif
#endif

#if ENABLE_LOGGING
#	include <QDebug>

/* IS_APRIL_DEBUG_ID_ALLOWED should be defined in LIBAPRIL_config.h */
#ifndef	IS_APRIL_DEBUG_ID_ALLOWED

//! disable all IDs
#	define	IS_APRIL_DEBUG_ID_ALLOWED( id )	false

#endif

//!@{
//! macros that intermediate the logging (enabled)
#	define APRDBG(id,txt)	\
	if ( IS_APRIL_DEBUG_ID_ALLOWED( id ) ) \
	qDebug() << april::debugName(id) << ": " << txt
#	define APRDBG2(id,txt1,txt2)	\
	if ( IS_APRIL_DEBUG_ID_ALLOWED( id ) ) \
	qDebug() << april::debugName(id) << ": " << txt1 << txt2
#	define APRDBG3(id,txt1,txt2,txt3)	\
	if ( IS_APRIL_DEBUG_ID_ALLOWED( id ) ) \
	qDebug() << april::debugName(id) << ": " << txt1 << txt2 << txt3
#	define APRDBG_FUNC(id)	APRDBG(id, __func__ )
#	define APRDBG_CDTOR		APRDBG2(APRDBG_CTORDTOR, __func__, this )
//!@}


#else
//!@{
//! macros that intermediate the logging (disabled)
#	define APRDBG(id,txt)
#	define APRDBG2(id,txt1,txt2)
#	define APRDBG3(id,txt1,txt2,txt3)
#	define APRDBG_FUNC(id)
#	define APRDBG_CDTOR
//!@}
#endif





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

namespace	april	{

//! get the name for a particular debug ID
APRILSHARED_EXPORT	const char *		debugName			( int i );

//! may be used by the IS_APRIL_DEBUG_ID_ALLOWED in 
APRILSHARED_EXPORT	bool				filterDebug			( int i );

}

/*  FUNCTIONS    =========================================================== */
//
//
//
//
#endif // __APRIL_DEBUG_INC__
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
