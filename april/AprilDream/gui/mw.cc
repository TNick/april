/* ========================================================================= */
/* ------------------------------------------------------------------------- */
/*!
  \file			mw.cc
  \date			Apr 2013
  \author		TNick
  
  \brief		Contains the implementation for MW class
  
  
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


#include	"mw.h"
#include	"ui_mw.h"
#include	<QLabel>

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
MW::MW	( QWidget *parent ) :
	QMainWindow( parent ), MemTrack(),
	ui(),
	d_crt_sel_(this),
	d_ids_(this),
	d_tree_(this),
	d_world_(this),
	w_scene_(),
	viever_(),
	l_run(NULL)
{
	APRDBG_CDTOR;
	ui.setupUi( this );
	
	ui.menuView->addAction( d_crt_sel_.action() );
	ui.menuView->addAction( d_ids_.action() );
	ui.menuView->addAction( d_tree_.action() );
	ui.menuView->addAction( d_world_.action() );
	
	setCentralWidget( &viever_ );
	viever_.setScene( &w_scene_ );
	
	connect( ui.actionStart, SIGNAL(triggered()),
			 this, SLOT( startWorld() ) );
	connect( ui.actionStop, SIGNAL(triggered()),
			 this, SLOT( stopWorld() ) );
	
	l_run = new QLabel( ui.statusbar );
	ui.statusbar->addWidget( l_run );
	l_run->setTextFormat(Qt::RichText);
    l_run->setText("<img src=\":/pause.png\">");
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
MW::~MW	( void )
{
	APRDBG_CDTOR;
	/* stub */
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void					MW::changeEvent			( QEvent * e )
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

/* ------------------------------------------------------------------------- */
void					MW::startWorld			( void )
{
	if ( w_scene_.start() )
	{
		l_run->setTextFormat(Qt::RichText);
		l_run->setText("<img src=\":/play.png\">");
	}
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void					MW::stopWorld			( void )
{
	if ( w_scene_.stop() )
	{
		l_run->setTextFormat(Qt::RichText);
		l_run->setText("<img src=\":/pause.png\">");
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
