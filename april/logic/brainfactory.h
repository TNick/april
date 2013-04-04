/* ========================================================================= */
/* ------------------------------------------------------------------------- */
/*!
  \file			brainfactory.h
  \date			Apr 2013
  \author		TNick

  \brief		Contains the definition for BrainFactory class


*//*


 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Please read COPYING and README files in root folder
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
#ifndef __BRAINFACTORY_INC__
#define __BRAINFACTORY_INC__
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

class	Brain;
class	Actor;

/*  DEFINITIONS    ========================================================= */
//
//
//
//
/*  CLASS    --------------------------------------------------------------- */

/**
*	@brief Base class for brain factories
*/
class
	APRILSHARED_EXPORT
	BrainFactory		: public Factory		{
	BBM_TRACK( BrainFactory );

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
	BrainFactory			( World * w );

protected:

	/**
	*	@brief	destructor;
	*/
	virtual				~BrainFactory		( void );


public:

	//! create an actuator;
	virtual Brain *		create				( Actor * ag, ID id ) = 0;

protected:

	//! add this class to the world
	bool					addMyself			( ID id );


	/*  FUNCTIONS    ======================================================= */
	//
	//
	//
	//

};	/*	class BrainFactory	*/

/*  CLASS    =============================================================== */
//
//
//
//

}   //  namespace   april

#endif // __BRAINFACTORY_INC__
/* ------------------------------------------------------------------------- */
/* ========================================================================= */