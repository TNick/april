/* ========================================================================= */
/* ------------------------------------------------------------------------- */
/*!
  \file			abox2d.h
  \date			Apr 2012
  \author		TNick

  \brief		Contains the definition for ABOX2D class


*//*


 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Please read COPYING and README files in root folder
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
#ifndef __ABOX2D_INC__
#define __ABOX2D_INC__
//
//
//
//
/*  INCLUDES    ------------------------------------------------------------ */

#include	"p2d.h"

/*  INCLUDES    ============================================================ */
//
//
//
//
/*  CLASS    --------------------------------------------------------------- */

/**
*	@brief	Represents a rectangle that is aligned with the axis
*
*	The line isDegenerate() if the two points that define it
*	are identical ( P2D::isEqual() == true )
*/
struct ABOX2D				{

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

	union	{
		/**
		*	@brief	coordinates in an array of 4 values: left, bottom, right, top
		*/
		COORDV		pts_[4];


		struct		{


			/**
			*	@brief	X1 component
			*/
			COORDV		left_;


			/**
			*	@brief	Y1 component
			*/
			COORDV		bottom_;


			/**
			*	@brief	X2 component
			*/
			COORDV		right_;


			/**
			*	@brief	Y2 component
			*/
			COORDV		top_;

		};


		struct		{


			/**
			*	@brief	first point
			*/
			P2D			bottom_left_;


			/**
			*	@brief	second point
			*/
			P2D			top_right_;

		};

	};
	/*  DATA    ============================================================ */
	//
	//
	//
	//
	/*  FUNCTIONS    ------------------------------------------------------- */

public:

	/**
	*	@brief	bring the internal variables to their ground state
	*/
	inline void			reset					( void )
	{ bottom_left_.reset(); top_right_.reset(); }


	/**
	*	@brief	compares two rectangles
	*
	*	Two rectangles are the same if their coordinates are the same
	*/
	inline bool operator ==						( const ABOX2D & other ) const
	{
		return ( ( COORDV_EQ( pts_[0], other.pts_[0] ) ) &&
				 ( COORDV_EQ( pts_[1], other.pts_[1] ) ) &&
				 ( COORDV_EQ( pts_[2], other.pts_[2] ) ) &&
				 ( COORDV_EQ( pts_[3], other.pts_[3] ) )
				 );
	}


	/**
	*	@brief	compares two points (their coorsinates)
	*/
	inline bool operator !=						( const ABOX2D & other ) const
	{
		return !( *this == other );
	}


	/**
	*	@brief	computes the bounding rectangle for the two input boxes
	*/
	inline void operator +=						( const ABOX2D & other )
	{
		unite( other );
	}


	/**
	*	@brief	computes the rectangle that is common to the two input boxes
	*/
	inline void operator -=						( const ABOX2D & other )
	{
		intersect( other );
	}


	/**
	*	@brief	width (side on the x axis)
	*/
	inline COORDV		width					( void ) const
	{ return right_ - left_; }


	/**
	*	@brief	height (side on the y axis)
	*/
	inline COORDV		height					( void ) const
	{ return top_ - bottom_; }


	/**
	*	@brief	tell if this box is degenerate or not
	*
	*	The box is degenerate if any of the width() or height() are
	*	zero or negative
	*/
	inline bool			isDegenerate			( void ) const
	{ return ( ( width() > 0 ) && ( height() > 0 ) ); }


	/**
	*	@brief	lenght of diagonal
	*/
	inline COORDV		diagonal				( void ) const
	{ return width() * height(); }


	/**
	*	@brief	set this rectangle to the union of two rectangles
	*/
	void				unite					(
			const ABOX2D &			first,
			const ABOX2D &			second
			);


	/**
	*	@brief	set this rectangle to the union of this and other rectangle
	*/
	void				unite					(
			const ABOX2D &			other
			);


	/**
	*	@brief	tell if the box contains a point
	*
	*	If the point is directly over left or bottom margin the method returns
	*	true; if the point is directly over right or top margin the method
	*	returns false.
	*/
	bool				contains				(
			const P2D &				other
			) const;


	/**
	*	@brief	tell if the box contains another box
	*
	*	Only returns true if the other box is fully contained by this box.
	*	Identical rectangles return true with this method.
	*/
	bool				contains				(
			const ABOX2D &			other
			) const;


	/**
	*	@brief	set this rectangle to the intersection of two rectangles
	*
	*	@return	true if the rectangles intersect and false if they do not
	*/
	bool				intersect				(
			const ABOX2D &			first,
			const ABOX2D &			second
			);


	/**
	*	@brief	set this rectangle to the intersection of this and
	*	other rectangle
	*
	*	@return	true if the rectangles intersect and false if they do not
	*/
	bool				intersect				(
			const ABOX2D &			other
			);

	/**
	*	@brief	tell if the rectangle is normalised (x1<x2, y1<y2)
	*/
	inline bool		isNormalised			( void ) const
	{ return ( ( left_ <= right_ ) && ( bottom_ <= top_ ) ); }


	/**
	*	@brief	normalise the rectangle (x1<x2, y1<y2)
	*/
	void			normalise				( void );

	/**
	*	@brief	extend or contract this box by given ammount
	*
	*	A positive value will expand the box; a negative value will shrink it
	*/
	void			offset					( COORDV dist );


	/**
	*	@brief	extend or contract the box by given ammount
	*
	*	A positive value will expand the box; a negative value will shrink it
	*/
	void			offset					( COORDV dist, ABOX2D & out ) const;


	/**
	*	@brief	move the item by this ammount relative to current position
	*/
	void				translate			(
			COORDV			dx,
			COORDV			dy
			)
	{
		left_ += dx;
		bottom_ += dy;
		right_ += dx;
		top_ += dy;
	}


	/**
	*	@brief	tell if the segment is "visible" inside given shape
	*
	*	"visible" is satisfied if the shape intersects or contains the segment.
	*/
	bool				visibleIn			(
			const ABOX2D &		other
			) const;


	/**
	*	@brief	the area of this thing
	*/
	inline COORDV		area				( void )
	{ return width() * height(); }


	/**
	*	@brief	the center point of this one
	*/
	inline void			center				( P2D & c )
	{
		c.x_ = ( left_ + right_ ) / 2;
		c.y_ = ( bottom_ + top_ ) / 2;
	}


	/*  FUNCTIONS    ======================================================= */
	//
	//
	//
	//

};	/*	class ABOX2D	*/

/*  CLASS    =============================================================== */
//
//
//
//
#endif // __ABOX2D_INC__
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
