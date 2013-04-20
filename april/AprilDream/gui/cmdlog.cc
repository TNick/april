/* ========================================================================= */
/* ------------------------------------------------------------------------- */
/*!
  \file			cmdlog.cc
  \date			Apr 2013
  \author		TNick

  \brief		Contains the implementation for CmdLog class


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


#include	"cmdlog.h"
#include	"ui_cmdlog.h"
#include    <april/cmd/commandmap.h>
#include    <april/AprilDream/gui/mw.h>

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
CmdLog::CmdLog	( QWidget * parent ) :
	QWidget( parent ), MemTrack(),
	cmd_map_(CommandMap::defaultInstance()),
	b_own_map_(false),
	ui()
{
	APRDBG_CDTOR;

	ui.setupUi( this );
	connect( ui.le_cmd, SIGNAL( returnPressed() ),
			 this, SLOT( executeCommand() ) );
	connect( ui.b_exec, SIGNAL( clicked() ),
			 this, SLOT( executeCommand() ) );
	if ( cmd_map_ == NULL )
	{
		cmd_map_ = new CommandMap();
		b_own_map_ = true;
	}
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
CmdLog::~CmdLog	( void )
{
	APRDBG_CDTOR;
	if ( b_own_map_ )
		delete cmd_map_;
	
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void					CmdLog::changeEvent			( QEvent * e )
{
	QWidget::changeEvent( e );
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
void					CmdLog::executeCommand		( void )
{
	QString s_cmd = ui.le_cmd->text();
	if ( s_cmd.isEmpty() )
	{
		ui.te_log->appendPlainText( tr( "No command to execute.\n" ) );
		return;
	}
	ui.te_log->appendPlainText( "> " + s_cmd );
	
	cmd_map_->execute( s_cmd );
	if ( cmd_map_->shouldExit() )
	{
		emit appClose();
	}
	ui.le_cmd->clear();
}
/* ========================================================================= */

/*  CLASS    =============================================================== */
//
//
//
//
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
