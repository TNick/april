/* ========================================================================= */
/* ------------------------------------------------------------------------- */
/*!
  \file			dnaeditordlg.h
  \date			Apr 2013
  \author		TNick

  \brief		Contains the definition for DNAEditorDlg class


*//*


 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Please read COPYING and README files in root folder
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
#ifndef __DNAEDITORDLG_INC__
#define __DNAEDITORDLG_INC__
//
//
//
//
/*  INCLUDES    ------------------------------------------------------------ */

#include    <QDialog>
#include    <april/april.h>
#include	"ui_dnaeditordlg.h"

/*  INCLUDES    ============================================================ */
//
//
//
//
/*  DEFINITIONS    --------------------------------------------------------- */

namespace   april	{

namespace	Gui		{

/*  DEFINITIONS    ========================================================= */
//
//
//
//
/*  CLASS    --------------------------------------------------------------- */


/**
*	@brief	Dialog to create or edit a kind
*/
class DNAEditorDlg : public QDialog, public MemTrack		{
	Q_OBJECT
	BBM_TRACK( DNAEditorDlg );

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
	Ui::DNAEditorDlg 			ui;


	/*  DATA    ============================================================ */
	//
	//
	//
	//
	/*  FUNCTIONS    ------------------------------------------------------- */

public:

	//! constructor
	explicit				DNAEditorDlg		( QWidget *parent = 0 );

	//! destructor
	~DNAEditorDlg			(void);

protected:
	
	//!@{
	//! other events
	void					changeEvent			( QEvent *e );
	//!@}

	//!@{
	//! list of components
	void					addActuators		( void );
	void					addBrains			( void );
	void					addReflex			( void );
	void					addSensor			( void );
	void					remActuators		( void );
	void					remBrains			( void );
	void					remReflex			( void );
	void					remSensor			( void );
	//!@}
	


	/*  FUNCTIONS    ======================================================= */
	//
	//
	//
	//

};	/*	class DNAEditorDlg	*/

/*  CLASS    =============================================================== */
//
//
//
//

}	//	namespace	Gui

}   //  namespace   april

#endif // __DNAEDITORDLG_INC__
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
