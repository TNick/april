/* ========================================================================= */
/* ------------------------------------------------------------------------- */
/*!
  \file			amodactor.h
  \date			Apr 2013
  \author		TNick

  \brief		Contains the definition for AModActor class


*//*


 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Please read COPYING and README files in root folder
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
#ifndef __AMODACTOR_INC__
#define __AMODACTOR_INC__
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
*	@brief
*/
class
	APRILSHARED_EXPORT
	AModActor		: public AprilModule		{
	BBM_TRACK( AModActor );

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
	AModActor			( CommandMap * cmd_map );

protected:

	//! destructor;
	virtual				~AModActor		( void );

	//! insert all commands
	virtual void		insertCommands	( CommandMap * cm );

	//! remove all commands
	virtual void		removeCommands	( CommandMap * cm );
	
	//! tell your name
	virtual QString		name			( void );

private:

	//! list all registered commands
	static bool			newActor		(
			const QString &			s_cmd,
			const AaTkString &		atks,
			QString &				s_err
			);

	//! list all registered modules
	static bool			listActor		(
			const QString &			s_cmd,
			const AaTkString &		atks,
			QString &				s_err
			);

	//! prints the version
	static bool			killActor		(
			const QString &			s_cmd,
			const AaTkString &		atks,
			QString &				s_err
			);

	/*  FUNCTIONS    ======================================================= */
	//
	//
	//
	//

};	/*	class AModActor	*/

/*  CLASS    =============================================================== */
//
//
//
//

}   //  namespace   april

#endif // __AMODACTOR_INC__
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
