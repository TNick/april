/* ========================================================================= */
/* ------------------------------------------------------------------------- */
/*!
  \file			pluginsdlg.h
  \date			Apr 2013
  \author		TNick

  \brief		Contains the definition for PluginsDlg class


*//*


 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Please read COPYING and README files in root folder
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
#ifndef __PLUGINSDLG_INC__
#define __PLUGINSDLG_INC__
//
//
//
//
/*  INCLUDES    ------------------------------------------------------------ */

#include    <QDialog>
#include    <april/april.h>
#include	"ui_pluginsdlg.h"

/*  INCLUDES    ============================================================ */
//
//
//
//
/*  DEFINITIONS    --------------------------------------------------------- */

namespace   april	{

namespace	Gui		{

class	PlginEntry;

/*  DEFINITIONS    ========================================================= */
//
//
//
//
/*  CLASS    --------------------------------------------------------------- */


/**
*	@brief	Dialog to list plugins
*/
class PluginsDlg : public QDialog, public MemTrack		{
	Q_OBJECT
	BBM_TRACK( PluginsDlg );

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
	Ui::PluginsDlg 			ui;

	
	/*  DATA    ============================================================ */
	//
	//
	//
	//
	/*  FUNCTIONS    ------------------------------------------------------- */

public:

	//! constructor
	explicit			PluginsDlg		( QWidget *parent = 0 );

	//! destructor
	~PluginsDlg			(void);
	
protected:
	
	//!@{
	//! other events
	void				changeEvent			( QEvent *e );
	//!@}

private slots:

	//! add a directory to our list
	void				addDirectory		( void );

	//! remove directories
	void				remDirectory		( void );

	//! scan directories again
	void				rescan				( void );

	//! if al ok exit
	void				validateAndClose	( void );

private:

	//! scan directories and add plug-ins to the list
	void				scanDirectories		( void );
	
	//! scan a single directory and add plug-ins to the list
	void				scanDirectory		( const QString & s );
	
	//! load directories in the list
	void				loadDirectories		( void );
	
	//! save directories in the list
	void				saveDirectories		( void );
	
	//! load plug-ins from the library
	void				loadLibraryPlugins	( void );
	
	//! find the structure for a certain file
	PlginEntry *		findPlugIn			( const QString & s );

	//! item was double-clicked => mark as loaded/unloaded
	void				itemDoubleClicked	( QTreeWidgetItem * it, int col);

	/*  FUNCTIONS    ======================================================= */
	//
	//
	//
	//

};	/*	class PluginsDlg	*/

/*  CLASS    =============================================================== */
//
//
//
//

}	//	namespace	Gui

}   //  namespace   april

#endif // __PLUGINSDLG_INC__
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
