/* ========================================================================= */
/* ------------------------------------------------------------------------- */
/*!
  \file			mw.h
  \date			Apr 2013
  \author		TNick

  \brief		Contains the definition for MW class


*//*


 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Please read COPYING and README files in root folder
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
#ifndef __MW_INC__
#define __MW_INC__
//
//
//
//
/*  INCLUDES    ------------------------------------------------------------ */

#include    <QMainWindow>
#include    <april/april.h>
#include	"ui_mw.h"
#include    <april/AprilDream/gui/dockcrtsel.h>
#include    <april/AprilDream/gui/dockids.h>
#include    <april/AprilDream/gui/docktree.h>
#include    <april/AprilDream/gui/dockworld.h>

/*  INCLUDES    ============================================================ */
//
//
//
//
/*  DEFINITIONS    --------------------------------------------------------- */

namespace   april    {

namespace	Gui		{

/*  DEFINITIONS    ========================================================= */
//
//
//
//
/*  CLASS    --------------------------------------------------------------- */

/**
*	@brief	Form that represents the main widget for the application
*/
class MW : public QMainWindow, public MemTrack		{
	Q_OBJECT
	BBM_TRACK( MW );

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

	//! GUI components embedded here
	Ui::MW         ui;

	//!@{ 
	//! dock widget
	DockCrtSel		d_crt_sel_;
	DockIds			d_ids_;
	DockTree		d_tree_;
	DockWorld		d_world_;
	//!@}
	
	
	/*  DATA    ============================================================ */
	//
	//
	//
	//
	/*  FUNCTIONS    ------------------------------------------------------- */

public:

	//! constructor
	explicit			MW		( QWidget *parent = 0 );

	//! destructor
	~MW					(void);

protected:

	//! examine change events for run-time language change
	void				changeEvent		( QEvent *e );


	/*  FUNCTIONS    ======================================================= */
	//
	//
	//
	//

};	/*	class MW	*/

/*  CLASS    =============================================================== */
//
//
//
//

}	//	namespace	Gui

}   //  namespace   april

#endif // __MW_INC__
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
