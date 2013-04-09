/* ========================================================================= */
/* ------------------------------------------------------------------------- */
/*!
  \file			worldfactory.h
  \date			Apr 2013
  \author		TNick

  \brief		Contains the definition for WorldFactory class


*//*


 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Please read COPYING and README files in root folder
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
#ifndef __WORLDFACTORY_INC__
#define __WORLDFACTORY_INC__
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

/*  DEFINITIONS    ========================================================= */
//
//
//
//
/*  CLASS    --------------------------------------------------------------- */

/**
*	@brief	Class capable of creating worlds
*/
class
	APRILSHARED_EXPORT
	WorldFactory		: public Factory		{
	BBM_TRACK( WorldFactory );

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

	//! constructor;
	WorldFactory			( const QString & s );

	//! destructor;
	virtual					~WorldFactory		( void );
	
	//! the generic type of the factory
	virtual FactoryType			factoryType		( void )
	{ return FTyWorld; }

	//! create a world; the base class implementation creates a basic World
	virtual World *			create				(
			const QString &			name,
			quint64					tot_energ
			);

	//! create a world from the settings object
	virtual World *			create				( QSettings & stg );


	/*  FUNCTIONS    ======================================================= */
	//
	//
	//
	//

};	/*	class WorldFactory	*/

/*  CLASS    =============================================================== */
//
//
//
//

}   //  namespace   april

#endif // __WORLDFACTORY_INC__
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
