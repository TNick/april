/* ========================================================================= */
/* ------------------------------------------------------------------------- */
/*!
  \file			actuatorfactory.h
  \date			Apr 2013
  \author		TNick

  \brief		Contains the definition for ActuatorFactory class


*//*


 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Please read COPYING and README files in root folder
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
#ifndef __ACTUATORFACTORY_INC__
#define __ACTUATORFACTORY_INC__
//
//
//
//
/*  INCLUDES    ------------------------------------------------------------ */

#include    <april/april.h>
#include    <april/logic/factory.h>

/*  INCLUDES    ============================================================ */
//
//
//
//
/*  DEFINITIONS    --------------------------------------------------------- */

namespace   april    {

class	Actor;
class	Actuator;

/*  DEFINITIONS    ========================================================= */
//
//
//
//
/*  CLASS    --------------------------------------------------------------- */

/**
*	@brief	Factory class for actuators
*/
class
	APRILSHARED_EXPORT
	ActuatorFactory		: public Factory		{
	BBM_TRACK( ActuatorFactory );

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
	ActuatorFactory			( World * w );

protected:

	/**
	*	@brief	destructor;
	*/
	virtual					~ActuatorFactory		( void );

public:

	//! create an actuator;
	virtual Actuator *		create					( Actor * ag, ID id ) = 0;

protected:

	//! add this class to the world
	bool					addMyself			( ID id );


	/*  FUNCTIONS    ======================================================= */
	//
	//
	//
	//

};	/*	class ActuatorFactory	*/

/*  CLASS    =============================================================== */
//
//
//
//

}   //  namespace   april

#endif // __ACTUATORFACTORY_INC__
/* ------------------------------------------------------------------------- */
/* ========================================================================= */