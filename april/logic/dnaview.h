/* ========================================================================= */
/* ------------------------------------------------------------------------- */
/*!
  \file			dnaview.h
  \date			Apr 2013
  \author		TNick

  \brief		Contains the definition for DNAView class


*//*


 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Please read COPYING and README files in root folder
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
#ifndef __DNAVIEW_INC__
#define __DNAVIEW_INC__
//
//
//
//
/*  INCLUDES    ------------------------------------------------------------ */

#include    <april/april.h>
#include	<april/logic/uniqueid.h>

/*  INCLUDES    ============================================================ */
//
//
//
//
/*  DEFINITIONS    --------------------------------------------------------- */

namespace   april    {

class	DNA;

/*  DEFINITIONS    ========================================================= */
//
//
//
//
/*  CLASS    --------------------------------------------------------------- */

/**
*	@brief	Provides access to an ID tagged portion of the DNA
*/
class
	APRILSHARED_EXPORT
	DNAView				{

	//
	//
	//
	//
	/*  DEFINITIONS    ----------------------------------------------------- */

	friend class DNA;

	/*  DEFINITIONS    ===================================================== */
	//
	//
	//
	//
	/*  DATA    ------------------------------------------------------------ */

private:


	//! the unique ID of the component
	ID				id_;
	
	//! index of the first value
	int				start_;
	
	//! number of values
	int				count_;
	
	//! the source DNA
	const DNA *		dna_;


	/*  DATA    ============================================================ */
	//
	//
	//
	//
	/*  FUNCTIONS    ------------------------------------------------------- */

public:


	//! constructs a view based on provided ID
	/**
	 * If the ID is not present in the DNA structure
	 * the view will be invalid.
	 *
	 * @param dna	where to look
	 * @param id	the ID to search
	 */
	DNAView ( const DNA * dna, ID id );

	/**
	*	@brief	destructor;
	*/
	~DNAView		( void );

	
	//! tell if this structure is valid or not
	bool			isValid				( void ) const
	{ return id_ == InvalidId; }
	
	//! get the value at index i
	qreal			value				( int i ) const;

protected:

	//! the unique ID of the component
	inline ID		identificator		( void ) const
	{ return id_; }
	
	//! index of the first value
	inline int		begin				( void ) const 
	{ return start_; }
	
	//! number of values
	inline int		count				( void ) const
	{ return count_; }
	
	//! the source DNA
	inline const DNA *	source			( void ) const
	{ return dna_; }


	//! set the unique ID of the component
	inline void		setIdentificator	( ID id )
	{ id_ = id; }
	
	//! set index of the first value
	inline void		setBegin			( int val )
	{ start_ = val; }

	//! set number of values
	inline void		setCount			( int val )
	{ count_ = val; }
	
	//! set the source DNA
	void			setDNA				( const DNA * d );


	/*  FUNCTIONS    ======================================================= */
	//
	//
	//
	//

};	/*	class DNAView	*/

/*  CLASS    =============================================================== */
//
//
//
//

}   //  namespace   april

#endif // __DNAVIEW_INC__
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
