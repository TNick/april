/* ========================================================================= */
/* ------------------------------------------------------------------------- */
/*!
  \file			p2d.h
  \date			Apr 2012
  \author		TNick

  \brief		Contains the definition for P2D class


*//*


 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Please read COPYING and README files in root folder
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
#ifndef __P2D_INC__
#define __P2D_INC__
//
//
//
//
/*  INCLUDES    ------------------------------------------------------------ */

#include	"geometry.h"

/*  INCLUDES    ============================================================ */
//
//
//
//
/*  CLASS    --------------------------------------------------------------- */

/**
*	@brief	a point in 2D space
*
*
@code
								Y ^
								  | 2*PI
								  |
								  |
								  |
							  y_  |----   x  P( x_, y_ )
								  |      /
								  |     /
								  |    /
					  II          |   /        I
								  |  /
								  | /      |
	 PI                           |/       | x_
	 -------------------------------------------------------------- >
								  | (0, 0)                          X
								  |
								  |
					  III         |            IV
								  |
								  |
								  |
								  |
								  |
								  |
								  |
						   3*PI/2 |
@endcode

		The base coodrinate system. All calculations are performed
	in this system, with counter-clockwise angles being positive.
		sin(< X0P) = y_ / r()
		cos(< X0P) = x_ / r()
		tan(< X0P) = y_ / x_
		ctg(< X0P) = x_ / y_


*/
struct	P2D				{

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
		*	@brief	coordinates in an array of 2 values: X and Y
		*/
		COORDV		pts_[2];


		struct	{


			/**
			*	@brief	X component
			*/
			COORDV		x_;


			/**
			*	@brief	Y component
			*/
			COORDV		y_;
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
	inline void			reset		( void )
	{ x_ = 0; y_ = 0; }


	/**
	*	@brief	compares two points (their coordinates)
	*/
	inline bool operator ==			( const P2D & other ) const
	{
		//		qDebug() << qAbs( x_ - other.x_ );
		//		qDebug() << qAbs( y_ - other.y_ );
		return ( ( COORDV_EQ( x_, other.x_ ) ) &&
				 ( COORDV_EQ( y_, other.y_ ) ) );
	}


	/**
	*	@brief	compares two points (their coorsinates)
	*/
	inline bool operator !=			( const P2D & other ) const
	{
		return !( *this == other );
	}


	/**
	*	@brief	adds the coordinates of the two points together
	*/
	inline void operator +=			( const P2D & other )
	{
		x_ += other.x_;
		y_ += other.y_;
	}


	/**
	*	@brief	adds the coordinates of the two points together
	*/
	inline void operator -=			( const P2D & other )
	{
		x_ -= other.x_;
		y_ -= other.y_;
	}


	/**
	*	@brief	the distance from point (0,0) to our point
	*/
	inline COORDV		r			( void )const
	{
		return COORDV_SQR( x_ * x_ + y_ * y_ ); }


	/**
	*	@brief	the distance from a point to our point
	*/
	inline COORDV		dist		( const P2D & other ) const
	{
		COORDV dx = other.x_ - x_;
		COORDV dy = other.y_ - y_;
		return COORDV_SQR( dx * dx + dy * dy );
	}


	/**
	*	@brief	the distance from origin to our point
	*/
	inline COORDV		magnitude		( void ) const
	{
		return COORDV_SQR( x_ * x_ + y_ * y_ );
	}


	/**
	*	@brief	the distance from a point to our point, squared
	*/
	inline COORDV		distSq		( const P2D & other ) const
	{
		COORDV dx = other.x_ - x_;
		COORDV dy = other.y_ - y_;
		return dx * dx + dy * dy;
	}

	/**
	*	@brief	move the item by this ammount relative to current position
	*/
	void				translate			(
			COORDV			dx,
			COORDV			dy
			)
	{ x_ += dx; y_ += dy; }


	/*  FUNCTIONS    ======================================================= */
	//
	//
	//
	//

};	/*	struct P2D	*/

/**
*	@brief	adds the coordinates of the two points together
*/
inline P2D operator +			( const P2D & first, const P2D & second )
{
	P2D	res;
	res.x_ = first.x_ + second.x_;
	res.y_ = first.y_ + second.y_;
	return res;
}

/**
*	@brief	extracts the coordinates of the second point from first point
*/
inline P2D operator -			( const P2D & first, const P2D & second )
{
	P2D	res;
	res.x_ = second.x_ - first.x_;
	res.y_ = second.y_ - first.y_;
	return res;
}


/*  CLASS    =============================================================== */
//
//
//
//
#endif // __P2D_INC__
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
