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
#include    <april/gui/worlds/wqstauto.h>

#include    <april/AprilDream/gui/dockcrtsel.h>
#include    <april/AprilDream/gui/dockids.h>
#include    <april/AprilDream/gui/docktree.h>
#include    <april/AprilDream/gui/dockworld.h>
#include    <april/AprilDream/gui/sceneviewer.h>


/*  INCLUDES    ============================================================ */
//
//
//
//
/*  DEFINITIONS    --------------------------------------------------------- */

class	QLabel;

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
	
	//! the scene 
	WqsTAuto		w_scene_;
	
	//! the scene viewer
	SceneViewer		viever_;
	
	//! the label showing run/stop status
	QLabel *		l_run;
	
	
	/*  DATA    ============================================================ */
	//
	//
	//
	//
	/*  FUNCTIONS    ------------------------------------------------------- */

public:

	//! constructor
	explicit				MW					( QWidget *parent = 0 );

	//! destructor
	~MW						( void );
	
	//! tell if we have a world loaded or not
	bool					hasWorld			( void ) const
	{ return w_scene_.hasWorld(); }
	
	//! underlying world
	World *					world				( void ) const
	{ return w_scene_.world(); }
	
	//! show an error message
	void					showError			( const QString & s_msg );
	
	//! show an informative message
	void					showInfo			( const QString & s_msg );
	
protected:

	//! examine change events for run-time language change
	void					changeEvent			( QEvent *e );

private slots:
	
	//! start the world
	void					startWorld			( void );
	
	//!  stop the world
	void					stopWorld			( void );
	
	
	//!@{
	//! basic slots for world
	bool					slotNewWorld		( void );
	bool					slotOpenWorld		( void );
	bool					slotCloseWorld		( void );
	bool					slotSaveWorld		( void );
	bool					slotSaveWorldAs		( void );
	//!@}
	

private:

	
	//!@{
	//! prepare to start
	void					prepareActionsWorld	( void );
	//!@}
	
	//! called when a world is opened/created or closed
	void					newWorldStatus		( void );

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
