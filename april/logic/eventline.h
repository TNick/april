/* ========================================================================= */
/* ------------------------------------------------------------------------- */
/*!
  \file			eventline.h
  \date			Apr 2013
  \author		TNick

  \brief		Contains the definition for EventLine class


*//*


 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Please read COPYING and README files in root folder
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
#ifndef __EVENTLINE_INC__
#define __EVENTLINE_INC__
//
//
//
//
/*  INCLUDES    ------------------------------------------------------------ */

#include    <april/april.h>
#include    <april/logic/component.h>
#include    <april/logic/uniqueid.h>
#include    <april/logic/eventdata.h>
#include    <libbbb/1/list2d.h>

/*  INCLUDES    ============================================================ */
//
//
//
//
/*  DEFINITIONS    --------------------------------------------------------- */

namespace   april    {
class	World;
class	EventData;

/*  DEFINITIONS    ========================================================= */
//
//
//
//
/*  CLASS    --------------------------------------------------------------- */

/**
*	@brief	Buffers between events and sensors
*/
class
	APRILSHARED_EXPORT
	EventLine		: public Component		{
	BBM_TRACK( EventLine );

	//
	//
	//
	//
	/*  DEFINITIONS    ----------------------------------------------------- */

	friend class	World;

	/*  DEFINITIONS    ===================================================== */
	//
	//
	//
	//
	/*  DATA    ------------------------------------------------------------ */

private:

	//! the world where this belongs
	World *				world_;

	//! the ID of this line
	ID					id_;
	
	//! the data
	List2Dh				event_data_;
	
	//! cache last in chain
	EventData *			last_;
	
	/*  DATA    ============================================================ */
	//
	//
	//
	//
	/*  FUNCTIONS    ------------------------------------------------------- */

public:


	//! constructor;
	EventLine			( World * w, ID id );

protected:

	//! destructor;
	virtual				~EventLine		( void );

public:

	//! the world where this belongs
	inline World *		world			( void ) const
	{ return world_; }

	//! the ID of this line
	inline ID			identificator	( void ) const
	{ return id_; }

	//! tell the number of packets
	inline int			dataCount		( void ) const
	{ return event_data_.count(); }

	//! post activity on this event line
	void				postActivity	( EventData * ed );
	
	//! iterate and discard old entries
	void				discardOldEntries	( void );

	//! get first (newest) packet
	inline EventData *	firstEventData	( void ) const
	{ return firstEventData_(this); }
	
	//! get last (oldest) packet
	EventData *			lastEventData	( void );
	
	
	/*  FUNCTIONS    ======================================================= */
	//
	//
	//
	//

};	/*	class EventLine	*/

/*  CLASS    =============================================================== */
//
//
//
//

}   //  namespace   april

#endif // __EVENTLINE_INC__
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
