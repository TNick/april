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
class
	APRILSHARED_EXPORT
	ActorFactory		: public Factory		{
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
	ActorFactory			( World * w );

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

protected:

	//! allow access to default dna storage
	DNA &					defaultDNA			( void )
	{ return default_dna_; }

	//! add this class to the world
	bool					addMyself			( ID id );
	
	//! set the DNA in the actor
	void					setDNA				( Actor * a, const DNA & dna );
	
	//! set default DNA in the actor
	void					setDNA				( Actor * a )
	{ setDNA( a, default_dna_ ); }
	
	//! initialise a DNA instance
	/**
	 * @param dna target structure
	 * @param id_kind the id to set in target structure
	 */
	void					initDNA				( DNA & dna, ID id_kind );
	
	//! initialise default DNA instance
	void					initDNA				( ID id_kind )
	{ initDNA( default_dna_, id_kind ); }
	
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
