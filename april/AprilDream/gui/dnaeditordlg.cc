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
#include	<april/logic/dna.h>
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
#include	<april/logic/genericactorfactory.h>
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

	//! holding the id for future reference
	ID	id_;
	
	//! constructor
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

DNA					DNAEditorDlg::invalid_dna_;

/*  DATA    ================================================================ */
//
//
//
//
/*  CLASS    --------------------------------------------------------------- */

/* ------------------------------------------------------------------------- */
DNAEditorDlg::DNAEditorDlg					( MW * parent, World * w ) :
	QDialog(parent), MemTrack(),
	w_( w ), dna_( invalid_dna_ )
{
	APRDBG_CDTOR;
	init();
	setWindowTitle( tr( "Create a new kind" ) );
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
static void				addIdList			( 
		const QList<ID> & lst, QListWidget * existing, QListWidget * mine )
{
	foreach( ID id, lst )
	{
		int i_max = existing->count();
		for ( int i = 0; i < i_max; i++ )
		{
			IdEntry * itr_existing = static_cast<IdEntry*>( existing->item( i ) );
			if ( itr_existing->id_ == id )
			{
				existing->takeItem( existing->row( itr_existing ) );
				mine->addItem( itr_existing );
				break;
			}
		}
	}
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
DNAEditorDlg::DNAEditorDlg					( MW * parent, World * w, DNA & dna ) :
	QDialog(parent), MemTrack(),
	w_( w ), dna_( dna )
{
	APRDBG_CDTOR;
	init();
	if ( dna.isValid() && w_->isIDAssigned( dna.kind() ) )
	{
		setWindowTitle( tr( "Edit kind id %1" ).arg( dna.kind() ) );
		ui.le_name->setText( w_->nameForId( dna.kind() ) );
		ui.sp_age->setValue( dna.age() );
		ui.sp_cost->setValue( dna.cost() );
		ui.sp_energy->setValue( dna.energy() );
		
		addIdList( dna.sensors(), ui.ls_sens_other, ui.ls_sens_part );
		addIdList( dna.reflexes(), ui.ls_refl_other, ui.ls_refl_part );
		addIdList( dna.brains(), ui.ls_brains_other, ui.ls_brains_part );
		addIdList( dna.actuators(), ui.ls_ak_others, ui.ls_ak_part );
		
	}
	else
	{
		setWindowTitle( tr( "Create a new kind" ) );
	}
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void				DNAEditorDlg::init		( void )
{
	Q_ASSERT( w_ != NULL );
	
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
	connect( ui.b_sens_add, SIGNAL( clicked() ),
			 this, SLOT( addSensor() ) );
	connect( ui.b_sens_rem, SIGNAL( clicked() ),
			 this, SLOT( remSensor() ) );
	
	/* load all components types */
	{
		const QMap<ID,SensorFactory*> & sf = w_->sensorFactories();
		QMap<ID,SensorFactory*>::ConstIterator itr = sf.constBegin();
		QMap<ID,SensorFactory*>::ConstIterator itr_e = sf.constEnd();
		while ( itr != itr_e )
		{
			IdEntry * ide = 
					new IdEntry( 
						itr.key(),
						w_->nameForId( itr.key() ), 
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
						w_->nameForId( itr.key() ), 
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
						w_->nameForId( itr.key() ), 
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
						w_->nameForId( itr.key() ), 
						itr.value()->factoryName() );
			ui.ls_ak_others->addItem( ide );
			itr++;
		}
	}
	ui.tabWidget->setCurrentIndex( 0 );
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
static void		moveLeft		( QListWidget * src, QListWidget * dst )
{
	QList<QListWidgetItem*> itl = src->selectedItems();
	if ( itl.count() == 0 )
	{
		QMessageBox::warning(
					qApp->activeWindow(), QObject::tr( "Failed to add" ),
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
static void		moveRight		( QListWidget * dst, QListWidget * src )
{
	QList<QListWidgetItem*> itl = src->selectedItems();
	if ( itl.count() == 0 )
	{
		QMessageBox::warning(
					qApp->activeWindow(), QObject::tr( "Failed to add" ),
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
QString					DNAEditorDlg::getName			( ID & id_for_name )
{
	QString s_name = ui.le_name->text();
	if ( s_name.isEmpty() )
	{
		QMessageBox::warning(
					this, QObject::tr( "Failed to create" ),
					QObject::tr( 
						"There is no name assigned to the kind.\n"
						"Please type a name.\n\n"
						),
					QMessageBox::Ok );
		ui.tabWidget->setCurrentIndex( TabGeneral );
		ui.le_name->setFocus();
	}
	id_for_name = w_->idValue( s_name );
	return s_name;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void					DNAEditorDlg::componentsToDNA	( DNA & dna )
{
	/* add things to this kind */
	int i_max;
	
	/// @cond internal
#	define	loadComponentX(uicmp,X)	\
	i_max = ui.ls_##uicmp##_part->count(); \
	for ( int i = 0; i < i_max; i++ ) { \
	IdEntry * ide = static_cast<IdEntry*>( ui.ls_##uicmp##_part->item( i ) ); \
	dna.add##X( ide->id_ ); \
}
	
	loadComponentX(sens,Sensor);
	loadComponentX(refl,Reflex);
	loadComponentX(brains,Brain);
	loadComponentX(ak,Actuator);
	
#	undef	loadComponentX
	/// @endcond
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void					DNAEditorDlg::validateNew		( 
		DNA::InitData & init_d )
{
	
	ID other_id;
	QString s_name = getName( other_id );
	if ( s_name.isEmpty() )
		return;
	if ( other_id != InvalidId )
	{
		QMessageBox::warning(
					this, QObject::tr( "Failed to create" ),
					QObject::tr( 
						"ID name %1 is already assigned to id %2.\n"
						"Please choose a different one.\n\n"
						).arg( s_name ).arg( other_id ),
					QMessageBox::Ok );
		ui.tabWidget->setCurrentIndex( TabGeneral );
		ui.le_name->setFocus();
		ui.le_name->selectAll();
		return;
	}
	init_d.kind_ = w_->addNewId( s_name );
	
	/* create this kind */
	GenericActorFactory * gf = GenericActorFactory::findMyself( w_ );
	Q_ASSERT( gf != NULL );
	gf->addNewKind( init_d );
	bool b = w_->addActorFactory( gf, init_d.kind_ );
	Q_ASSERT(b);
	Q_UNUSED(b);
	DEC_REF(gf,gf);
	
	/* get the DNA that we've created */
	DNA & dna = gf->dna( init_d.kind_ );
	Q_ASSERT( dna.isValid() );
	
	componentsToDNA( dna );
	
	accept();
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void					DNAEditorDlg::validateEdit		( 
		DNA::InitData & init_d )
{
	ID other_id;
	QString s_name = getName( other_id );
	if ( s_name.isEmpty() )
		return;
	init_d.kind_ = dna_.kind();
	if ( other_id != dna_.kind() )
	{
		QMessageBox::warning(
					this, QObject::tr( "Failed to create" ),
					QObject::tr( 
						"ID name %1 is already assigned to id %2.\n"
						"Please choose a different one.\n\n"
						).arg( s_name ).arg( other_id ),
					QMessageBox::Ok );
		return;
	}
	
	/* change the name of the ID */
	w_->insertId( init_d.kind_, s_name );
	
	/* create ghost dna to use in copy process */
	DNA dna_new;
	dna_new.initDNA( init_d );
	componentsToDNA( dna_new );
	dna_.reinitDNA( dna_new, false );
	accept();
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void					DNAEditorDlg::validate			( void )
{
	DNA::InitData init_d;
	init_d.kind_ = InvalidId;
	init_d.cost_ = ui.sp_cost->value();
	Q_ASSERT( init_d.cost_ > 0 );
	init_d.age_ = ui.sp_age->value();
	Q_ASSERT( init_d.age_ > 0 );
	init_d.energy_ = ui.sp_energy->value();
	Q_ASSERT( init_d.energy_ > 0 );

	if ( dna_.isValid() )
	{
		validateEdit( init_d );
	}
	else
	{
		validateNew( init_d );
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







