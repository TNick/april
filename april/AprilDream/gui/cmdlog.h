/* ========================================================================= */
/* ------------------------------------------------------------------------- */
/*!
  \file			cmdlog.h
  \date			Apr 2013
  \author		TNick

  \brief		Contains the definition for CmdLog class


*//*


 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Please read COPYING and README files in root folder
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
#ifndef __CMDLOG_INC__
#define __CMDLOG_INC__
//
//
//
//
/*  INCLUDES    ------------------------------------------------------------ */

#include    <QMainWindow>
#include    <april/april.h>
#include	"ui_cmdlog.h"

/*  INCLUDES    ============================================================ */
//
//
//
//
/*  DEFINITIONS    --------------------------------------------------------- */

namespace   april    {

class CommandMap;

namespace	Gui		{

class	MW;

/*  DEFINITIONS    ========================================================= */
//
//
//
//
/*  CLASS    --------------------------------------------------------------- */


/**
*	@brief	Form that allows interfacing with april-cmd library
*/
class CmdLog : public QWidget, public MemTrack		{
	Q_OBJECT
	BBM_TRACK( CmdLog );

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
	CommandMap *			cmd_map_;

	//! the CommandMap instance is owned by us
	bool					b_own_map_;
	
	//! GUI components embedded here
	Ui::CmdLog				ui;
	

	/*  DATA    ============================================================ */
	//
	//
	//
	//
	/*  FUNCTIONS    ------------------------------------------------------- */

public:

	//! constructor
	explicit			CmdLog				( QWidget * parent  );

	//! destructor
	~CmdLog				( void );
	
	
protected:

	//!@{
	//! other events
	void				changeEvent			( QEvent *e );
	//!@}

private slots:
	
	//! executes the command in the text area
	void				executeCommand		( void );
	
signals:

	//! the program should close
	void				appClose			( void );
	
	/*  FUNCTIONS    ======================================================= */
	//
	//
	//
	//

};	/*	class CmdLog	*/

/*  CLASS    =============================================================== */
//
//
//
//

}	//	namespace	Gui

}   //  namespace   april

#endif // __CMDLOG_INC__
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
