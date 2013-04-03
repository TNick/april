/* ========================================================================= */
/* ------------------------------------------------------------------------- */
/*!
  \file			brain.h
  \date			Apr 2013
  \author		TNick

  \brief		Contains the definition for Brain class


*//*


 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Please read COPYING and README files in root folder
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
#ifndef __BRAIN_INC__
#define __BRAIN_INC__
//
//
//
//
/*  INCLUDES    ------------------------------------------------------------ */

#include    <april/april.h>
#include    <april/logic/component.h>

/*  INCLUDES    ============================================================ */
//
//
//
//
/*  DEFINITIONS    --------------------------------------------------------- */

namespace   april    {
class	Actor;

/*  DEFINITIONS    ========================================================= */
//
//
//
//
/*  CLASS    --------------------------------------------------------------- */

/**
*	@brief	Base class for a brain
*/
class
	APRILSHARED_EXPORT
	Brain		: public Component		{
	BBM_TRACK( Brain );

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

	//! parent actor
	Actor *					actor_;

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
	Brain				( Actor * actor );

protected:

	/**
	*	@brief	destructor;
	*/
	virtual				~Brain		( void );

public:

	//! parent actor
	inline Actor *		actor		( void ) const
	{ return actor_; }


	/*  FUNCTIONS    ======================================================= */
	//
	//
	//
	//

};	/*	class Brain	*/

/*  CLASS    =============================================================== */
//
//
//
//

}   //  namespace   april

#endif // __BRAIN_INC__
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
