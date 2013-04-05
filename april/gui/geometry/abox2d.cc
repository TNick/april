/* ========================================================================= */
/* ------------------------------------------------------------------------- */
/*!
  \file			abox2d.cc
  \date			Apr 2012
  \author		TNick

  \brief		Contains the implementation of ABOX2D class


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

#include	"abox2d.h"


/*  INCLUDES    ============================================================ */
//
//
//
//
/*  DEFINITIONS    --------------------------------------------------------- */


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
void			ABOX2D::unite			(
		const ABOX2D & first, const ABOX2D & second )
{
	left_ = ( first.left_ < second.left_ ? first.left_ : second.left_ );
	bottom_ = ( first.bottom_ < second.bottom_ ? first.bottom_ : second.bottom_ );
	right_ = ( first.right_ > second.right_ ? first.right_ : second.right_ );
	top_ = ( first.top_ > second.top_ ? first.top_ : second.top_ );
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void			ABOX2D::unite			( const ABOX2D & other )
{
	left_ = ( left_ < other.left_ ? left_ : other.left_ );
	bottom_ = ( bottom_ < other.bottom_ ? bottom_ : other.bottom_ );
	right_ = ( right_ > other.right_ ? right_ : other.right_ );
	top_ = ( top_ > other.top_ ? top_ : other.top_ );
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool			ABOX2D::contains		( const P2D & other ) const
{
	return ( ( other.x_ >= left_ ) &&
			 ( other.y_ >= bottom_ ) &&
			 ( other.x_ < right_ ) &&
			 ( other.y_ < top_ )
			 );
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool			ABOX2D::contains		( const ABOX2D & other ) const
{
	return ( ( other.left_ >= left_ ) &&
			 ( other.bottom_ >= bottom_ ) &&
			 ( other.right_ <= right_ ) &&
			 ( other.top_ <= top_ ) );
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool			ABOX2D::intersect		(
		const ABOX2D & first, const ABOX2D & second )
{
	bool	b_res = true;
	left_ = ( first.left_ > second.left_ ? first.left_ : second.left_ );
	bottom_ = ( first.bottom_ > second.bottom_ ? first.bottom_ : second.bottom_ );
	right_ = ( first.right_ < second.right_ ? first.right_ : second.right_ );
	top_ = ( first.top_ < second.top_ ? first.top_ : second.top_ );
	if ( left_ > right_ )
	{
		left_ = 0;
		right_ = 0;
		b_res = false;
	}
	if ( bottom_ > top_ )
	{
		bottom_ = 0;
		top_ = 0;
		b_res = false;
	}
	return b_res;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool			ABOX2D::intersect		( const ABOX2D & other )
{
	return intersect( *this, other );
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void			ABOX2D::normalise		( void )
{
	COORDV	tmp;
	if ( left_ > right_ )
	{
		tmp = left_;
		left_ = right_;
		right_ = tmp;
	}
	if ( bottom_ > top_ )
	{
		tmp = bottom_;
		bottom_ = top_;
		top_ = tmp;
	}
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void			ABOX2D::offset			( COORDV dist )
{
	left_ -= dist;
	bottom_ -= dist;
	right_ += dist;
	top_ += dist;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void			ABOX2D::offset			( COORDV dist, ABOX2D & out ) const
{
	out.left_ = left_ - dist;
	out.bottom_ = bottom_ - dist;
	out.right_ = right_ + dist;
	out.top_ = top_ + dist;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool			ABOX2D::visibleIn		( const ABOX2D & other ) const
{
	Q_ASSERT( isNormalised() );
	Q_ASSERT( other.isNormalised() );

	if ( ( right_ < other.left_ ) ||
		 ( left_ > other.right_ ) ||
		 ( top_ < other.bottom_ ) ||
		 ( bottom_ > other.top_ ) )
		return false;

	return true;

}
/* ========================================================================= */

/*  CLASS    =============================================================== */
//
//
//
//
/* ------------------------------------------------------------------------- */
/* ========================================================================= */


