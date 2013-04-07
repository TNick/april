/* ========================================================================= */
/* ------------------------------------------------------------------------- */
/*!
  \file			sample.h
  \date			Apr 2013
  \author		TNick

  \brief		Contains the definition for Sample class


*//*


 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Please read COPYING and README files in root folder
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
#ifndef __SAMPLEPLUGIN_INC__
#define __SAMPLEPLUGIN_INC__
//
//
//
//
/*  INCLUDES    ------------------------------------------------------------ */

#include    <april/april.h>
#include	<april/plugins/aprilplugininterf.h>

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
*	@brief	Sample plug-in
*/
class Sample		: public AprilPluginInterf		{
	BBM_TRACK( Sample );

	//
	//
	//
	//
	/*  DEFINITIONS    ----------------------------------------------------- */
	
	Q_OBJECT
	Q_INTERFACES(AprilPluginInterf)
#if QT_VERSION >= 0x050000
	Q_PLUGIN_METADATA(IID "org.april.sample" FILE  "sample.json")
#endif
	
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
	Sample							( void );

	//! destructor;
	virtual				~Sample		( void );

	//! identify yourself;
	QString				name		( void )
	{ return tr( "Sample PlugIn" ); }

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
	virtual bool		initialised	( void );
	
	//! called before the plug-in is unloaded
	/**
	 * This method is called only if initialised() returned true.
	 */
	virtual void		unloading	( void );
	
	/*  FUNCTIONS    ======================================================= */
	//
	//
	//
	//

};	/*	class Sample	*/

/*  CLASS    =============================================================== */
//
//
//
//

}   //  namespace   april


#endif // __SAMPLEPLUGIN_INC__
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
