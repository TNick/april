/* ========================================================================= */
/* ------------------------------------------------------------------------- */
/*!
  \file			aaoutput.h
  \date			Apr 2013
  \author		TNick

  \brief		Contains the definition for AaOutput class


*//*


 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Please read COPYING and README files in root folder
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
#ifndef __AAOUTPUT_INC__
#define __AAOUTPUT_INC__
//
//
//
//
/*  INCLUDES    ------------------------------------------------------------ */

#include    <april/april.h>

/*  INCLUDES    ============================================================ */
//
//
//
//
/*  DEFINITIONS    --------------------------------------------------------- */

namespace   april    {

/*  DEFINITIONS    ========================================================= */
//
//
//
//
/*  CLASS    --------------------------------------------------------------- */

/**
*	@brief	Manages the output in abstracta application
*/
class AaOutput		: public MemTrack		{
	BBM_TRACK( AaOutput );

	//
	//
	//
	//
	/*  DEFINITIONS    ----------------------------------------------------- */

	/*  DEFINITIONS    ===================================================== */
	//
	//
	//
	//
	/*  DATA    ------------------------------------------------------------ */

private:


	/*  DATA    ============================================================ */
	//
	//
	//
	//
	/*  FUNCTIONS    ------------------------------------------------------- */

public:

	//! present an informative message
	static void				showInfo			( const QString & s_msg );

	//! present an warning message
	static void				showWarning			( const QString & s_msg );

	//! present an error message
	static void				showError			( const QString & s_msg );

	//! present an informative message
	static void				showInfo			( 
			const QString &			s_title,
			const QString &			s_msg
			);

	//! present an warning message
	static void				showWarning			( 
			const QString &			s_title,
			const QString &			s_msg
			);

	//! present an error message
	static void				showError			( 
			const QString &			s_title,
			const QString &			s_msg
			);
	
	
	//! present a table
	static void				showTable			(
			const QList<QStringList> &	table,
			bool						has_header
			);

	/*  FUNCTIONS    ======================================================= */
	//
	//
	//
	//

};	/*	class AaOutput	*/

/*  CLASS    =============================================================== */
//
//
//
//

}   //  namespace   april

#endif // __AAOUTPUT_INC__
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
