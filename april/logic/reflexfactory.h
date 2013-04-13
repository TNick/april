/* ========================================================================= */
/* ------------------------------------------------------------------------- */
/*!
  \file			reflexfactory.h
  \date			Apr 2013
  \author		TNick

  \brief		Contains the definition for ReflexFactory class


*//*


 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Please read COPYING and README files in root folder
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
#ifndef __REFLEXFACTORY_INC__
#define __REFLEXFACTORY_INC__
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
class	Reflex;

/*  DEFINITIONS    ========================================================= */
//
//
//
//
/*  CLASS    --------------------------------------------------------------- */

/**
*	@brief	Base class for reflex factories
*/
class
	APRILSHARED_EXPORT
	ReflexFactory		: public Factory		{
	BBM_TRACK( ReflexFactory );

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
	ReflexFactory			( World * w );

protected:

	/**
	*	@brief	destructor;
	*/
	virtual					~ReflexFactory		( void );

public:
	
	//! the generic type of the factory
	virtual FactoryType		factoryType			( void )
	{ return FTyReflex; }
	
	//! the name used to save this factory
	virtual QString			factoryName			( void )
	{ return "Reflex.Factory.Default"; }

	//! create an actuator;
	/**
	 * By default this method creates a simple Reflex.
	 * The caller recieves a reference that should eventually discard.
	 *
	 * @param ag The actor where this is to be created
	 * @param id The id that is requested; the implementation does 
	 * not use this parameter
	 * @return either a pointer or NULL
	 */
	virtual Reflex *		create				( Actor * ag, ID id );

public:

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

};	/*	class ReflexFactory	*/

/*  CLASS    =============================================================== */
//
//
//
//

}   //  namespace   april

#endif // __REFLEXFACTORY_INC__
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
