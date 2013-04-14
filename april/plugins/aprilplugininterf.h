/* ========================================================================= */
/* ------------------------------------------------------------------------- */
/*!
  \file			aprilplugininterf.h
  \date			Apr 2013
  \author		TNick

  \brief		Contains the definition for AprilPluginInterf class


*//*


 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Please read COPYING and README files in root folder
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
#ifndef __APRILPLUGININTERF_INC__
#define __APRILPLUGININTERF_INC__
//
//
//
//
/*  INCLUDES    ------------------------------------------------------------ */

#include    <april/april.h>
#include    <libbbb/1/list2d.h>
#include	<QtPlugin>
#include	<QPluginLoader>

/*  INCLUDES    ============================================================ */
//
//
//
//
/*  DEFINITIONS    --------------------------------------------------------- */

//! class to load and manage plug-ins
class
	APRILSHARED_EXPORT
	AprilPluginLoader	: public QPluginLoader, public List2De, public MemTrack {
	BBM_TRACK( AprilPluginInterf );
public:
	//! constructor
	AprilPluginLoader( const QString & s ) : QPluginLoader( s ), List2De(), MemTrack()
	{}
	
	//! the name of the plug-in if loaded, otherwise an empty string
	QString			name					( void );
	
};

namespace april {
class	AprilLibrary;
}

/*  DEFINITIONS    ========================================================= */
//
//
//
//
/*  CLASS    --------------------------------------------------------------- */

/**
*	@brief	Interface for plugins used with April
*/
class
	APRILSHARED_EXPORT
	AprilPluginInterf		: public QObject, public MemTrack		{
	BBM_TRACK( AprilPluginInterf );

	//
	//
	//
	//
	/*  DEFINITIONS    ----------------------------------------------------- */

	friend class april::AprilLibrary;

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
	AprilPluginInterf							( void );

	//! destructor;
	virtual				~AprilPluginInterf		( void );

	//! identify yourself;
	virtual QString 	name					( void ) = 0;
	
protected:

	//! called after the plug-in is loaded
	/**
	 * The plug-in system allows initialisation after the
	 * plug-in is succesfully loaded. The plug-in may initialise
	 * itself and, if certain errors occur it may return false
	 * to indicate to the system that it failed and should 
	 * be unloaded.
	 *
	 * @return true to keep the plug-in, false to unload
	 */
	virtual bool		initialised	( void )
	{ return true; }
	
	//! called before the plug-in is unloaded
	/**
	 * This method is called only if initialised() returned true.
	 */
	virtual void		unloading	( void )
	{}

	/*  FUNCTIONS    ======================================================= */
	//
	//
	//
	//

};	/*	class AprilPluginInterf	*/

/*  CLASS    =============================================================== */
//
//
//
//

Q_DECLARE_INTERFACE(AprilPluginInterf,  "org.april.PluginInterface/1.0")

#endif // __APRILPLUGININTERF_INC__
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
