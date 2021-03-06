/* ========================================================================= */
/* ------------------------------------------------------------------------- */
/*!
  \file			dna.h
  \date			Apr 2013
  \author		TNick
  
  \brief		Contains the definition for DNA class
  
  
*//*


 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Please read COPYING and README files in root folder
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
#ifndef __DNA_INC__
#define __DNA_INC__
//
//
//
//
/*  INCLUDES    ------------------------------------------------------------ */

#include    <april/april.h>
#include	<april/logic/uniqueid.h>
#include	<april/logic/dnaview.h>

#include	<QSettings>
#include	<QVector>

/*  INCLUDES    ============================================================ */
//
//
//
//
/*  DEFINITIONS    --------------------------------------------------------- */

namespace   april    {

class World;
class Factory;

/*  DEFINITIONS    ========================================================= */
//
//
//
//
/*  CLASS    --------------------------------------------------------------- */

/**
*	@brief	Represents persistent read-only storage space for Actors
*
*	The class stores a list of real numbers represented 
*	as double-precision floating points. This list is 
*	partitioned in parts, each with an unique id. 
*	Each part is accesible as a DNAView.
*/
class
		APRILSHARED_EXPORT
		DNA				{
	
	//
	//
	//
	//
	/*  DEFINITIONS    ----------------------------------------------------- */
	
	friend class DNAView;
	friend class ActorFactory;
	
public:
	
	
	//! an entry in the list of partitions
	struct	Partition	{
		
		//! the unique ID of the component
		ID			id_;
		
		//! index of the first value
		int			start_;
		
		//! number of values
		int			count_;
		
		
		//! tell if two classes are equal
		bool			operator ==		( const Partition & other ) const
		{
			return ( ( id_ == other.id_ ) && 
					 ( start_ == other.start_ ) && 
					 ( count_ == other.count_ ) );
		}
		//! tell if two classes are not equal
		bool			operator !=		( const Partition & other ) const
		{
			return !operator==(other); 
		}
	};
	
public:
	
	//! the initialisation data 
	struct	InitData	{
		ID			kind_;	/**< ID of the factory that creates this kind of agent */
		quint64		cost_;	/**< the cost of running this agent */
		quint64		age_;	/**< average age of death */
		quint64		energy_;/**< energy required at birth */
	};
	
public:
	
	//! offsets for predefined values
	enum	Predef	{
		OffKind = 0,	/**< the kind - ID */
		
		OffBrains,		/**< number of brains in the list that follows */
		
		OffActuators,	/**< number of actuators in the list that follows */
		OffSensors,		/**< number of sensors in the list that follows */
		OffReflexes,	/**< number of reflexes in the list that follows */
		
		OffCost,		/**< the cost for running the Actor per time unit */
		OffAge,			/**< average age */
		OffStartEnergy,	/**< energy at birth */
		
		
		OffMax,
		OffLastList = OffReflexes+1
		/* the list of brains, actuators, sensors, reflex id's follows */
	};
	
	/*  DEFINITIONS    ===================================================== */
	//
	//
	//
	//
	/*  DATA    ------------------------------------------------------------ */
	
protected:
	
	//! list of regions that partition the list of values
	QVector<Partition>			parts_;
	
	//! actual sequence of numbers; subject to degradation
	QList<qreal>				values_;
	
	//! actual sequence of numbers; not subject to degradation
	QList<quint64>				values_i_;
	
	
	/*  DATA    ============================================================ */
	//
	//
	//
	//
	/*  FUNCTIONS    ------------------------------------------------------- */
	
public:
	
	
	/**
	*	@brief	constructor; creates an empty, invalid shell
	*/
	DNA				( void );
	
	/**
	*	@brief	constructor; creates a valid instance
	*
	*	The kind is looked up in the world and, if found, the default
	*	DNA for that kind is copied.
	*
	*	The resulted instance may be invalid if something goes wrong
	*	(world is invalid,  the kind does not
	*	have a valid default DNA).
	*
	*	If the world does not contain that kind the instance is valid
	*	but mostly empty.
	*/
	DNA				( const World * w, ID kind );
	
	/**
	*	@brief	destructor;
	*/
	~DNA			( void );
	
	//! set the DNA as a result of the two parents
	/**
	 *	This instance is set to the result of the merge. It is affected 
	 *	by random noise in the real part.
	 *
	 * @param p1 first parent
	 * @param p2 second parent
	 * @return true if the merge was succesfull
	 */
	bool			fromMerge		(
			const DNA &			p1,
			const DNA &			p2
			);
	
	//! tell if this instance is valid or not
	bool			isValid			( void ) const;
	
	//! tell if two classes are equal
	bool			operator ==		( const DNA & other ) const;
	
	
	
	/* OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO */
	/** @name examine components
	 */
	///@{
	
	
	//! get a view for a particular id
	/**
	 *	If the id is not to be found and a factory is 
	 *	provided then it is asked for a default for this ID.
	 *	If that does not work the DNAView will be invalid.
	 */
	DNAView			getView			( ID id, Factory * f = NULL );
	
	//! get a view for a particular id
	/**
	 *	This variant is for the callers that assert a certain minimum size for
	 *	returned view. If the id is not to be found and a factory is 
	 *	provided then it is asked for a default for this ID.
	 *	If that does not work the DNAView will be invalid.
	 *
	 *	If the id is found but its size is smaller than requested a new
	 *	portion large enough is allocated at the end of the dna array. Old 
	 *	values are copied in their respective spots and new spots are filled
	 *	by requesting the averageDNA values from the factory.
	 */
	DNAView			getView			( ID id, int sz, Factory * f = NULL );
	
	//! get the kind
	ID				kind			( void ) const;
	
	//! energy cost
	quint64			cost			( void ) const
	{ 
		Q_ASSERT(values_i_.length() >= OffMax ); 
		return values_i_.at( OffCost ); 
	}
	
	//! average age for this kind of actor
	quint64			age				( void ) const
	{
		Q_ASSERT(values_i_.length() >= OffMax ); 
		return values_i_.at( OffAge ); 
	}
	
	//! birth energy
	quint64			energy			( void ) const
	{ 
		Q_ASSERT(values_i_.length() >= OffMax ); 
		return values_i_.at( OffStartEnergy );
	}
	
	//! get the list of brains
	QList<ID>		brains			( void ) const;
	
	//! get the list of actuators
	QList<ID>		actuators		( void ) const;
	
	//! get the list of sensors
	QList<ID>		sensors			( void ) const;
	
	//! get the list of reflexes
	QList<ID>		reflexes		( void ) const;
	
	//! list of regions that partition the list of values
	QVector<Partition>	partitions	( void ) const
	{ return parts_; }

	///@}
	/* ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo */
	
	
	/* OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO */
	/** @name add components
	 */
	///@{
	
	//! append a brain
	/**
	 * May fail because id is invalid. The id is inserted in
	 * the list and will be shown by a call to brains().
	 * @param id the ID to insert (different than InvalidID)
	 * @return true for success
	 */
	bool			addBrain		( ID id );
	
	//! append an actuator
	/**
	 * May fail because id is invalid. The id is inserted in
	 * the list and will be shown by a call to actuators().
	 * @param id the ID to insert (different than InvalidID)
	 * @return true for success
	 */
	bool			addActuator		( ID id );
	
	//! append a sensor
	/**
	 * May fail because id is invalid. The id is inserted in
	 * the list and will be shown by a call to sensors().
	 * @param id the ID to insert (different than InvalidID)
	 * @return true for success
	 */
	bool			addSensor		( ID id );
	
	//! append a reflex
	/**
	 * May fail because id is invalid. The id is inserted in
	 * the list and will be shown by a call to reflexes().
	 * @param id the ID to insert (different than InvalidID)
	 * @return true for success
	 */
	bool			addReflex		( ID id );
	
	
	///@}
	/* ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo */
	
	
	
	//! save the content of this DNA to indicated object
	bool			save			( QSettings & stg ) const;
	
	//! load the content of this DNA from indicated object
	bool			load			( QSettings & stg );
	
	
	//! the level of noise to add to copy opperations
	static qreal	dnaNoise		( void );
	
	
	//! get the index of the ID or -1 if not found
	int				findID			( ID id ) const;
	
	//! initialise an empty DNA; the instance becomes valid
	/**
	 * This is usefull for ActorFactory to create a default DNA
	 * @param init initial data
	 */
	void			initDNA			( const InitData & init );
	
	//! set components and characteristics for source DNA
	/**
	 * 
	 * @param src source DNA (values are copied from this one
	 * @param clear_content should we clear \b values_ and \b parts_ ?
	 */
	void			reinitDNA		( const DNA & src, bool clear_content );

	
	/* OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO */
	/** @name Merge helpers
	 */
	///@{
	
private:
	
	bool			mergeAllVals	(
			const DNA &			p1,
			const DNA &			p2
			);
	
	int				mergeUniteEl	(
			int					iter_1,
			int					iter_2,
			int					i_max_1,
			int					i_max_2,
			const DNA &			p1,
			const DNA &			p2
			);
	
	bool			mergeBrains		(
			const DNA &			p1,
			const DNA &			p2
			);
	
	void			mergeAllParts	(
			const DNA &			p1,
			const DNA &			p2
			);
	
	void			mergeParts		(
			const Partition &	part_1, 
			const Partition &	part_2, 
			const DNA &			p1, 
			const DNA &			p2
			);
	
	void			mergePart		(
			const Partition &	part,
			const DNA &			p
			);
	
	
	///@}
	/* ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo */
	
	
#ifdef APRIL_INTERNAL_TESTS
public:
	void			setParts				( QVector<Partition> & new_val )
	{ parts_ = new_val; }
	void			setValues				( QList<qreal> & new_val )
	{ values_ = new_val; }
	void			setValuesI				( QList<quint64> & new_val )
	{ values_i_ = new_val; }
#endif
	
private:
	
	//! helper for getView()
	bool			getViewNotFound			(
			DNAView &			view,
			ID					id,
			Factory *			f
			);
	
	
	/*  FUNCTIONS    ======================================================= */
	//
	//
	//
	//
	
};	/*	class DNA	*/

/*  CLASS    =============================================================== */
//
//
//
//

}   //  namespace   april

#endif // __DNA_INC__
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
