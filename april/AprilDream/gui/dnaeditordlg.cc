/* ========================================================================= */
/* ------------------------------------------------------------------------- */
/*!
  \file			dnaeditordlg.cc
  \date			Apr 2013
  \author		TNick
  
  \brief		Contains the implementation for DNAEditorDlg class
  
  
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

#include	"dnaeditordlg.h"
#include	<QList>
#include	<QListWidget>
#include	<QListWidgetItem>
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
DNAEditorDlg::DNAEditorDlg					( QWidget *parent ) :
	QDialog(parent), MemTrack()
{
	APRDBG_CDTOR;
	
	ui.setupUi(this);
	connect( ui.buttonBox, SIGNAL( accepted() ),
			 this, SLOT( validate() ) );
	
	connect( ui.b_ak_add, SIGNAL( clicked() ),
			 this, SLOT( addActuators() ) );
	connect( ui.b_ak_rem, SIGNAL( clicked() ),
			 this, SLOT( remActuators() ) );
	connect( ui.b_brains_add, SIGNAL( clicked() ),
			 this, SLOT( addBrains() ) );
	connect( ui.b_brains_rem, SIGNAL( clicked() ),
			 this, SLOT( remBrains() ) );
	connect( ui.b_refl_add, SIGNAL( clicked() ),
			 this, SLOT( addReflex() ) );
	connect( ui.b_refl_rem, SIGNAL( clicked() ),
			 this, SLOT( remReflex() ) );
	connect( ui.b_refl_add, SIGNAL( clicked() ),
			 this, SLOT( addSensor() ) );
	connect( ui.b_refl_rem, SIGNAL( clicked() ),
			 this, SLOT( remSensor() ) );
	
	/*
	QDialogButtonBox *buttonBox;
	QLineEdit *le_name;
	QListWidget *ls_ak_others;
	QListWidget *ls_ak_part;
	QListWidget *ls_brains_other;
	QListWidget *ls_brains_part;
	QListWidget *ls_refl_other;
	QListWidget *ls_refl_part;
	QListWidget *ls_sens_other;
	QListWidget *ls_sens_part;
	QSpinBox *sp_age;
	QSpinBox *sp_cost;
	QSpinBox *sp_energy;
	QToolButton *b_ak_add;
	QToolButton *b_ak_rem;
	QToolButton *b_brains_add;
	QToolButton *b_brains_rem;
	QToolButton *b_refl_add;
	QToolButton *b_refl_rem;
	QToolButton *b_sens_add;
	QToolButton *b_sens_rem;
	*/
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
DNAEditorDlg::~DNAEditorDlg					( void )
{
	APRDBG_CDTOR;
	/* stub */
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void					DNAEditorDlg::changeEvent			( QEvent *e )
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
void		moveLeft		( QListWidget * src, QListWidget * dst )
{
	QList<QListWidgetItem*> itl = src->selectedItems();
	if ( itl.count() == 0 )
	{
		QMessageBox::warning(
					NULL, QObject::tr( "Failed to add" ),
					QObject::tr( "There is no selected item in\n"
								 "the right panel." ),
					QMessageBox::Ok );
		return;
	}
	foreach( QListWidgetItem* itr, itl )
	{
		src->takeItem( src->row(itr) );
		dst->addItem( itr );
	}
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void		moveRight		( QListWidget * dst, QListWidget * src )
{
	QList<QListWidgetItem*> itl = src->selectedItems();
	if ( itl.count() == 0 )
	{
		QMessageBox::warning(
					NULL, QObject::tr( "Failed to add" ),
					QObject::tr( "There is no selected item in\n"
								 "the left panel." ),
					QMessageBox::Ok );
		return;
	}
	foreach( QListWidgetItem* itr, itl )
	{
		src->takeItem( src->row(itr) );
		dst->addItem( itr );
	}
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void					DNAEditorDlg::addReflex			( void )
{
	moveLeft( ui.ls_refl_other, ui.ls_refl_part );
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void					DNAEditorDlg::remReflex			( void )
{
	moveRight( ui.ls_refl_other, ui.ls_refl_part );
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void					DNAEditorDlg::addBrains			( void )
{
	moveLeft( ui.ls_brains_other, ui.ls_brains_part );
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void					DNAEditorDlg::remBrains			( void )
{
	moveRight( ui.ls_brains_other, ui.ls_brains_part );
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void					DNAEditorDlg::addActuators		( void )
{
	moveLeft( ui.ls_ak_others, ui.ls_ak_part );	
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void					DNAEditorDlg::remActuators		( void )
{
	moveRight( ui.ls_ak_others, ui.ls_ak_part );	
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void					DNAEditorDlg::addSensor			( void )
{
	moveLeft( ui.ls_sens_other, ui.ls_sens_part );	
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void					DNAEditorDlg::remSensor			( void )
{
	moveRight( ui.ls_sens_other, ui.ls_sens_part );	
}
/* ========================================================================= */


/*  CLASS    =============================================================== */
//
//
//
//
/* ------------------------------------------------------------------------- */
/* ========================================================================= */







