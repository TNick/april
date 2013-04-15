/* ========================================================================= */
/* ------------------------------------------------------------------------- */
/*!
  \file			aoutput.h
  \date			Apr 2013
  \author		TNick
  
  \brief		Contains the definition for AOutput class
  
  
*//*


 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Please read COPYING and README files in root folder
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
#ifndef __AMODOUTPUT_INC__
#define __AMODOUTPUT_INC__
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
class
	APRILSHARED_EXPORT
	AOutput		: public MemTrack		{
	BBM_TRACK( AOutput );
	
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
	
	//! the prompt
	std::string				prompt_string;

	
	
	//! the one and only instance
	static AOutput *		uniq_;
	
	/*  DATA    ============================================================ */
	//
	//
	//
	//
	/*  FUNCTIONS    ------------------------------------------------------- */
	
public:
	
	//! initialise the output system
	static bool				init				( void );
	
	//! terminate the output system
	static void				end					( void );
	
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
			bool						has_header,
			bool						row_index = true
			);
	
	
	//! change the prompt
	static void				setPrompt			(
			const QString &			s_new_prompt	
			);
	
	//! show the prompt
	static void				showPrompt			( void );
	
	
	/*  FUNCTIONS    ======================================================= */
	//
	//
	//
	//
	
};	/*	class AOutput	*/

/*  CLASS    =============================================================== */
//
//
//
//

}   //  namespace   april

#endif // __AMODOUTPUT_INC__
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
