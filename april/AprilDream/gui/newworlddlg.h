/* ========================================================================= */
/* ------------------------------------------------------------------------- */
/*!
  \file			newworlddlg.h
  \date			Apr 2013
  \author		TNick

  \brief		Contains the definition for NewWorldDlg class


*//*


 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Please read COPYING and README files in root folder
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
#ifndef __NEWWORLDDLG_INC__
#define __NEWWORLDDLG_INC__
//
//
//
//
/*  INCLUDES    ------------------------------------------------------------ */

#include    <QDialog>
#include    <april/april.h>
#include	"ui_newworlddlg.h"

/*  INCLUDES    ============================================================ */
//
//
//
//
/*  DEFINITIONS    --------------------------------------------------------- */

namespace   april	{

class	World;

namespace	Gui		{

/*  DEFINITIONS    ========================================================= */
//
//
//
//
/*  CLASS    --------------------------------------------------------------- */

/**
*	@brief	Dialog to create a new world
*/
class NewWorldDlg : public QDialog, public MemTrack		{
	Q_OBJECT
	BBM_TRACK( NewWorldDlg );

	//
	//
	//
	//
	/*  DEFINITIONS    ----------------------------------------------------- */

public:

	//! the type
	enum PredefinedTypes {
		DefaultType = 0
	};
	
	//! threading mode
	enum ThreadingMode {
		ThreadNone = 0,	/**< No threads */
		ThreadOne,		/**< A worker thread */
		ThreadTwo,		/**< 2 worker threads */
		ThreadFour,		/**< 4 worker threads */
		ThreadEight,	/**< 8 worker threads */
		Thread16,		/**< 16 worker threads */
		Thread64,		/**< 64 worker threads */
		ThreadActor,	/**< One thread for each actor */
		
		ThreadMax
	};
	
	//! data for general tab
	struct GeneralData		{
		int				type_;		/**< index of the type - 0 is DefaultType */
		ThreadingMode	th_mode_;	/**< threading mode */
		quint64			energy_;	/**< amount of energy in the world */
		QString			s_name_;	/**< name */
		QString			s_file_;	/**< file */
	};

	/*  DEFINITIONS    ===================================================== */
	//
	//
	//
	//
	/*  DATA    ------------------------------------------------------------ */

private:

	//! GUI components embedded in this instance
	Ui::NewWorldDlg 			ui;

	//! the world that is created
	World *						w_;

	//! the data inside general tab
	GeneralData					data_;
	
	/*  DATA    ============================================================ */
	//
	//
	//
	//
	/*  FUNCTIONS    ------------------------------------------------------- */

public:

	//! constructor
	explicit			NewWorldDlg		( QWidget *parent = 0 );

	//! destructor
	~NewWorldDlg		(void);
	
	//! the world that is created
	inline World *		world			( void ) const
	{ return w_; }

	//! the data inside general tab
	GeneralData &		generalData		( void )
	{ return data_; }

protected:

	//!@{
	//! other events
	void				changeEvent			( QEvent *e );
	//!@}
	
private slots:

	//! check the input; if OK emmit accepted()
	void				validateAndClose	( void );
	
	//! change current type
	void				changeType			( int i );
	
	//! pick a file
	void				browseForFile		( void );


	/*  FUNCTIONS    ======================================================= */
	//
	//
	//
	//

};	/*	class NewWorldDlg	*/

/*  CLASS    =============================================================== */
//
//
//
//

}	//	namespace	Gui

}   //  namespace   april

#endif // __NEWWORLDDLG_INC__
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
