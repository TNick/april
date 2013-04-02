/* ========================================================================= */
/* ------------------------------------------------------------------------- */
/*!
  \file			factory.h
  \date			Apr 2013
  \author		TNick

  \brief		Contains the definition for Factory class


*//*


 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Please read COPYING and README files in root folder
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
#ifndef __FACTORY_INC__
#define __FACTORY_INC__
//
//
//
//
/*  INCLUDES    ------------------------------------------------------------ */

#include    <april/april.h>
#include    <april/logic/uniqueid.h>

/*  INCLUDES    ============================================================ */
//
//
//
//
/*  DEFINITIONS    --------------------------------------------------------- */

namespace   april    {

class	World;

/*  DEFINITIONS    ========================================================= */
//
//
//
//
/*  CLASS    --------------------------------------------------------------- */

/**
*	@brief	Base class for factory classes
*/
class
	APRILSHARED_EXPORT
	Factory		: public libbbb::RefCnt, public MemTrack		{
	BBM_TRACK( Factory );

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

	//! the world where this class is hosted
	World *				w_;

	//! storage space for one name (usually there will only be one)
	QString				s_name_for_id_;

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
	Factory						( World * w );

protected:

	/**
	*	@brief	destructor;
	*/
	virtual						~Factory		( void );

public:

	//! the world that hosts us;
	inline World *				world			( void ) const
	{ return w_; }

	//! name of the element represented by provided ID
	virtual const QString &		name			( ID id ) const
	{ Q_UNUSED( id ); return s_name_for_id_; }

	//! get the default DNA sequence for a particular ID
	virtual QList<qreal>		defaultDNA		( ID id ) const
	{ Q_UNUSED( id ); return QList<qreal>(); }

protected:
	
	//! chang the name of the element represented by provided ID
	void						setName			( const QString & s )
	{ s_name_for_id_ = s; }



	/*  FUNCTIONS    ======================================================= */
	//
	//
	//
	//

};	/*	class Factory	*/

/*  CLASS    =============================================================== */
//
//
//
//

}   //  namespace   april

#endif // __FACTORY_INC__
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
