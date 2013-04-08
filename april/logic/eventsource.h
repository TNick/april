/* ========================================================================= */
/* ------------------------------------------------------------------------- */
/*!
  \file			eventsource.h
  \date			Apr 2013
  \author		TNick

  \brief		Contains the definition for EventSource class


*//*


 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Please read COPYING and README files in root folder
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
#ifndef __EVENT_INC__
#define __EVENT_INC__
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
class	World;

/*  DEFINITIONS    ========================================================= */
//
//
//
//
/*  CLASS    --------------------------------------------------------------- */

/**
*	@brief	An event is a way to stimulate agents from a world.
*
*	Events may stimulate certain kinds of sensors. They may have a placement
*	and a range and the intensity of the stimulation may be a function
*	of distance from source. Events may exists that have no placement.
*
*	Events may stay alive a long time and generate activity from time to time
*	or they may be single-shoots.
*
*	A world has EventLine's, each with an ID. An EventSource posts activity on the
*	EventLine's that are then checked by the Sensor's. Each EventSource may post
*	to one or more EventLine's.
*/
class
	APRILSHARED_EXPORT
	EventSource		: public Component		{
	BBM_TRACK( EventSource );

	//
	//
	//
	//
	/*  DEFINITIONS    ----------------------------------------------------- */

	friend class	World;
	friend class	Director;

	/*  DEFINITIONS    ===================================================== */
	//
	//
	//
	//
	/*  DATA    ------------------------------------------------------------ */

private:

	//! the world where this belongs
	World *				world_;

	/*  DATA    ============================================================ */
	//
	//
	//
	//
	/*  FUNCTIONS    ------------------------------------------------------- */

public:

	//! constructor;
	EventSource				( World * w );

protected:

	//! destructor;
	virtual				~EventSource		( void );

	//! perform steps (called by the World)
	virtual void		doSteps		( int steps  = 1 ) = 0;

public:

	//! the world where this belongs
	inline World *		world		( void ) const
	{ return world_; }

	//! save to a QSettings object
	virtual bool		save		( QSettings & s ) const;
	
	//! load from a QSettings object
	virtual bool		load		( QSettings & s );

	/*  FUNCTIONS    ======================================================= */
	//
	//
	//
	//

};	/*	class EventSource	*/

/*  CLASS    =============================================================== */
//
//
//
//

}   //  namespace   april

#endif // __EVENT_INC__
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
