/* ========================================================================= */
/* ------------------------------------------------------------------------- */
/*!
  \file			amodworld.h
  \date			Apr 2013
  \author		TNick

  \brief		Contains the definition for AModWorld class


*//*


 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Please read COPYING and README files in root folder
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
#ifndef __AMODWORLD_INC__
#define __AMODWORLD_INC__
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
*	@brief	Module that provides commands related to worlds
*/
class
	APRILSHARED_EXPORT
	AModWorld		: public AprilModule		{
	BBM_TRACK( AModWorld );

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
	AModWorld				( CommandMap * cmd_map );

protected:

	//! destructor;
	virtual				~AModWorld		( void );
	
protected:

	//! insert all commands
	virtual void		insertCommands	( CommandMap * cm );

	//! remove all commands
	virtual void		removeCommands	( CommandMap * cm );
	
	//! tell your name
	virtual QString		name			( void );


public:

	//! directly open a world from a file
	static bool			dOpenWorld		(
			const QString &			s_file,
			QString &				s_err			
			);

private:

	//! create a new world
	static bool			newWorld		(
			const QString &			s_cmd,
			const AaTkString &		atks,
			QString &				s_err
			);

	//! open a world
	static bool			openWorld		(
			const QString &			s_cmd,
			const AaTkString &		atks,
			QString &				s_err
			);

	//! save a world
	static bool			saveWorld		(
			const QString &			s_cmd,
			const AaTkString &		atks,
			QString &				s_err
			);

	//! close a world
	static bool			closeWorld		(
			const QString &			s_cmd,
			const AaTkString &		atks,
			QString &				s_err
			);

	//! list all worlds
	static bool			listWorld		(
			const QString &			s_cmd,
			const AaTkString &		atks,
			QString &				s_err
			);
			
	//! start a world
	static bool			startWorld		(
			const QString &			s_cmd,
			const AaTkString &		atks,
			QString &				s_err
			);
			
	//! stop a world
	static bool			stopWorld		(
			const QString &			s_cmd,
			const AaTkString &		atks,
			QString &				s_err
			);
			
	//! advance a world
	static bool			advWorld		(
			const QString &			s_cmd,
			const AaTkString &		atks,
			QString &				s_err
			);
			
	//! change current world
	static bool			crtWorld		(
			const QString &			s_cmd,
			const AaTkString &		atks,
			QString &				s_err
			);
			
			
			
	
	/*  FUNCTIONS    ======================================================= */
	//
	//
	//
	//

};	/*	class AModWorld	*/

/*  CLASS    =============================================================== */
//
//
//
//

}   //  namespace   april

#endif // __AMODWORLD_INC__
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
