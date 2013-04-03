/* ========================================================================= */
/* ------------------------------------------------------------------------- */
/*!
  \file			actor.h
  \date			Apr 2013
  \author		TNick

  \brief		Contains the definition for Actor class


*//*


 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Please read COPYING and README files in root folder
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
#ifndef __ACTOR_INC__
#define __ACTOR_INC__
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

class World;
class Sensor;
class Actuator;
class Brain;
class Actor;
class Reflex;

/*  DEFINITIONS    ========================================================= */
//
//
//
//
/*  CLASS    --------------------------------------------------------------- */

/**
*	@brief	An active ocupier of the world
*/
class
	APRILSHARED_EXPORT
	Actor		: public Component		{
	BBM_TRACK( Actor );

	//
	//
	//
	//
	/*  DEFINITIONS    ----------------------------------------------------- */

	friend class Sensor;
	friend class Actuator;
	friend class World;
	friend class Reflex;
	friend class Brain;
	
	/*  DEFINITIONS    ===================================================== */
	//
	//
	//
	//
	/*  DATA    ------------------------------------------------------------ */

private:

	//! the world where we belong
	World *					world_;

	//! header for the list of sensors
	List2Dh					sensors_;
	
	//! header for the list of actuators
	List2Dh					actuators_;
	
	//! header for the list of reflexes
	List2Dh					reflexes_;
	
	//! header for the list of brains
	List2Dh					brains_;
	

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
	Actor			( World * w );

protected:

	/**
	*	@brief	destructor;
	*/
	virtual			~Actor		( void );

public:

	//! the world where we belong
	inline World *		world				( void ) const
	{ return world_; }


public:
	
	
	//! first sensor in internal list
	Sensor *		firstSensor				( void ) const;
	
	//! first actuator in internal list
	Actuator *		firstActuator			( void ) const;
	
	//! first reflex in internal list
	Reflex *		firstReflex				( void ) const;
	
	//! first brain in internal list
	Brain *			firstBrain				( void ) const;


	/*  FUNCTIONS    ======================================================= */
	//
	//
	//
	//

};	/*	class Actor	*/

/*  CLASS    =============================================================== */
//
//
//
//

}   //  namespace   april

#endif // __ACTOR_INC__
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
