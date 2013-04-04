/* ========================================================================= */
/* ------------------------------------------------------------------------- */
/*!
  \file			dockcrtsel.cc
  \date			Apr 2013
  \author		TNick
  
  \brief		Contains the implementation of DockCrtSel class
  
  
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

#include	"dockcrtsel.h"
#include	<april/AprilDream/propertybrowser/qtpropertybrowser.h>
#include	<april/AprilDream/propertybrowser/qttreepropertybrowser.h>
#include	<april/AprilDream/propertybrowser/qtpropertymanager.h>
#include	<april/AprilDream/propertybrowser/qteditorfactory.h>

/*  INCLUDES    ============================================================ */
//
//
//
//
/*  DEFINITIONS    --------------------------------------------------------- */

using namespace april;
using namespace april::Gui;

namespace   april	{

namespace	Gui		{

	//! index in the list of properties for the world
	enum	WorldProps	{
		WEnergy = 0,
		WEnergyBound,
		
		WFreq,
		WInterval,
		
		/* all below this line are read-only */
		WTime,
		WActors,
		WEvents,
		WEventsFact,
		WActorsFact,
		WActFact,
		WSensFact,
		WBrainFact,
		
		WMax,
		WFirstReadOnly = WTime
	};
	
	
class	DockCrtSel_p		{
public:

	//! property browser
	QtTreePropertyBrowser *		tree_;

	//!@{
	//! managers for properties
	QtBoolPropertyManager *		boolManager; 
	QtIntPropertyManager *		intManager; 
	QtStringPropertyManager *	stringManager;
	//	QtSizePropertyManager *		sizeManager; 
	//	QtRectPropertyManager *		rectManager;
	//	QtSizePolicyPropertyManager *sizePolicyManager;
	//	QtEnumPropertyManager *		enumManager;
	//	QtGroupPropertyManager *	groupManager;
	//!@}

	QtCheckBoxFactory *			checkBoxFactory;
	QtSpinBoxFactory *			spinBoxFactory;
	QtLineEditFactory *			lineEditFactory;
	//	QtSliderFactory *			sliderFactory;
	//	QtScrollBarFactory *		scrollBarFactory;
	//	QtEnumEditorFactory *		comboBoxFactory;
	

	//! array of properties
	QtProperty *				props_[WMax];
	
};

}   //  namespace   Gui

}   //  namespace   april

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
DockCrtSel::DockCrtSel	( MW * mw )
	: Dock( mw, "Current selection" )
{
	APRDBG_CDTOR;
	/* stub */
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
DockCrtSel::~DockCrtSel	( void )
{
	APRDBG_CDTOR;
	if ( d_ != NULL )
	{
		deconstruct();
	}
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void				DockCrtSel::construct			( void )
{
	if ( d_ != NULL )
	{
		deconstruct();
	}
	d_ = new DockCrtSel_p();
	
	d_->tree_ = new QtTreePropertyBrowser( dock() );
	dock()->setWidget( d_->tree_ );
	
	d_->boolManager = 
			new QtBoolPropertyManager(this);
	d_->intManager = 
			new QtIntPropertyManager(this);
	d_->stringManager =
			new QtStringPropertyManager(this);
	//	d_->sizeManager = 
	//			new QtSizePropertyManager(this);
	//	d_->rectManager =
	//			new QtRectPropertyManager(this);
	//	d_->sizePolicyManager =
	//			new QtSizePolicyPropertyManager(this);
	//	d_->enumManager =
	//			new QtEnumPropertyManager(this);
	//	d_->groupManager =
	//			new QtGroupPropertyManager(this);
	
	d_->checkBoxFactory = 
			new QtCheckBoxFactory( this );
	d_->spinBoxFactory = 
			new QtSpinBoxFactory( this );
	d_->lineEditFactory = 
			new QtLineEditFactory( this );
	//	d_->sliderFactory = 
	//			new QtSliderFactory( this );
	//	d_->scrollBarFactory =
	//			new QtScrollBarFactory( this );
	//	d_->comboBoxFactory = 
	//			new QtEnumEditorFactory( this );
	
	d_->tree_->setFactoryForManager(
				d_->boolManager, d_->checkBoxFactory);
	d_->tree_->setFactoryForManager(
				d_->intManager, d_->spinBoxFactory);
	d_->tree_->setFactoryForManager(
				d_->stringManager, d_->lineEditFactory);
	//	d_->tree_->setFactoryForManager(
	//				sizeManager->subIntPropertyManager(), spinBoxFactory);
	//	d_->tree_->setFactoryForManager(
	//				rectManager->subIntPropertyManager(), spinBoxFactory);
	//	d_->tree_->setFactoryForManager(
	//				sizePolicyManager->subIntPropertyManager(), spinBoxFactory);
	//	d_->tree_->setFactoryForManager(
	//				sizePolicyManager->subEnumPropertyManager(), comboBoxFactory);
	//	d_->tree_->setFactoryForManager(
	//				enumManager, comboBoxFactory);
	

	DOCK_ADD_IPROP_B(WEnergy,"energy",10,10000000);
	DOCK_ADD_IPROP(WEnergyBound,"bound energy");
	DOCK_ADD_IPROP_B(WFreq,"update frequency",1,10000);
	DOCK_ADD_IPROP_B(WInterval,"gui interval",1,1000);
	DOCK_ADD_IPROP(WTime,"world time");
	DOCK_ADD_IPROP(WActors,"actors");
	DOCK_ADD_IPROP(WEvents,"events");
	DOCK_ADD_IPROP(WEventsFact,"event fact.");
	DOCK_ADD_IPROP(WActorsFact,"actors fact.");
	DOCK_ADD_IPROP(WActFact,"actuators fact.");
	DOCK_ADD_IPROP(WSensFact,"sensors fact.");
	DOCK_ADD_IPROP(WBrainFact,"brain fact.");

}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void				DockCrtSel::deconstruct			( void )
{

	d_->tree_->deleteLater();
	
	d_->boolManager->deleteLater(); 
	d_->intManager->deleteLater(); 
	d_->stringManager->deleteLater();
	//	d_->sizeManager->deleteLater(); 
	//	d_->rectManager->deleteLater();
	//	d_->sizePolicyManager->deleteLater();
	//	d_->enumManager->deleteLater();
	//	d_->groupManager->deleteLater();
	
	d_->checkBoxFactory->deleteLater();
	d_->spinBoxFactory->deleteLater();
	d_->lineEditFactory->deleteLater();
	//	d_->sliderFactory->deleteLater();
	//	d_->scrollBarFactory->deleteLater();
	//	d_->comboBoxFactory->deleteLater();
	
	for ( int i = 0; i < WMax; i++ )
	{
		delete d_->props_[i];
	}
	
	delete d_;
	d_ = NULL;
}
/* ========================================================================= */

/*  CLASS    =============================================================== */
//
//
//
//
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
