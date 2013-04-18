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
#include	"newworlddlg.h"
#include	"pluginsdlg.h"
#include	"dnaeditordlg.h"
#include	"newactordlg.h"

#include	<april/logic/world.h>
#include	<april/aprillibrary.h>

#include	<QLabel>
#include	<QFileDialog>
#include	<QMessageBox>

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
	
	prepareActionsWorld();
	prepareActionsComp();
	
	connect( ui.actionStart, SIGNAL(triggered()),
			 this, SLOT( startWorld() ) );
	connect( ui.actionStop, SIGNAL(triggered()),
			 this, SLOT( stopWorld() ) );
	connect( ui.action_plug_ins, SIGNAL(triggered()),
			 this, SLOT( showplugIns() ) );
	
	l_run = new QLabel( ui.statusbar );
	ui.statusbar->addWidget( l_run );
	l_run->setTextFormat(Qt::RichText);
	l_run->setText("<img src=\":/pause.png\">");
	
	newWorldStatus();
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void					MW::prepareActionsWorld	( void )
{
	connect( ui.action_new_world, SIGNAL( triggered() ),
			 this, SLOT( slotNewWorld() ) );
	connect( ui.action_open_world, SIGNAL( triggered() ),
			 this, SLOT( slotOpenWorld() ) );
	connect( ui.action_close_current_world, SIGNAL( triggered() ),
			 this, SLOT( slotCloseWorld() ) );
	connect( ui.action_save_world, SIGNAL( triggered() ),
			 this, SLOT( slotSaveWorld() ) );
	connect( ui.action_save_world_as, SIGNAL( triggered() ),
			 this, SLOT( slotSaveWorldAs() ) );
	connect( ui.action_exit, SIGNAL( triggered() ),
			 this, SLOT( close() ) );
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void					MW::prepareActionsComp	( void )
{
	connect( ui.action_new_kind, SIGNAL( triggered() ),
			 this, SLOT( slotNewKind() ) );
	connect( ui.action_edit_kind, SIGNAL( triggered() ),
			 this, SLOT( slotEditKind() ) );
	connect( ui.action_new_actor, SIGNAL( triggered() ),
			 this, SLOT( slotNewActor() ) );
	connect( ui.action_kill_actor, SIGNAL( triggered() ),
			 this, SLOT( slotKillActor() ) );
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
void					MW::showError			( const QString & s_msg )
{
	Q_ASSERT( s_msg.isEmpty() == false );
	ui.statusbar->showMessage( s_msg, 10 );
	QMessageBox::critical( this, "Error in AprilDream", s_msg );
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void					MW::showInfo			( const QString & s_msg )
{
	Q_ASSERT( s_msg.isEmpty() == false );
	ui.statusbar->showMessage( s_msg, 10 );
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

/* ------------------------------------------------------------------------- */
void					MW::showplugIns			( void )
{
	PluginsDlg pdlg( this );
	int i = pdlg.exec();
	if ( i == QDialog::Accepted )
	{
		/* stub */
	}
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool					MW::slotNewWorld	( void )
{
	NewWorldDlg wdlg( this );
	int i = wdlg.exec();
	if ( i == QDialog::Accepted )
	{
		Q_ASSERT( wdlg.world() != NULL );
		QString s_err;
		if ( w_scene_.loadWorld( wdlg.world(), s_err ) == false )
		{
			showError( s_err );
			AprilLibrary::remWorld( wdlg.world() );
		}
		else
		{
			newWorldStatus();
			return true;
		}
	}
	return false;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool					MW::slotOpenWorld	( void )
{
	QString fileName = QFileDialog::getOpenFileName(
				this,
				tr( "Select the file to open:" ),
				QString(),
				QString()
				);
	if ( !fileName.isEmpty() )
	{
		QString s_err;
		if ( w_scene_.openWorld( fileName, s_err ) == false )
		{
			showError( tr( "Could not load file %1!\n%2" )
					   .arg( fileName )
					   .arg( s_err ) );
		}
		else
		{
			newWorldStatus();
			return true;
		}
	}
	return false;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool					MW::slotCloseWorld	( void )
{
	QString s_err;
	if ( w_scene_.closeWorld( s_err ) == false )
	{
		if ( s_err.isEmpty() == false )
			showError( s_err );
		return false;
	}
	else
	{
		newWorldStatus();
		return true;
	}
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool					MW::slotSaveWorld	( void )
{
	if ( hasWorld() == false )
		return false;
	QString s_err;
	if ( w_scene_.save( s_err ) == false )
	{
		if ( s_err.isEmpty() == false )
			showError( s_err );
		return false;
	}
	newWorldStatus();
	return true;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool					MW::slotSaveWorldAs	( void )
{
	if ( hasWorld() == false )
		return false;
	QString s_err;
	if ( w_scene_.saveAs( s_err ) == false )
	{
		if ( s_err.isEmpty() == false )
			showError( s_err );
		return false;
	}
	newWorldStatus();
	return true;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void					MW::slotNewKind			( void )
{
	if ( hasWorld() == false )
		return;
	DNAEditorDlg	ded(this);
	ded.exec();
	/** @todo slotNewKind() */
	newWorldStatus();
	return;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void					MW::slotEditKind		( void )
{
	if ( hasWorld() == false )
		return;
	DNAEditorDlg	ded(this);
	ded.exec();
	
	/** @todo slotEditKind() */
	
	newWorldStatus();
	return;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void					MW::slotNewActor		( void )
{
	if ( hasWorld() == false )
		return;
	NewActorDlg acd(this);
	acd.exec();
	
	/** @todo slotNewActor() */
	
	newWorldStatus();
	return;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void					MW::slotKillActor		( void )
{
	if ( hasWorld() == false )
		return;
	
	/** @todo slotKillActor() */
	
	newWorldStatus();
	return;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void					MW::newWorldStatus	( void )
{
	bool b = hasWorld();
	
	ui.actionStart->setEnabled( b );
	ui.actionStop->setEnabled( b );
	ui.action_close_current_world->setEnabled( b );
	ui.action_save_world->setEnabled( b );
	ui.action_save_world_as->setEnabled( b );
	viever_.setEnabled( b );
	if ( b )
	{
		QString s_file = w_scene_.hasAssociatedFile() ? 
					w_scene_.associatedFile() : 
					tr("no file");
		setWindowTitle( tr("%1[*] <%2> - AprilDream")
						.arg( world()->name() )
						.arg( s_file )
						);
	}
	else
	{
		setWindowTitle( tr( "AprilDream (no world loaded)" ) );
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
