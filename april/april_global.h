/* ========================================================================= */
/* ------------------------------------------------------------------------- */
/*!
  \file			april_global.h
  \date			November 2012
  \author		TNick

  \brief		Contains definitions for april library

*//*


 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Please read COPYING and README files in root folder
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
#ifndef __APRIL_GLOBAL_HEADER_INC__
#define __APRIL_GLOBAL_HEADER_INC__
//
//
//
//
/*  INCLUDES    ------------------------------------------------------------ */

#include	<QtGlobal>
#include	<april/april_config.h>

/*  INCLUDES    ============================================================ */
//
//
//
//
/*  DEFINITIONS    --------------------------------------------------------- */

namespace   april    {

#ifndef APRIL_STANDALONE
#   if defined(APRIL_LIBRARY)
		/**
		*	@brief	let the methods take export form in dynamic library
		*/
#       define APRILSHARED_EXPORT Q_DECL_EXPORT
#   else
		/**
		*	@brief	let the methods take import form in clients
		*/
#       define APRILSHARED_EXPORT Q_DECL_IMPORT
#   endif
#else
	/**
	*	@brief	sometimes there is no special handling required
	*/
#   define APRILSHARED_EXPORT
#endif




/**
*	@brief	name of this product
*/
#define	APRIL_NAME		"april"




#ifndef ADD_PTR_INT
	/**
	*	@brief	simple pointer arithmetic is tricky in c++
	*/
#   define ADD_PTR_INT(p,i)	( ((char*)p) + i )
#endif



/**
*	@brief	We're using this redirection to keep a nice aspect of the class
*/
#ifdef	APRIL_SIGNALS
#	define		APRIL_OBJECT			Q_OBJECT
#else
#	define		APRIL_OBJECT
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

/*  FUNCTIONS    =========================================================== */
//
//
//
//

}   //  namespace   april

#endif // __APRIL_GLOBAL_HEADER_INC__
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
