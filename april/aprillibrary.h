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
#include    <QMap>
#include    <libbbb/1/list2d.h>

/*  INCLUDES    ============================================================ */
//
//
//
//
/*  DEFINITIONS    --------------------------------------------------------- */

class	AprilPluginInterf;
class	AprilPluginLoader;

namespace   april    {

class	World;
class	Factory;
class	WorldFactory;

//! callback used to create factories
/**
*	The callback must provide a reference to the caller. The reference is 
*	owned by the Factory.
*/
typedef Factory *		(*FactoryCreator)	( World * w, const QString & s_name );


/*  DEFINITIONS    ========================================================= */
//
//
//
//
/*  CLASS    --------------------------------------------------------------- */

/**
*	@brief	Represents the root structure for the library
*/
class
	APRILSHARED_EXPORT
	AprilLibrary		: public QObject, public MemTrack	{
	APRIL_OBJECT
	BBM_TRACK( AprilLibrary );

	//
	//
	//
	//
	/*  DEFINITIONS    ----------------------------------------------------- */

	friend class World;
	friend class WorldFactory;
	

public:

	//! entire set of properties
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

	//! the properties
	LibProps						props_;

	//! associated worlds
	List2Dh							worlds_;

	//! list of loaded plug-ins
	List2Dh							plugins_;

	//! default world
	World *							def_world_;

	//! world factories
	QMap<QString,WorldFactory*>		world_factories_;

	//! factories creators
	QMap<QString,FactoryCreator>	factories_src_;


	//! the one and only instance
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

	//! the properties
	static LibProps &		properties			( void )
	{ Q_ASSERT( uniq_ != NULL ); return uniq_->props_; }


	///@}
	/* ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo */


	/* ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo */
	/** @name World related functionality
	 */
	///@{

public:

	//! tell if an world is inside the chain
	static bool		hasWorld			(
			World *			world
			);

	//! remove a world
	static void		remWorld			(
			World *			world
			);
	

	//! first world
	static World *			firstWorld		( void );
	
	//! get a unique name for a world
	static QString			uniqueWorldName	( const QString & pattern );
	
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

	//! adds the world
	void			internalAddWorld		( World * world );

	//! removes the world
	void			internalRemWorld		( World * world );


	///@}
	/* ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo */


	/* ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo */
	/** @name Plug-in related functionality
	 */
	///@{

public:

	//! load a plug-in from the file indicated (may be relative to cuurrent directory)
	static AprilPluginInterf *	loadPlugIn			( const QString & s );
	
	//! unload a plug-in based on file name (may be relative to cuurrent directory)
	static bool					unloadPlugIn		( const QString & s );
	
	//! unload a plug-in
	static bool					unloadPlugIn		( AprilPluginInterf * p );
	
	//! get the plug-in for a certain file (must be absolute path)
	static AprilPluginInterf *	findPlugIn			( const QString & s );
	
	//! get the plug-in for a certain file (may be relative to cuurrent directory)
	static AprilPluginInterf *	findPlugInRel		( const QString & s );

	//! first plugin
	static AprilPluginLoader *	firstPlugin			( void );

	///@}
	/* ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo */


	/* ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo */
	/** @name Factory related functionality
	 */
	///@{

public:
	
	//! register a callback for a particular Factory
	static bool					registerFactory		( 
			const QString &			s_name,
			FactoryCreator			callback
			);
	
	//! unregister a callback for a particular Factory
	static bool					unregisterFactory		( 
			const QString &			s_name,
			FactoryCreator			callback
			);

	//! get the name used by the defalt WorldFactory
	static QString				defaultWorldFactoryName	( void );
	
	//! get the factory that coresponds to given string
	static Factory *			factoryForString	(
			World *					w, 
			const QString &			s_name
			);

	//! find a world factory in internal list
	/**
	 * The method does not add a reference; the caller must do that itself
	 * @param s the string to search
	 * @return the pointer or NULL if not found
	 */
	static WorldFactory *		findWorldFactory		(
			const QString &			s
			);
	
protected:

	//! adds a world factory to internal list
	static bool					addWorldFactory		(
			const QString &			s,
			WorldFactory *			inst
			);
			
	//! removes a world factory from internal list
	static bool					remWorldFactory		(
			const QString &			s, 
			WorldFactory *			inst
			);
	
private:

	//! factory creator for default worlds
	/**
	 * The caller recieves a reference to the Factory that it should release 
	 * at some point
	 * @param s_name ignored
	 * @return the factory instance
	 */
	static Factory *			defaultWorldFactoryCreator	( 
			World *				w,
			const QString &		s_name
			);
	
	//! register build-in factories
	void						registerFactoryCreators		( void );

	
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
