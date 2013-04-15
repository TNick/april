/* ========================================================================= */
/* ------------------------------------------------------------------------- */
/*!
  \file			amodplugins.h
  \date			Apr 2013
  \author		TNick

  \brief		Contains the definition for AModPlugIns class


*//*


 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Please read COPYING and README files in root folder
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
#ifndef __AMODPLUGINS_INC__
#define __AMODPLUGINS_INC__
//
//
//
//
/*  INCLUDES    ------------------------------------------------------------ */

#include    <april/april.h>
#include    <april/cmd/aprilmodule.h>

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
*	@brief	Module that provides commands related to plug-ins
*/
class
	APRILSHARED_EXPORT
	AModPlugIns		: public AprilModule		{
	BBM_TRACK( AModPlugIns );

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

	//! constructor
	AModPlugIns			( CommandMap * cmd_map );

protected:

	//! destructor;
	virtual				~AModPlugIns		( void );

	//! insert all commands
	virtual void		insertCommands	( CommandMap * cm );

	//! remove all commands
	virtual void		removeCommands	( CommandMap * cm );
	
	//! tell your name
	virtual QString		name			( void );
	
private:

	//! load a plug-in
	static bool			loadPlugIn		(
			const QString &			s_cmd,
			const AaTkString &		atks,
			QString &				s_err
			);

	//! unload a plug-in
	static bool			unloadPlugIn		(
			const QString &			s_cmd,
			const AaTkString &		atks,
			QString &				s_err
			);

	//! list loaded plug-ins
	static bool			listPlugIn		(
			const QString &			s_cmd,
			const AaTkString &		atks,
			QString &				s_err
			);


	/*  FUNCTIONS    ======================================================= */
	//
	//
	//
	//

};	/*	class AModPlugIns	*/

/*  CLASS    =============================================================== */
//
//
//
//

}   //  namespace   april

#endif // __AMODPLUGINS_INC__
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
