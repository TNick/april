/* ========================================================================= */
/* ------------------------------------------------------------------------- */
/*!
  \file			eventfactory.h
  \date			Apr 2013
  \author		TNick

  \brief		Contains the definition for EventFactory class


*//*


 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Please read COPYING and README files in root folder
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
#ifndef __EVENTFACTORY_INC__
#define __EVENTFACTORY_INC__
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

class	EventSource;

/*  DEFINITIONS    ========================================================= */
//
//
//
//
/*  CLASS    --------------------------------------------------------------- */

/**
*	@brief	Factory class for events
*
*	Each such class may be capable of creating one or more
*	types or events. At construction time each such type (ID)
*	must be associated with this instance in the World with 
*	World::addEventFactory().
*/
class
	APRILSHARED_EXPORT
	EventFactory		: public Factory		{
	BBM_TRACK( EventFactory );

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

	//! constructor;
	EventFactory			( World * w );


protected:

	//! destructor;
	virtual					~EventFactory		( void );

public:
	
	//! the generic type of the factory
	virtual FactoryType		factoryType			( void )
	{ return FTyEvent; }
	
	//! the name used to save this factory
	virtual QString			factoryName			( void )
	{ return "Event.Factory.Default"; }

	//! create an event source;
	/**
	 * By default this method creates a simple EventSource.
	 * The caller recieves a reference that should eventually discard.
	 *
	 * @param id The id that is requested; the implementation does 
	 * not use this parameter
	 * @return either a pointer or NULL
	 */
	virtual EventSource *	create				( ID id );

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

};	/*	class EventFactory	*/

/*  CLASS    =============================================================== */
//
//
//
//

}   //  namespace   april

#endif // __EVENTFACTORY_INC__
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
