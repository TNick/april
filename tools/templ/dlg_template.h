/* ========================================================================= */
/* ------------------------------------------------------------------------- */
/*!
  \file			##FILENAME##.h
  \date			##DATA##
  \author		##AUTHOR##

  \brief		Contains the definition for ##CLASS## class


*//*


 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Please read COPYING and README files in root folder
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
#ifndef __##U_FILENAME##_INC__
#define __##U_FILENAME##_INC__
//
//
//
//
/*  INCLUDES    ------------------------------------------------------------ */

#include    <QDialog>
#include    <april/april.h>
#include	"ui_##FILENAME##.h"

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
*	@brief	Dialog to ...
*/
class ##CLASS## : public QDialog, public MemTrack		{
	Q_OBJECT
	BBM_TRACK( ##CLASS## );

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
	Ui::##CLASS## 			ui;


	/*  DATA    ============================================================ */
	//
	//
	//
	//
	/*  FUNCTIONS    ------------------------------------------------------- */

public:

	//! constructor
	explicit			##CLASS##		( QWidget *parent = 0 );

	//! destructor
	~##CLASS##			(void);

protected:
	
	//!@{
	//! other events
	void				changeEvent			( QEvent *e );
	//!@}

	/*  FUNCTIONS    ======================================================= */
	//
	//
	//
	//

};	/*	class ##CLASS##	*/

/*  CLASS    =============================================================== */
//
//
//
//

}	//	namespace	Gui

}   //  namespace   april

#endif // __##U_FILENAME##_INC__
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
