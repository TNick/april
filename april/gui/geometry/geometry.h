/* ========================================================================= */
/* ------------------------------------------------------------------------- */
/*!
  \file			geometry.h
  \date			Apr 2012
  \author		TNick

*//*


 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Please read COPYING and README files in root folder
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
#ifndef __GEOMETRY_INC__
#define __GEOMETRY_INC__

#include	<limits.h>
#include	<qmath.h>

/**
*	@brief the data type used to represent internal values
*/
#define		COORDV			int


/**
*	@brief special value that marks infinity
*/
#define		COORDV_INFINITY	INT_MAX


/**
*	@brief compares two values to see if they are equal
*/
#define		COORDV_EQ(a,b)	( qAbs( a - b ) < 0.0001 )


/**
*	@brief computes square root of a COORDV
*/
#define		COORDV_SQR(a)	qSqrt(a)


/**
*	@brief computes sinus of a
*/
#define		COORDV_SIN(a)	qSin(a)


/**
*	@brief computes cosinus of a
*/
#define		COORDV_COS(a)	qCos(a)


/**
*	@brief computes tangent of a
*/
#define		COORDV_TAN(a)	qTan(a)


/**
*	@brief computes arc sinus of a
*/
#define		COORDV_ASIN(a)	qAsin(a) /*qFastSin(a)*/


/**
*	@brief computes arc cosinus of a
*/
#define		COORDV_ACOS(a)	qAcos(a) /*qFastCos(a)*/


/**
*	@brief computes arc tangent of a
*/
#define		COORDV_ATAN(a)	qAtan(a)


/**
*	@brief computes arc tangent of an angle knowing x and y
*/
#define		COORDV_ATAN2(x, y)	qAtan2(y, x)


/**
*	@brief the value of PI
*/
#define		COORDV_PI			3.141592653589793


/**
*	@brief the value of PI / 2
*/
#define		COORDV_PI_DIV_2		1.5707963267948965


/**
*	@brief the value of PI / 4
*/
#define		COORDV_PI_DIV_4		0.78539816339744825


/**
*	@brief the value of 2 * PI
*/
#define		COORDV_2_PI			6.283185307179586




#endif // __GEOMETRY_INC__
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
