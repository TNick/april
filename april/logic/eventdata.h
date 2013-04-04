/* ========================================================================= */
/* ------------------------------------------------------------------------- */
/*!
  \file			eventdata.h
  \date			Apr 2013
  \author		TNick

  \brief		Contains the definition for EventData class


*//*


 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Please read COPYING and README files in root folder
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
#ifndef __EVENTDATA_INC__
#define __EVENTDATA_INC__
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
*	@brief	A packet in an EventLine
*/
class EventData		: public Component		{
	BBM_TRACK( EventData );

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

	//! the time when this should be discarded
	quint64				discard_time_;

	/*  DATA    ============================================================ */
	//
	//
	//
	//
	/*  FUNCTIONS    ------------------------------------------------------- */

public:

	//! constructor;
	EventData			( void );

protected:

	//! destructor;
	virtual				~EventData		( void );

public:

	//! the time when this should be discarded
	inline quint64		discardTime		( void ) const
	{ return discard_time_; }

protected:

	//! set the time when this should be discarded
	inline void			setDiscardTime	( quint64 t )
	{ discard_time_ = t; }

	//! set how long this data should stay in the lines
	void				setDuration		( World * w, quint64 dt );

	/*  FUNCTIONS    ======================================================= */
	//
	//
	//
	//

};	/*	class EventData	*/

/*  CLASS    =============================================================== */
//
//
//
//

}   //  namespace   april

#endif // __EVENTDATA_INC__
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
