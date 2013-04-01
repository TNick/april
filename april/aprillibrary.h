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
#include    <QObject>
#include    <QSettings>

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
*	@brief	Represents the root structure for the library
*/
class APRILSHARED_EXPORT AprilLibrary		: public QObject, public MemTrack	{
	APRIL_OBJECT
	BBM_TRACK( AprilLibrary );

	//
	//
	//
	//
	/*  DEFINITIONS    ----------------------------------------------------- */

	friend class World;
	

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
	*	@brief	associated worlds
	*/
	QList<World*>					worlds_;

	/**
	*	@brief	default world
	*/
	World*							def_world_;

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



	/* ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo */
	/** @name World related functionality
	 */
	///@{

public:


	/**
	*	@brief	tell if an world is inside the chain
	*/
	static bool		hasWorld			(
			World *			world
			);

	/**
	*	@brief	remove a world
	*/
	static void		remWorld			(
			World *			world
			);

protected:


	/**
	*	@brief	add a world
	*
	*	Do not use directly. This method is used by World constructor to
	*	signal the parent library.
	*/
	static void		addWorld				(
			World *			world
			);

private:


	/**
	*	@brief	adds the world
	*/
	void			internalAddWorld		( World * world );


	/**
	*	@brief	removes the world
	*/
	void			internalRemWorld		( int i, World * world );


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
APRILSHARED_EXPORT bool	initAprilLibrary			( void );
APRILSHARED_EXPORT void	endAprilLibrary				( void );

#endif // __APRILLIBRARY_INC__
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
