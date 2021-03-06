/* ========================================================================= */
/* ------------------------------------------------------------------------- */
/*!
  \file			##FILENAME##.cc
  \date			##DATA##
  \author		##AUTHOR##

  \brief		Contains the implementation for ##CLASS## class


*//*


 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Please read COPYING and README files in root folder
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
//
//
//
//
/*  INCLUDES    ------------------------------------------------------------ */


#include	"##FILENAME##.h"
#include	"ui_##FILENAME##.h"

/*  INCLUDES    ============================================================ */
//
//
//
//
/*  DEFINITIONS    --------------------------------------------------------- */

using namespace april;
using namespace april::Gui;

/*  DEFINITIONS    ========================================================= */
//
//
//
//
/*  DATA    ---------------------------------------------------------------- */

/*  DATA    ================================================================ */
//
//
//
//
/*  CLASS    --------------------------------------------------------------- */

/* ------------------------------------------------------------------------- */
##CLASS##::##CLASS##	( QWidget *parent ) :
	QMainWindow( parent ), MemTrack()
{
	APRDBG_CDTOR;

	ui.setupUi( this );

}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
##CLASS##::~##CLASS##	( void )
{
	APRDBG_CDTOR;
	/* stub */
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void					##CLASS##::changeEvent			( QEvent * e )
{
	QMainWindow::changeEvent( e );
	switch ( e->type() ) {
	case QEvent::LanguageChange:	{
		ui.retranslateUi( this );
		break;}
	default:						{
		break;}
	}
}
/* ========================================================================= */

/*  CLASS    =============================================================== */
//
//
//
//
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
