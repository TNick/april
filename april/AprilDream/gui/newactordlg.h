/* ========================================================================= */
/* ------------------------------------------------------------------------- */
/*!
  \file			newactordlg.h
  \date			Apr 2013
  \author		TNick

  \brief		Contains the definition for NewActorDlg class


*//*


 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Please read COPYING and README files in root folder
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
#ifndef __NEWACTORDLG_INC__
#define __NEWACTORDLG_INC__
//
//
//
//
/*  INCLUDES    ------------------------------------------------------------ */

#include    <QDialog>
#include    <april/april.h>
#include    <april/logic/uniqueid.h>
#include	"ui_newactordlg.h"

/*  INCLUDES    ============================================================ */
//
//
//
//
/*  DEFINITIONS    --------------------------------------------------------- */

namespace   april	{

class	World;

namespace	Gui		{

class	MW;

/*  DEFINITIONS    ========================================================= */
//
//
//
//
/*  CLASS    --------------------------------------------------------------- */


/**
*	@brief	Dialog to add a new actor
*/
class NewActorDlg : public QDialog, public MemTrack		{
	Q_OBJECT
	BBM_TRACK( NewActorDlg );

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

	//! GUI components embedded in this instance
	Ui::NewActorDlg 			ui;

	//! the world we're editing
	World *						w_;

	/*  DATA    ============================================================ */
	//
	//
	//
	//
	/*  FUNCTIONS    ------------------------------------------------------- */

public:

	//! constructor
	explicit				NewActorDlg		(  MW * parent, World * w );

	//! destructor
	~NewActorDlg			(void);

	//! the ID that was selected by the user
	ID						selectedID		( void ) const;

protected:
	
	//!@{
	//! other events
	void					changeEvent		( QEvent *e );
	//!@}

	/*  FUNCTIONS    ======================================================= */
	//
	//
	//
	//

};	/*	class NewActorDlg	*/

/*  CLASS    =============================================================== */
//
//
//
//

}	//	namespace	Gui

}   //  namespace   april

#endif // __NEWACTORDLG_INC__
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
