/* ========================================================================= */
/* ------------------------------------------------------------------------- */
/*!
  \file			genericactorfactory.h
  \date			Apr 2013
  \author		TNick

  \brief		Contains the definition for GenericActorFactory class


*//*


 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Please read COPYING and README files in root folder
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
#ifndef __GENERICACTORFACTORY_INC__
#define __GENERICACTORFACTORY_INC__
//
//
//
//
/*  INCLUDES    ------------------------------------------------------------ */

#include    <april/april.h>
#include    <april/logic/actorfactory.h>
#include    <april/logic/uniqueid.h>

/*  INCLUDES    ============================================================ */
//
//
//
//
/*  DEFINITIONS    --------------------------------------------------------- */

namespace   april    {

/*  DEFINITIONS    ========================================================= */
//
//
//
//
/*  CLASS    --------------------------------------------------------------- */

/**
*	@brief	A generic actor factory
*
*	The factory simply worls with IDs and DNA. For each DNA registered an
*	ID is used.
*/
class
		APRILSHARED_EXPORT
		GenericActorFactory		: public ActorFactory		{
	BBM_TRACK( GenericActorFactory );

	//
	//
	//
	//
	/*  DEFINITIONS    ----------------------------------------------------- */

public:

	//! a list of ID and DNA values
	typedef	QMap<ID,DNA>					IdDnaMap;
	typedef	QMap<ID,DNA>::Iterator			IdDnaMapIter;
	typedef	QMap<ID,DNA>::ConstIterator		IdDnaMapIterC;

	/*  DEFINITIONS    ===================================================== */
	//
	//
	//
	//
	/*  DATA    ------------------------------------------------------------ */

private:

	//! the list of IDs and DNA
	IdDnaMap				list_;

	//! invalid reference
	DNA						dna_invalid_;
	
	/*  DATA    ============================================================ */
	//
	//
	//
	//
	/*  FUNCTIONS    ------------------------------------------------------- */

public:

	//! constructor
	GenericActorFactory		( World * w );

protected:

	//! destructor;
	virtual					~GenericActorFactory( void );
	
	//! the generic type of the factory
	virtual FactoryType		factoryType			( void )
	{ return FTyGenericActor; }
	
	//! the name used to save this factory
	virtual QString			factoryName			( void )
	{ return staticName(); }

	//! create a new actor
	/**
	 * Looks up the ID in the internal list. If found, the DNA for
	 * that ID is used to construct a new Actor.
	 *
	 * The caller recieves a reference that should eventually discard.
	 *
	 * @param id The id that is requested
	 * @return either a pointer or NULL
	 */
	virtual Actor *			create				( ID id );

	//! save to a QSettings object
	virtual bool			save				( QSettings & s ) const;
	
	//! load from a QSettings object
	virtual bool			load				( QSettings & s );

public:

	//! find the instance (should only be one) of this class in a world
	/**
	 * The method returns a reference to the caller that should
	 * eventually release it.
	 *
	 * @param w the target world
	 * @return always non-null
	 */
	static GenericActorFactory *	findMyself	( World * w );

	//! the name of this factory
	static QString			staticName			( void )
	{ return "Actor.Factory.Generic"; }

	//! the list of IDs and DNA
	const IdDnaMap &		dnaList				( void ) const
	{ return list_; }

	//! creates a new kind
	void					addNewKind			( const DNA::InitData & data );

	//! get the DNA at a particular index
	DNA &					dna					( ID id );

	/*  FUNCTIONS    ======================================================= */
	//
	//
	//
	//

};	/*	class GenericActorFactory	*/

/*  CLASS    =============================================================== */
//
//
//
//

}   //  namespace   april

#endif // __GENERICACTORFACTORY_INC__
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
