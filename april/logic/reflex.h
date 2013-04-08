/* ========================================================================= */
/* ------------------------------------------------------------------------- */
/*!
  \file			reflex.h
  \date			Apr 2013
  \author		TNick

  \brief		Contains the definition for Reflex class


*//*


 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Please read COPYING and README files in root folder
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
#ifndef __REFLEX_INC__
#define __REFLEX_INC__
//
//
//
//
/*  INCLUDES    ------------------------------------------------------------ */

#include    <april/april.h>
#include    <april/logic/actorcomp.h>

/*  INCLUDES    ============================================================ */
//
//
//
//
/*  DEFINITIONS    --------------------------------------------------------- */

namespace   april    {
class	Actor;

/*  DEFINITIONS    ========================================================= */
//
//
//
//
/*  CLASS    --------------------------------------------------------------- */

/**
*	@brief	A base class for a reflex
*/
class
	APRILSHARED_EXPORT
	Reflex		: public ActorComp		{
	BBM_TRACK( Reflex );

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


	//! constructor; sets cost and packed energy to 0
	Reflex				( Actor * actor );

	//! constructor; sets cost and packed energy
	Reflex				( Actor * actor, quint64 cost, quint64 energy );

protected:

	/**
	*	@brief	destructor;
	*/
	virtual				~Reflex		( void );

public:

	//! save to a QSettings object
	virtual bool		save					( QSettings & s ) const;
	
	//! load from a QSettings object
	virtual bool		load					( QSettings & s );


	/*  FUNCTIONS    ======================================================= */
	//
	//
	//
	//

};	/*	class Reflex	*/

/*  CLASS    =============================================================== */
//
//
//
//

}   //  namespace   april

#endif // __REFLEX_INC__
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
