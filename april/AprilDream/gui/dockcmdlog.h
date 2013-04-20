/* ========================================================================= */
/* ------------------------------------------------------------------------- */
/*!
  \file			dockcmdlog.h
  \date			Apr 2013
  \author		TNick

  \brief		Contains the definition for DockCmdLog class


*//*


 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Please read COPYING and README files in root folder
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
#ifndef __DOCKCMDLOG_INC__
#define __DOCKCMDLOG_INC__
//
//
//
//
/*  INCLUDES    ------------------------------------------------------------ */

#include    <april/april.h>
#include    <april/AprilDream/gui/dock.h>

/*  INCLUDES    ============================================================ */
//
//
//
//
/*  DEFINITIONS    --------------------------------------------------------- */

namespace   april    {

namespace	Gui		{

class	MW;
class	DockCmdLog_p;

/*  DEFINITIONS    ========================================================= */
//
//
//
//
/*  CLASS    --------------------------------------------------------------- */

/**
*	@brief	Command and log dock panel
*/
class DockCmdLog		: public Dock		{
	BBM_TRACK( DockCmdLog );

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

	//! data only allocated when visible
	DockCmdLog_p *		d_;

	/*  DATA    ============================================================ */
	//
	//
	//
	//
	/*  FUNCTIONS    ------------------------------------------------------- */

public:

	//! constructor
	DockCmdLog			( MW * mw );

	//! destructor;
	virtual				~DockCmdLog		( void );

protected:

	//! used to construct the widget
	void				construct				( void );

	//! used to destruct the widget
	void				deconstruct				( void );


	/*  FUNCTIONS    ======================================================= */
	//
	//
	//
	//

};	/*	class DockCmdLog	*/

/*  CLASS    =============================================================== */
//
//
//
//

}   //  namespace   Gui

}   //  namespace   april

#endif // __DOCKCMDLOG_INC__
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
