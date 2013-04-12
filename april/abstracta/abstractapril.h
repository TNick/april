/* ========================================================================= */
/* ------------------------------------------------------------------------- */
/*!
  \file			abstractapril.h
  \date			Apr 2013
  \author		TNick

  \brief		Contains the definition for AbstractApril class


*//*


 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Please read COPYING and README files in root folder
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
#ifndef __ABSTRACTAPRIL_INC__
#define __ABSTRACTAPRIL_INC__
//
//
//
//
/*  INCLUDES    ------------------------------------------------------------ */

#include    <april/april.h>
#include    <april/abstracta/commandmap.h>

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
*	@brief	Main class for abstracta application
*/
class AbstractApril		: public MemTrack		{
	BBM_TRACK( AbstractApril );

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

	//! map of commands
	CommandMap					cmd_map;
	
	//! application exit code
	int							exit_code_;
	
	//! the one and only instance
	static AbstractApril *		uniq_;

	/*  DATA    ============================================================ */
	//
	//
	//
	//
	/*  FUNCTIONS    ------------------------------------------------------- */

private:

	//! constructor
	AbstractApril		( void );

	//! destructor;
	virtual				~AbstractApril		( void );

public:

	//! enter main loop; return program exit code
	static int			runMainLoop			( void );

	//! add a command to the list; returns false if the string is in use
	static bool			addCommand			( const QString & s_cmd, cmdCallBack kb )
	{ return uniq_->cmd_map.addCommand( s_cmd, kb ); }

	//! remove a command to from list; returns false if not found or don't match
	static bool			remCommand			( const QString & s_cmd, cmdCallBack kb )
	{ return uniq_->cmd_map.remCommand( s_cmd, kb ); }

	//! execute the command associated with the given string
	static void			execute				( const QString & s_input )
	{ uniq_->cmd_map.execute( s_input ); }


	/*  FUNCTIONS    ======================================================= */
	//
	//
	//
	//

};	/*	class AbstractApril	*/

/*  CLASS    =============================================================== */
//
//
//
//

}   //  namespace   april

#endif // __ABSTRACTAPRIL_INC__
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
