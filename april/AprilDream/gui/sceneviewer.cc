/* ========================================================================= */
/* ------------------------------------------------------------------------- */
/*!
  \file			sceneviewer.cc
  \date			Apr 2013
  \author		TNick

  \brief		Contains the implementation of SceneViewer class


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

#include	"sceneviewer.h"
#include	<QMouseEvent>
#include	<QTimeLine>


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
SceneViewer::SceneViewer	( QWidget * parent )
	: QGraphicsView( parent ), MemTrack(),
	num_scheduled_scalings_( 0 )
{
	APRDBG_CDTOR;
	
/*
	setRenderHints( QPainter::Antialiasing | QPainter::SmoothPixmapTransform );
	setCacheMode( QGraphicsView::CacheBackground );
*/
	setResizeAnchor( QGraphicsView::AnchorUnderMouse );
	setDragMode( QGraphicsView::RubberBandDrag );
	
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
SceneViewer::~SceneViewer	( void )
{
	APRDBG_CDTOR;
	/* stub */
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void				SceneViewer::mousePressEvent		( QMouseEvent * me )
{
	if ( me->button() == Qt::MiddleButton )
	{
		setDragMode( QGraphicsView::ScrollHandDrag );
		QMouseEvent	mev( me->type(), me->pos(), me->globalPos(),
						 Qt::LeftButton, Qt::LeftButton, Qt::NoModifier );
		QGraphicsView::mousePressEvent( &mev );
		return;
	}
	QGraphicsView::mousePressEvent( me );
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void				SceneViewer::mouseReleaseEvent		( QMouseEvent * me )
{
	if ( dragMode() == QGraphicsView::ScrollHandDrag )
	{
		setDragMode( QGraphicsView::NoDrag );
	}
	QGraphicsView::mouseReleaseEvent( me );
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void				SceneViewer::mouseMoveEvent			( QMouseEvent * me )
{
	QGraphicsView::mouseMoveEvent( me );
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void				SceneViewer::wheelEvent				( QWheelEvent * event )
{
	int numDegrees = event->delta() / 8;
	int numSteps = numDegrees / 15;  // see QWheelEvent documentation
	num_scheduled_scalings_ += numSteps;
	// if user moved the wheel in another direction, we reset previously scheduled scalings
	if (num_scheduled_scalings_ * numSteps < 0 )
		num_scheduled_scalings_ = numSteps;

	QTimeLine * anim = new QTimeLine(300, this);
	anim->setUpdateInterval(10);
	anim->setCurveShape( QTimeLine::EaseOutCurve );
	connect( anim, SIGNAL(valueChanged(qreal) ),
			this, SLOT(scalingTime(qreal)) );
	connect( anim, SIGNAL(finished() ),
			this, SLOT(animFinished()) );
	anim->start();
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void				SceneViewer::scalingTime			( qreal x )
{
	Q_UNUSED( x );
	qreal factor = 1.0 + qreal( num_scheduled_scalings_ ) / 1000.0;
	scale( factor, factor );
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void				SceneViewer::animFinished	( void )
{
	if (num_scheduled_scalings_ > 0)
		num_scheduled_scalings_--;
	else
		num_scheduled_scalings_++;
	sender()->~QObject();
}
/* ========================================================================= */

/*  CLASS    =============================================================== */
//
//
//
//
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
