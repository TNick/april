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
*	@brief	Buffers between events and sensors
*/
class EventLine		: public Component		{
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
