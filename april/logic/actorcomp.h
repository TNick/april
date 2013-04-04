/* ========================================================================= */
/* ------------------------------------------------------------------------- */
/*!
  \file			actorcomp.h
  \date			Apr 2013
  \author		TNick

  \brief		Contains the definition for ActorComp class


*//*


 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Please read COPYING and README files in root folder
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
#ifndef __ACTORCOMP_INC__
#define __ACTORCOMP_INC__
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
*	@brief
*/
class ActorComp		: public Component		{
	BBM_TRACK( ActorComp );

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

	//! cost per time unit
	quint64					cost_;

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
	ActorComp			( Actor * actor );

protected:

	/**
	*	@brief	destructor;
	*/
	virtual				~ActorComp		( void );

public:

	//! parent actor
	inline Actor *		actor		( void ) const
	{ return actor_; }

	//! cost per time unit
	inline quint64		cost		( void ) const
	{ return cost_; }

protected:

	//! set cost per time unit
	void				setCost		( quint64 new_val )
	{ cost_ = new_val; }

	/*  FUNCTIONS    ======================================================= */
	//
	//
	//
	//

};	/*	class ActorComp	*/

/*  CLASS    =============================================================== */
//
//
//
//

}   //  namespace   april

#endif // __ACTORCOMP_INC__
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
