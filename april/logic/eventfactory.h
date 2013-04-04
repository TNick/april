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

class	Event;

/*  DEFINITIONS    ========================================================= */
//
//
//
//
/*  CLASS    --------------------------------------------------------------- */

/**
*	@brief	Factory class for events
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
	virtual Event *			create				( ID id ) = 0;

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