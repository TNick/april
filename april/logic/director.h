/* ========================================================================= */
/* ------------------------------------------------------------------------- */
/*!
  \file			director.h
  \date			Apr 2013
  \author		TNick

  \brief		Contains the definition for Director class


*//*


 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Please read COPYING and README files in root folder
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
#ifndef __DIRECTOR_INC__
#define __DIRECTOR_INC__
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
class	EventLine;

/*  DEFINITIONS    ========================================================= */
//
//
//
//
/*  CLASS    --------------------------------------------------------------- */

/**
*	@brief	manages the runnings of a world
*/
class
	APRILSHARED_EXPORT
	Director		: public libbbb::RefCnt, public MemTrack		{
	BBM_TRACK( Director );

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

	//! the world we're managing
	World *				w_;

	/*  DATA    ============================================================ */
	//
	//
	//
	//
	/*  FUNCTIONS    ------------------------------------------------------- */

public:

	//! constructor;
	Director			( World * w );

	//! destructor;
	virtual				~Director		( void );

	//! the world we're managing
	inline World *		world			( void ) const
	{ return w_; }

	//! start the world
	virtual bool		start			( void )
	{ return true; }

	//! stop the world
	virtual void		stop			( void )
	{}

	//! advance the world
	virtual void		advance			( void );

	//! save to a QSettings object
	virtual bool		save			( QSettings & s ) const;
	
	//! load from a QSettings object
	virtual bool		load			( QSettings & s );

protected:

	//! access to event lines in the world - first
	QMap<ID,EventLine*>::ConstIterator	firstEventLine		( void );

	//! access to event lines in the world - end
	QMap<ID,EventLine*>::ConstIterator	endEventLine		( void );
	
	//! advance the time in the world
	void				stepTime		( void );

	/*  FUNCTIONS    ======================================================= */
	//
	//
	//
	//

};	/*	class Director	*/

/*  CLASS    =============================================================== */
//
//
//
//

}   //  namespace   april

#endif // __DIRECTOR_INC__
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
