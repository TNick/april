/* ========================================================================= */
/* ------------------------------------------------------------------------- */
/*!
  \file			sceneviewer.h
  \date			Apr 2013
  \author		TNick

  \brief		Contains the definition for SceneViewer class


*//*


 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Please read COPYING and README files in root folder
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
#ifndef __SCENEVIEWER_INC__
#define __SCENEVIEWER_INC__
//
//
//
//
/*  INCLUDES    ------------------------------------------------------------ */

#include    <april/april.h>
#include    <QGraphicsView>

/*  INCLUDES    ============================================================ */
//
//
//
//
/*  DEFINITIONS    --------------------------------------------------------- */

namespace	april	{

namespace	Gui		{

/*  DEFINITIONS    ========================================================= */
//
//
//
//
/*  CLASS    --------------------------------------------------------------- */

/**
*	@brief	An enhanced scene viewer based on QGraphicsView
*/
class SceneViewer		: public QGraphicsView, public MemTrack		{
	Q_OBJECT
	BBM_TRACK( SceneViewer );

	//
	//
	//
	//
	/*  DEFINITIONS    ----------------------------------------------------- */

	/*  DEFINITIONS    ===================================================== */
	//
	//
	//
	//
	/*  DATA    ------------------------------------------------------------ */

private:

	//! zoom helper
	int			num_scheduled_scalings_;

	/*  DATA    ============================================================ */
	//
	//
	//
	//
	/*  FUNCTIONS    ------------------------------------------------------- */

public:

	//! constructor;
	SceneViewer			( QWidget * parent = NULL );

	//! destructor;
	virtual				~SceneViewer		( void );

protected:

	//! zooming using this one
	void		wheelEvent				( QWheelEvent *event );

	//! mouse press
	void		mousePressEvent			( QMouseEvent * me );

	//! mouse release
	void		mouseReleaseEvent		( QMouseEvent * me );

	//! mouse move
	void		mouseMoveEvent			( QMouseEvent * me );

private slots:

	//! zooming utility
	void		scalingTime				( qreal x );

	//! zooming utility
	void		animFinished			( void );


	/*  FUNCTIONS    ======================================================= */
	//
	//
	//
	//

};	/*	class SceneViewer	*/

/*  CLASS    =============================================================== */
//
//
//
//

}   //  namespace   april

}   //  namespace   Gui

#endif // __SCENEVIEWER_INC__
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
