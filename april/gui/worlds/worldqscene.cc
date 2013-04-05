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

/*  INCLUDES    ============================================================ */
//
//
//
//
/*  DEFINITIONS    --------------------------------------------------------- */

using namespace april;
using namespace april::Gui;

class	WQS_Unit		: public QGraphicsItem	{
	
	int		scale = 100;
public:
	
	WQS_Unit() : QGraphicsItem()
	{}
	
	QRectF						boundingRect		( void ) const
	{
		int		scale_16 = scale/16;
		qreal penWidth = 1;
		return QRectF(-scale_16 - penWidth / 2, -scale_16 - penWidth / 2,
					  scale+scale_16 + penWidth, scale+scale_16 + penWidth);
	}
	
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
	  w_( new World( "AprilDream", 100000 ) )
{
	APRDBG_CDTOR;
	
	setItemIndexMethod( QGraphicsScene::NoIndex );

	OWN_CREF( w_, this );

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
