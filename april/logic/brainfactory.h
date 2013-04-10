/* ========================================================================= */
/* ------------------------------------------------------------------------- */
/*!
  \file			brainfactory.h
  \date			Apr 2013
  \author		TNick

  \brief		Contains the definition for BrainFactory class


*//*


 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Please read COPYING and README files in root folder
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
#ifndef __BRAINFACTORY_INC__
#define __BRAINFACTORY_INC__
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

class	Brain;
class	Actor;

/*  DEFINITIONS    ========================================================= */
//
//
//
//
/*  CLASS    --------------------------------------------------------------- */

/**
*	@brief Base class for brain factories
*/
class
	APRILSHARED_EXPORT
	BrainFactory		: public Factory		{
	BBM_TRACK( BrainFactory );

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
	BrainFactory		( World * w );

protected:

	/**
	*	@brief	destructor;
	*/
	virtual				~BrainFactory			( void );


public:
	
	//! the generic type of the factory
	virtual FactoryType			factoryType		( void )
	{ return FTyBrain; }
	
	//! the name used to save this factory
	virtual QString			factoryName			( void )
	{ return "Brain.Factory.Default"; }

	//! create an actuator;
	/**
	 * By default this method creates a simple Brain.
	 * The caller recieves a reference that should eventually discard.
	 *
	 * @param id The id that is requested; the implementation does 
	 * not use this parameter
	 * @return either a pointer or NULL
	 */
	virtual Brain *		create					( Actor * ag, ID id );

	//! save to a QSettings object
	virtual bool		save					( QSettings & s ) const;
	
	//! load from a QSettings object
	virtual bool		load					( QSettings & s );

protected:

	//! add this class to the world
	bool				addMyself				( ID id );


	/*  FUNCTIONS    ======================================================= */
	//
	//
	//
	//

};	/*	class BrainFactory	*/

/*  CLASS    =============================================================== */
//
//
//
//

}   //  namespace   april

#endif // __BRAINFACTORY_INC__
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
