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
	
	//! the generic type of the factory
	virtual FactoryType		factoryType			( void )
	{ return FTyActor; }
	
	//! the name used to save this factory
	virtual QString			factoryName			( void )
	{ return "Actor.Factory.Default"; }

	//! copies default DNA from internal storage to destination
	virtual void			copyDefaultDNA		( DNA & destination )
	{ destination = default_dna_; }

	//! create a new actor
	/**
	 * By default this method creates a simple Actor based on the
	 * default_dna_. The method fails if the id in DNA is not the 
	 * same as the one that was required.
	 *
	 * The caller recieves a reference that should eventually discard.
	 *
	 * @param id The id that is requested
	 * @return either a pointer or NULL
	 */
	virtual Actor *			create				( ID id );

//	//! create a new actor from saved settings
//	/** @deprecated */
//	virtual Actor *			create				( QSettings & stg )
//	{ Q_UNUSED(stg); return NULL;}

	//! save to a QSettings object
	virtual bool			save				( QSettings & s ) const;
	
	//! load from a QSettings object
	virtual bool			load				( QSettings & s );
	
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
	void					initDNA				(
			DNA &					dna,
			const DNA::InitData &	init
			);
	
	//! initialise default DNA instance
	void					initDNA				( const DNA::InitData & init )
	{ initDNA( default_dna_, init ); }
	
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
