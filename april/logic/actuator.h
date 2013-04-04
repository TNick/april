/* ========================================================================= */
/* ------------------------------------------------------------------------- */
/*!
  \file			actuator.h
  \date			Apr 2013
  \author		TNick

  \brief		Contains the definition for Actuator class


*//*


 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Please read COPYING and README files in root folder
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
#ifndef __ACTUATOR_INC__
#define __ACTUATOR_INC__
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
*	@brief	Base class for actuators
*
*	This is the output of an actor. This may be a hand or a foot, for example,
*	or the generic action of moving.
*/
class
	APRILSHARED_EXPORT
	Actuator		: public Component		{
	BBM_TRACK( Actuator );

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
	Actuator			( Actor * actor );

protected:

	/**
	*	@brief	destructor;
	*/
	virtual				~Actuator		( void );

public:

	//! parent actor
	inline Actor *		actor		( void ) const
	{ return actor_; }


	/*  FUNCTIONS    ======================================================= */
	//
	//
	//
	//

};	/*	class Actuator	*/

/*  CLASS    =============================================================== */
//
//
//
//

}   //  namespace   april

#endif // __ACTUATOR_INC__
/* ------------------------------------------------------------------------- */
/* ========================================================================= */