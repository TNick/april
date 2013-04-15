/* ========================================================================= */
/* ------------------------------------------------------------------------- */
/*!
  \file			aaplugins.h
  \date			Apr 2013
  \author		TNick

  \brief		Contains the definition for AaPlugIns class


*//*


 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Please read COPYING and README files in root folder
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
#ifndef __AAPLUGINS_INC__
#define __AAPLUGINS_INC__
//
//
//
//
/*  INCLUDES    ------------------------------------------------------------ */

#include    <april/april.h>
#include    <april/cmd/aamodule.h>

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
	AaPlugIns		: public AaModule		{
	BBM_TRACK( AaPlugIns );

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
	AaPlugIns			( CommandMap * cmd_map );

protected:

	//! destructor;
	virtual				~AaPlugIns		( void );

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

};	/*	class AaPlugIns	*/

/*  CLASS    =============================================================== */
//
//
//
//

}   //  namespace   april

#endif // __AAPLUGINS_INC__
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
