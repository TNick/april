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

#include    <QMainWindow>
#include    <april/april.h>
#include	"ui_##FILENAME##.h"

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
*	@brief	Form that ...
*/
class ##CLASS## : public QMainWindow, public MemTrack		{
	Q_OBJECT
	BBM_TRACK( ##CLASS## )

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

	/**
	*	@brief	GUI components embedded here
	*/
   Ui::##CLASS##         ui;


	/*  DATA    ============================================================ */
	//
	//
	//
	//
	/*  FUNCTIONS    ------------------------------------------------------- */

public:

	/**
	*	@brief	constructor
	*/
	explicit			##CLASS##		( QWidget *parent = 0 );


	/**
	*	@brief	destructor
	*/
	~##CLASS##		(void);


protected:
	void				changeEvent		( QEvent *e );


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
