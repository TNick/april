/* ========================================================================= */
/* ------------------------------------------------------------------------- */
/*!
  \file			p3d.h
  \date			Apr 2012
  \author		TNick

  \brief		Contains the definition for P3D class


*//*


 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Please read COPYING and README files in root folder
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
#ifndef __P3D_INC__
#define __P3D_INC__
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
*	@brief	a point in 3D space
*/
struct P3D				{

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
		*	@brief	coordinates in an array of 3 values: X, Y and Z
		*/
		COORDV		pts_[3];


		struct	{

			/**
			*	@brief	X component
			*/
			COORDV		x_;


			/**
			*	@brief	Y component
			*/
			COORDV		y_;


			/**
			*	@brief	Y component
			*/
			COORDV		z_;
		};


		/* 2d point is just a matter of casting */
		struct	{

			/**
			*	@brief	projection to X0Y plane
			*/
			P2D			d2_;

			/* no need for a dummy value here */

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
	*	@brief	compares two points and compares their coorsinates
	*/
	inline bool operator ==			(const P3D & other) const
	{
		if ( ( COORDV_EQ( x_, other.x_ ) ) &&
			 ( COORDV_EQ( y_, other.y_ ) ) &&
			 ( COORDV_EQ( z_, other.z_ ) ) )
			return true;
		return false;
	}


	/**
	*	@brief	compares two points and compares their coorsinates
	*/
	inline bool operator !=			(const P3D & other) const
	{
		return !( *this == other );
	}


	/*  FUNCTIONS    ======================================================= */
	//
	//
	//
	//

};	/*	class P3D	*/

/*  CLASS    =============================================================== */
//
//
//
//
#endif // __P3D_INC__
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
