/* ========================================================================= */
/* ------------------------------------------------------------------------- */
/*!
  \file			aprillibrary.h
  \date			Jan 2013
  \author		TNick

  \brief		Contains the definition for AprilLibrary class


*//*


 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Please read COPYING and README files in root folder
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
#ifndef __APRILLIBRARY_INC__
#define __APRILLIBRARY_INC__
//
//
//
//
/*  INCLUDES    ------------------------------------------------------------ */

#include    <april/april.h>
#include    <april/memmng/memmanager.h>
#include    <QObject>
#include    <QSettings>

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
*	@brief	Represents the root structure for the library
*/
class APRILSHARED_EXPORT AprilLibrary		: public QObject, public MemTrack	{
	QPRIL_OBJECT
	BBM_TRACK( AprilLibrary );

	//
	//
	//
	//
	/*  DEFINITIONS    ----------------------------------------------------- */

public:


	/**
	*	@brief	entire set of properties
	*/
	struct		LibProps			{



		void save ( QSettings & s );
		void load ( QSettings & s );
	};


	/*  DEFINITIONS    ===================================================== */
	//
	//
	//
	//
	/*  DATA    ------------------------------------------------------------ */

private:


	/**
	*	@brief	the properties
	*/
	LibProps						props_;

	/**
	*	@brief	memory manager
	*/
	MemManager						mmanager_;

	/**
	*	@brief	the one and only instance
	*/
	static AprilLibrary *			uniq_;


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
	AprilLibrary			( QObject * parent = NULL );


	/**
	*	@brief	destructor;
	*/
	virtual					~AprilLibrary		( void );


	/**
	*	@brief	the one and only instance
	*/
	static AprilLibrary *	unique				( void )
	{ return uniq_; }





	/* ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo */
	/** @name Properties related functionality
	 */
	///@{

public:

	/**
	*	@brief	load properties from permanent storage
	*
	*	The constructor automatically loads properties
	*/
	void					loadProps			( void );


	/**
	*	@brief	save properties to permanent storage
	*
	*	Changes to properties need to be explicitly saved
	*/
	void					saveProps			( void );


	/**
	*	@brief	the properties
	*/
	static LibProps &		properties			( void )
	{ Q_ASSERT( uniq_ != NULL ); return uniq_->props_; }


	///@}
	/* ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo */



	/*  FUNCTIONS    ======================================================= */
	//
	//
	//
	//

};	/*	class AprilLibrary	*/

/*  CLASS    =============================================================== */
//
//
//
//

}   //  namespace   april

/// starts the library
DIGIBSHARED_EXPORT bool	initAprilLibrary			( void );
DIGIBSHARED_EXPORT void	endAprilLibrary				( void );

#endif // __APRILLIBRARY_INC__
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
