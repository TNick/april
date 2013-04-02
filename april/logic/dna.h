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

private:

	//! an entry in the list of partitions
	struct	Partition {
		
		//! the unique ID of the component
		ID			id_;
		
		//! index of the first value
		int			start_;
		
		//! number of values
		int			count_;
	};
	
public:
	
	//! offsets for predefined values
	enum	Predef	{
		OffKind = 0,	/**< the kind - ID */
		OffBrains,		/**< number of brains in the list that follows */
		OffActuators,	/**< number of actuators in the list that follows */
		OffSensors,		/**< number of sensors in the list that follows */
		OffReflexes,	/**< number of reflexes in the list that follows */
		
		OffMax
		/* the list of brains, actuators, sensors, reflex id's follows */
	};

	/*  DEFINITIONS    ===================================================== */
	//
	//
	//
	//
	/*  DATA    ------------------------------------------------------------ */

private:

	//! list of regions that partition the list of values
	QVector<Partition>			parts_;

protected:
	
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
	*	@brief	constructor;
	*/
	DNA					( void );


	/**
	*	@brief	destructor;
	*/
	~DNA				( void );


	//! get a view for a particular id
	/**
	 *	If the id is not to be found the DNAView will be invalid
	 */
	DNAView			getView			( ID id );
	
	//! set the DNA as a result of the two parents
	void			fromMerge		(
			const DNA &			p1,
			const DNA &			p2
			);
	
protected:

	//! get the index of the ID or -1 if not found
	int				findID			( ID id ) const;


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
