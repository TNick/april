/* ========================================================================= */
/* ------------------------------------------------------------------------- */
/*!
  \file			brain.h
  \date			Apr 2013
  \author		TNick

  \brief		Contains the definition for Brain class


*//*


 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Please read COPYING and README files in root folder
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
#ifndef __BRAIN_INC__
#define __BRAIN_INC__
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
*	@brief	Base class for a brain
*/
class
	APRILSHARED_EXPORT
	Brain		: public ActorComp		{
	BBM_TRACK( Brain );

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
	Brain				( Actor * actor );
	
	//! constructor; sets cost and packed energy
	Brain				( Actor * actor, quint64 cost, quint64 energy );
	
	//! constructor method; creates and loads an Brain from QSettings
	Q_REQUIRED_RESULT
	static Brain *		fromStg				( Actor * a, QSettings & stg );

protected:

	/**
	*	@brief	destructor;
	*/
	virtual				~Brain		( void );

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

};	/*	class Brain	*/

/*  CLASS    =============================================================== */
//
//
//
//

}   //  namespace   april

#endif // __BRAIN_INC__
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
