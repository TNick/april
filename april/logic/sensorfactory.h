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
	
	//! the generic type of the factory
	virtual FactoryType		factoryType			( void )
	{ return FTySensor; }
	
	//! the name used to save this factory
	virtual QString			factoryName			( void )
	{ return "Sensor.Factory.Default"; }

	//! create an actuator;
	/**
	 * By default this method creates a simple Sensor.
	 * The caller recieves a reference that should eventually discard.
	 *
	 * @param id The id that is requested; the implementation does 
	 * not use this parameter
	 * @return either a pointer or NULL
	 */
	virtual Sensor *		create				( Actor * ag, ID id );

	//! save to a QSettings object
	virtual bool			save				( QSettings & s ) const;
	
	//! load from a QSettings object
	virtual bool			load				( QSettings & s );

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
