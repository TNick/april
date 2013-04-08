/* ========================================================================= */
/* ------------------------------------------------------------------------- */
/*!
  \file			component.h
  \date			Apr 2013
  \author		TNick

  \brief		Contains the definition for Component class


*//*


 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Please read COPYING and README files in root folder
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
#ifndef __COMPONENT_INC__
#define __COMPONENT_INC__
//
//
//
//
/*  INCLUDES    ------------------------------------------------------------ */

#include    <april/april.h>
#include	<libbbb/1/list2d.h>
#include	<libbbb/1/amorph.h>
#include	<april/logic/uniqueid.h>

/*  INCLUDES    ============================================================ */
//
//
//
//
/*  DEFINITIONS    --------------------------------------------------------- */

class	QSettings;

namespace   april    {

/*  DEFINITIONS    ========================================================= */
//
//
//
//
/*  CLASS    --------------------------------------------------------------- */

/**
*	@brief	Base class for various components
*
*	Components may be chained in a linked list as they inherit List2De; also,
*	they are reference-counted.
*/
class
	APRILSHARED_EXPORT
	Component		: public List2De, public libbbb::RefCnt, public MemTrack		{
	BBM_TRACK( Component );

	//
	//
	//
	//
	/*  DEFINITIONS    ----------------------------------------------------- */

	friend class AprilLibrary;
	friend class World;
	friend class Actor;
	
	/*  DEFINITIONS    ===================================================== */
	//
	//
	//
	//
	/*  DATA    ------------------------------------------------------------ */

private:

	//! associated data
	Amorph					payload_;

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
	Component			( void );

protected:

	/**
	*	@brief	destructor;
	*/
	virtual				~Component				( void );

public:

	//! associated data
	Amorph &			payload					( void )
	{ return payload_; }

	//! associated ID, if any
	virtual ID			identificator			( void )
	{ return InvalidId; }

	//! save to a QSettings object
	virtual bool		save					( QSettings & s ) const = 0;
	
	//! load from a QSettings object
	virtual bool		load					( QSettings & s ) = 0;

protected:
	
	//! the instance is informed that the parent attached it
	/**
	 *	The method signals that insertion process ended succesfully.
	 */
	virtual void		inserted				( void )
	{ }

	

	/*  FUNCTIONS    ======================================================= */
	//
	//
	//
	//

};	/*	class Component	*/

/*  CLASS    =============================================================== */
//
//
//
//

}   //  namespace   april

#endif // __COMPONENT_INC__
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
