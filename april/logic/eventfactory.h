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


	/**
	*	@brief	constructor;
	*/
	EventFactory			( World * w );


protected:

	/**
	*	@brief	destructor;
	*/
	virtual					~EventFactory		( void );


public:

	//! create an actuator;
	virtual EventSource *			create				( ID id ) = 0;

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
