/* ========================================================================= */
/* ------------------------------------------------------------------------- */
/*!
  \file			newworlddlg.cc
  \date			Apr 2013
  \author		TNick

  \brief		Contains the implementation for NewWorldDlg class


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

#include	"newworlddlg.h"
#include	<QFileDialog>
#include	<QMessageBox>
#include	<april/logic/world.h>

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
NewWorldDlg::NewWorldDlg					( QWidget *parent ) :
	QDialog(parent), MemTrack(),
	ui(),
	w_( NULL ),
	data_()
{
	APRDBG_CDTOR;

	ui.setupUi(this);

    connect( ui.buttonBox, SIGNAL( accepted() ), 
			 this, SLOT( validateAndClose() ) );
    connect( ui.cb_type, SIGNAL( currentIndexChanged(int) ), 
			 this, SLOT( changeType(int) ) );
    connect( ui.b_file, SIGNAL( clicked() ), 
			 this, SLOT( browseForFile() ) );
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
NewWorldDlg::~NewWorldDlg					( void )
{
	APRDBG_CDTOR;
	if ( w_ != NULL )
	{
		DEC_REF(w_,this);
	}
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void					NewWorldDlg::changeEvent			( QEvent *e )
{
	QDialog::changeEvent( e );
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
void					NewWorldDlg::validateAndClose		( void )
{
	data_.type_ = ui.cb_type->currentIndex();
	data_.th_mode_ = (ThreadingMode)ui.cb_threads->currentIndex();
	data_.energy_ = ui.sp_energy->value();
	data_.s_name_ = ui.le_name->text();
	data_.s_file_ = ui.le_file->text();
	
	if ( data_.s_name_.isEmpty() )
	{
		ui.tabWidget->setCurrentIndex( 0 );
		ui.le_name->setFocus();
		QMessageBox::critical( this, tr( "New world" ), 
							   tr( "The world must have a name" ) );
		return;
	}
	Q_ASSERT( data_.type_ >= 0 );
	Q_ASSERT( data_.th_mode_ >= ThreadNone );
	Q_ASSERT( data_.th_mode_ < ThreadMax );
	Q_ASSERT( data_.energy_ > 0 );
	
	if ( data_.type_ == DefaultType )
	{
		w_ = new World( data_.s_name_, data_.energy_ );
		OWN_CREF(w_,this);
		//setResult( QDialog::Accepted );
		accept();
	}
	else
	{
		/** @todo for custom types of worlds create the custom world */
	}
	return;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void					NewWorldDlg::changeType				( int i )
{
	Q_UNUSED( i );
	/** @todo for custom types of worlds load config dialog */
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void					NewWorldDlg::browseForFile			( void )
{
	QString fileName = QFileDialog::getOpenFileName(
				this,
				tr( "Save world as:" ),
				ui.le_file->text(),
				QString()
				);
	if ( !fileName.isEmpty() )
	{
		ui.le_file->setText( fileName );
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







