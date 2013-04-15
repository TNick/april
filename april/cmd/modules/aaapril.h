/* ========================================================================= */
/* ------------------------------------------------------------------------- */
/*!
  \file			aaapril.h
  \date			Apr 2013
  \author		TNick

  \brief		Contains the definition for AaApril class


*//*


 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Please read COPYING and README files in root folder
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
#ifndef __AAAPRIL_INC__
#define __AAAPRIL_INC__
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
*	@brief	Module that provides commands related to introspection
*/
class
	APRILSHARED_EXPORT
	AaApril		: public AaModule		{
	BBM_TRACK( AaApril );

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
	AaApril			( CommandMap * cmd_map );

protected:

	//! destructor;
	virtual				~AaApril		( void );

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

};	/*	class AaApril	*/

/*  CLASS    =============================================================== */
//
//
//
//

}   //  namespace   april

#endif // __AAAPRIL_INC__
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
