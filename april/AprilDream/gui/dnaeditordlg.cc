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
#include	<april/logic/eventsource.h>
#include	<april/logic/eventfactory.h>
#include	<april/logic/sensor.h>
#include	<april/logic/sensorfactory.h>
#include	<april/logic/actuator.h>
#include	<april/logic/actuatorfactory.h>
#include	<april/logic/brain.h>
#include	<april/logic/brainfactory.h>
#include	<april/logic/reflex.h>
#include	<april/logic/reflexfactory.h>
#include	<april/logic/world.h>
#include	<april/AprilDream/gui/mw.h>


/*  INCLUDES    ============================================================ */
//
//
//
//
/*  DEFINITIONS    --------------------------------------------------------- */

using namespace april;
using namespace april::Gui;

//! an item in a list holding an ID for future use
class IdEntry : public QListWidgetItem, public MemTrack {
	BBM_TRACK( IdEntry );
public:
	ID	id_;
	IdEntry( ID id, const QString & s_name, const QString & s_factory_name )
		: QListWidgetItem(),
		  id_(id)
	{
		setText( QObject::tr( "%1\t%2 (%3)" )
				 .arg( id )
				 .arg( s_name )
				 .arg( s_factory_name )
				 );
	}
};

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
DNAEditorDlg::DNAEditorDlg					( MW * parent, World * w ) :
	QDialog(parent), MemTrack(),
	w_( w )
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
	
	
	{
		const QMap<ID,SensorFactory*> & sf = w_->sensorFactories();
		QMap<ID,SensorFactory*>::ConstIterator itr = sf.constBegin();
		QMap<ID,SensorFactory*>::ConstIterator itr_e = sf.constEnd();
		while ( itr != itr_e )
		{
			IdEntry * ide = 
					new IdEntry( 
						itr.key(),
						w->nameForId( itr.key() ), 
						itr.value()->factoryName() );
			ui.ls_sens_other->addItem( ide );
			itr++;
		}
	}
	{
		const QMap<ID,BrainFactory*> & sf = w_->brainFactories();
		QMap<ID,BrainFactory*>::ConstIterator itr = sf.constBegin();
		QMap<ID,BrainFactory*>::ConstIterator itr_e = sf.constEnd();
		while ( itr != itr_e )
		{
			IdEntry * ide = 
					new IdEntry( 
						itr.key(),
						w->nameForId( itr.key() ), 
						itr.value()->factoryName() );
			ui.ls_brains_other->addItem( ide );
			itr++;
		}
	}
	{
		const QMap<ID,ReflexFactory*> & sf = w_->reflexFactories();
		QMap<ID,ReflexFactory*>::ConstIterator itr = sf.constBegin();
		QMap<ID,ReflexFactory*>::ConstIterator itr_e = sf.constEnd();
		while ( itr != itr_e )
		{
			IdEntry * ide = 
					new IdEntry( 
						itr.key(),
						w->nameForId( itr.key() ), 
						itr.value()->factoryName() );
			ui.ls_refl_other->addItem( ide );
			itr++;
		}
	}
	{
		const QMap<ID,ActuatorFactory*> & sf = w_->actuatorFactories();
		QMap<ID,ActuatorFactory*>::ConstIterator itr = sf.constBegin();
		QMap<ID,ActuatorFactory*>::ConstIterator itr_e = sf.constEnd();
		while ( itr != itr_e )
		{
			IdEntry * ide = 
					new IdEntry( 
						itr.key(),
						w->nameForId( itr.key() ), 
						itr.value()->factoryName() );
			ui.ls_ak_others->addItem( ide );
			itr++;
		}
	}
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

/* ------------------------------------------------------------------------- */
void					DNAEditorDlg::validate			( void )
{
	
	/** @todo validate */
	
}
/* ========================================================================= */


/*  CLASS    =============================================================== */
//
//
//
//
/* ------------------------------------------------------------------------- */
/* ========================================================================= */







