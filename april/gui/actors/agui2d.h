/* ========================================================================= */
/* ------------------------------------------------------------------------- */
/*!
  \file			agui2d.h
  \date			Apr 2013
  \author		TNick

  \brief		Contains the definition for AGui2D class


*//*


 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Please read COPYING and README files in root folder
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
#ifndef __AGUI2D_INC__
#define __AGUI2D_INC__
//
//
//
//
/*  INCLUDES    ------------------------------------------------------------ */

#include    <april/april.h>
#include    <april/gui/actors/agui.h>
#include    <QPoint>
#include    <QPointF>
#include    <QRect>
#include    <QRectF>
#include    <april/gui/geometry/abox2d.h>

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
*	@brief
*/
class
	APRILSHARED_EXPORT
	AGui2D		: public AGui		{
	BBM_TRACK( AGui2D );

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

	//! the position of the origin point on x axis
	COORDV			x_;
	//! the position of the origin point on y axis
	COORDV			y_;
	
	//! bounding box relative to origin point - x
	COORDV			b_x_;
	//! bounding box relative to origin point - y
	COORDV			b_y_;
	//! bounding box relative to origin point - width
	COORDV			b_w_;
	//! bounding box relative to origin point - height
	COORDV			b_h_;
	

	/*  DATA    ============================================================ */
	//
	//
	//
	//
	/*  FUNCTIONS    ------------------------------------------------------- */

public:


	/**
	*	@brief	constructor;
	*/
	AGui2D				( World * w );

protected:

	/**
	*	@brief	destructor;
	*/
	virtual				~AGui2D			( void );

	//! the position of the origin point on x axis
	inline COORDV		originX			( void ) const
	{ return x_; }
	
	//! the position of the origin point on y axis
	inline COORDV		originY			( void ) const
	{ return y_; }
	
	//! bounding box relative to origin point - x
	inline COORDV		boundingX		( void ) const
	{ return b_x_; }
	
	//! bounding box relative to origin point - y
	inline COORDV		boundingY		( void ) const
	{ return b_y_; }
	
	//! bounding box relative to origin point - width
	inline COORDV		boundingWidth	( void ) const
	{ return b_w_; }
	
	//! bounding box relative to origin point - height
	inline COORDV		boundingHeight	( void ) const
	{ return b_h_; }

	//! position as QPoint
	inline QPoint		originPos		( void ) const
	{ return QPoint( x_, y_ ); }

	//! position as QPointF
	inline QPointF		originPosF		( void ) const
	{ return QPointF( x_, y_ ); }

	//! bounding box as QRect
	inline QRect		boundRect		( void ) const
	{ return QRect( b_x_, b_y_, b_w_, b_h_ ); }

	//! position as QPointF
	inline QRectF		boundRectF		( void ) const
	{ return QRectF( b_x_, b_y_, b_w_, b_h_ ); }

	//! tell if the bounding box of this item intersects the others
	bool				intersect		( const AGui2D & other );

	/*  FUNCTIONS    ======================================================= */
	//
	//
	//
	//

};	/*	class AGui2D	*/

/*  CLASS    =============================================================== */
//
//
//
//

}   //  namespace Gui

}   //  namespace april

#endif // __AGUI2D_INC__
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
