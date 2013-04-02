/* ========================================================================= */
/* ------------------------------------------------------------------------- */
/*!
  \file			actorfactory.h
  \date			Apr 2013
  \author		TNick

  \brief		Contains the definition for ActorFactory class


*//*


 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Please read COPYING and README files in root folder
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
#ifndef __ACTORFACTORY_INC__
#define __ACTORFACTORY_INC__
//
//
//
//
/*  INCLUDES    ------------------------------------------------------------ */

#include    <april/april.h>
#include    <april/logic/factory.h>
#include    <april/logic/dna.h>

/*  INCLUDES    ============================================================ */
//
//
//
//
/*  DEFINITIONS    --------------------------------------------------------- */

namespace   april    {

class		DNA;
class		Actor;

/*  DEFINITIONS    ========================================================= */
//
//
//
//
/*  CLASS    --------------------------------------------------------------- */

/**
*	@brief	Factory class for agents
*/
class ActorFactory		: public Factory		{
	BBM_TRACK( ActorFactory );

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

	//! storage space for default DNA
	/**
	 * If the class provides more than one actor than additional space
	 * will be needed.
	 */
	DNA			default_dna_;

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
	ActorFactory			( void );

protected:

	/**
	*	@brief	destructor;
	*/
	virtual					~ActorFactory		( void );

public:


	//! copies default DNA from internal storage to destination
	virtual void			copyDefaultDNA		( DNA & destination )
	{ destination = default_dna_; }

	//! create a new actor
	virtual Actor *			create				( ID id ) = 0;

	/*  FUNCTIONS    ======================================================= */
	//
	//
	//
	//

};	/*	class ActorFactory	*/

/*  CLASS    =============================================================== */
//
//
//
//

}   //  namespace   april

#endif // __ACTORFACTORY_INC__
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
