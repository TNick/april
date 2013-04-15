/* ========================================================================= */
/* ------------------------------------------------------------------------- */
/*!
  \file			amodapril.h
  \date			Apr 2013
  \author		TNick

  \brief		Contains the definition for AModApril class


*//*


 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Please read COPYING and README files in root folder
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
#ifndef __AMODAPRIL_INC__
#define __AMODAPRIL_INC__
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
*	@brief	Module that provides commands related to introspection
*/
class
	APRILSHARED_EXPORT
	AModApril		: public AprilModule		{
	BBM_TRACK( AModApril );

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
	AModApril			( CommandMap * cmd_map );

protected:

	//! destructor;
	virtual				~AModApril		( void );

	//! insert all commands
	virtual void		insertCommands	( CommandMap * cm );

	//! remove all commands
	virtual void		removeCommands	( CommandMap * cm );
	
	//! tell your name
	virtual QString		name			( void );

private:

	//! list all registered commands
	static bool			commands		(
			const QString &			s_cmd,
			const AaTkString &		atks,
			QString &				s_err
			);

	//! list all registered modules
	static bool			modules			(
			const QString &			s_cmd,
			const AaTkString &		atks,
			QString &				s_err
			);

	//! prints the version
	static bool			version			(
			const QString &			s_cmd,
			const AaTkString &		atks,
			QString &				s_err
			);

	//! informs about the copyright
	static bool			copyright			(
			const QString &			s_cmd,
			const AaTkString &		atks,
			QString &				s_err
			);

	//! change the prompt to specified string
	static bool			prompt			(
			const QString &			s_cmd,
			const AaTkString &		atks,
			QString &				s_err
			);


	/*  FUNCTIONS    ======================================================= */
	//
	//
	//
	//

};	/*	class AModApril	*/

/*  CLASS    =============================================================== */
//
//
//
//

}   //  namespace   april

#endif // __AMODAPRIL_INC__
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
