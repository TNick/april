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
	
	//! the generic type of the factory
	virtual FactoryType			factoryType		( void )
	{ return FTyActuator; }
	
	//! the name used to save this factory
	virtual QString			factoryName			( void )
	{ return "Actuator.Factory.Default"; }

	//! create an actuator;
	/**
	 * By default this method creates a simple Actuator.
	 * The caller recieves a reference that should eventually discard.
	 *
	 * @param ag The actor where this is to be created
	 * @param id The id that is requested; the implementation does 
	 * not use this parameter
	 * @return either a pointer or NULL
	 */
	virtual Actuator *		create					( Actor * ag, ID id );

protected:

	//! add this class to the world
	bool					addMyself				( ID id );

public:

	//! save to a QSettings object
	virtual bool		save						( QSettings & s ) const;
	
	//! load from a QSettings object
	virtual bool		load						( QSettings & s );

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
