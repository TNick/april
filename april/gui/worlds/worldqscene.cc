/* ========================================================================= */
/* ------------------------------------------------------------------------- */
/*!
  \file			worldqscene.cc
  \date			Apr 2013
  \author		TNick
  
  \brief		Contains the implementation of WorldQScene class
  
  
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

#include	"worldqscene.h"
#include	<QGraphicsItem>
#include	<QPainter>
#include	<QDebug>
#include	<QFileDialog>
#include	<QApplication>
#include	<april/aprillibrary.h>

/*  INCLUDES    ============================================================ */
//
//
//
//
/*  DEFINITIONS    --------------------------------------------------------- */

using namespace april;
using namespace april::Gui;

//! Item for scene that represents the origin and axis directions
class	WQS_Unit		: public QGraphicsItem	{
	
	int		scale;
public:
	
	//! constructor
	WQS_Unit() : QGraphicsItem(), scale(100)
	{}
	
	//! the rectangle that contains our item
	QRectF						boundingRect		( void ) const
	{
		int		scale_16 = scale/16;
		qreal penWidth = 1;
		return QRectF(-scale_16 - penWidth / 2, -scale_16 - penWidth / 2,
					  scale+scale_16 + penWidth, scale+scale_16 + penWidth);
	}
	
	//! paint our item
	void						paint				(
			QPainter *							painter, 
			const QStyleOptionGraphicsItem *	option,
			QWidget *							widget)
	{
		Q_UNUSED( option );
		Q_UNUSED( widget );
		
		int		scale_12_16 = 12*scale/16;
		int		scale_16 = scale/16;
		
		painter->drawLine( 0, 0, 0, scale_12_16 );
		painter->drawLine( 0, scale, -scale_16, scale_12_16 );
		painter->drawLine( -scale_16, scale_12_16, scale_16, scale_12_16 );
		painter->drawLine( 0, scale, scale_16, scale_12_16 );
		
		painter->drawLine( 0, 0, scale_12_16, 0 );
		painter->drawLine( scale, 0, scale_12_16, -scale_16 );
		painter->drawLine( scale_12_16, -scale_16, scale_12_16, scale_16 );
		painter->drawLine( scale, 0, scale_12_16, scale_16 );
		
		painter->drawText( scale, -scale_16, "X");
		painter->drawText( scale_16, scale, "Y");
		
	}
	
};

//! the initial width and height
#define INIT_SCENE_RECT		1200

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
WorldQScene::WorldQScene	( QObject * parent )
	: QGraphicsScene( parent ), MemTrack(),
	  w_( NULL )
{
	APRDBG_CDTOR;
	
	setItemIndexMethod( QGraphicsScene::NoIndex );

	/** @todo switch for showing this */
	WQS_Unit * origin = new WQS_Unit();
	addItem( origin );
	
	origin->setPos( 0, 0 );
	origin->setFlags( 0 );
	
	setSceneRect( 
				-INIT_SCENE_RECT, -INIT_SCENE_RECT, 
				INIT_SCENE_RECT*2, INIT_SCENE_RECT*2 );
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
WorldQScene::~WorldQScene	( void )
{
	APRDBG_CDTOR;
	if ( w_ != NULL )
	{
		DEC_REF( w_, this );
		AprilLibrary::remWorld( w_ );
	}
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool				WorldQScene::openWorld			(
		const QString & s_file, QString & s_err )
{
	World * w = World::fromStg( s_file, s_err );
	if ( w == NULL )
		return false;
	if ( loadWorld( w, s_err ) == false )
	{
		DEC_REF( w_, this );
		AprilLibrary::remWorld( w );
		return false;
	}
	else
	{
		OWN_CREF(w_,this);
		w_->setAssociatedFile( s_file );
		return true;
	}
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool				WorldQScene::closeWorld			( QString & s_err )
{
	if ( hasWorld() == false )
		return true;
	if ( w_->isRunning() )
	{
		s_err = QObject::tr( "Current world can't be closed because is running." );
		return false;
	}
	DEC_REF(w_,this);
	AprilLibrary::remWorld( w_ );
	w_ = NULL;
	return true;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool				WorldQScene::loadWorld			( World * w, QString & s_err  )
{
	if ( closeWorld( s_err ) )
	{
		w_ = w;
		if ( w_ != NULL )
		{
			INC_REF(w_,this);
		}
		w_->setAssociatedFile( QString() );
		return true;
	}
	else
	{
		return false;
	}
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool				WorldQScene::save				( QString & s_err )
{
	if ( hasWorld() == false )
	{
		s_err = QObject::tr( "No world is loaded." );
		return false;
	}
	if ( w_->isRunning() )
	{
		s_err = QObject::tr( "World ca't be saved while running." );
		return false;
	}
	
	if ( w_->hasAssociatedFile() == false )
		return saveAs( s_err );
	return w_->saveAsStg( w_->associatedFile(), s_err );
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool				WorldQScene::saveAs				( QString & s_err )
{
	if ( hasWorld() == false )
	{
		s_err = QObject::tr( "No world is loaded." );
		return false;
	}
	if ( w_->isRunning() )
	{
		s_err = QObject::tr( "World ca't be saved while running." );
		return false;
	}
	
	QString fileName = QFileDialog::getSaveFileName(
				qApp->activeWindow(),
				tr( "Where to save the world:" ),
				w_->associatedFile()
				);
	if ( !fileName.isEmpty() )
	{
		if ( w_->saveAsStg( fileName, s_err ) )
		{
			w_->setAssociatedFile( fileName );
			return true;
		}
	}
	return false;
}
/* ========================================================================= */

/*  CLASS    =============================================================== */
//
//
//
//
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
