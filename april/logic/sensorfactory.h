/* ========================================================================= */
/* ------------------------------------------------------------------------- */
/*!
  \file			sensorfactory.h
  \date			Apr 2013
  \author		TNick

  \brief		Contains the definition for SensorFactory class


*//*


 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Please read COPYING and README files in root folder
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
#ifndef __SENSORFACTORY_INC__
#define __SENSORFACTORY_INC__
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

class	Sensor;
class	Actor;

/*  DEFINITIONS    ========================================================= */
//
//
//
//
/*  CLASS    --------------------------------------------------------------- */

/**
*	@brief	Factory class for sensors
*/
class
	APRILSHARED_EXPORT
	SensorFactory		: public Factory		{
	BBM_TRACK( SensorFactory );

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
	SensorFactory			( World * w );

protected:

	/**
	*	@brief	destructor;
	*/
	virtual					~SensorFactory		( void );

public:

	//! create an actuator;
	virtual Sensor *		create				( Actor * ag, ID id ) = 0;

protected:

	//! add this class to the world
	bool					addMyself			( ID id );

	/*  FUNCTIONS    ======================================================= */
	//
	//
	//
	//

};	/*	class SensorFactory	*/

/*  CLASS    =============================================================== */
//
//
//
//

}   //  namespace   april

#endif // __SENSORFACTORY_INC__
/* ------------------------------------------------------------------------- */
/* ========================================================================= */