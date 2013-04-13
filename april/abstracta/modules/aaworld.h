/* ========================================================================= */
/* ------------------------------------------------------------------------- */
/*!
  \file			aaworld.h
  \date			Apr 2013
  \author		TNick

  \brief		Contains the definition for AaWorld class


*//*


 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Please read COPYING and README files in root folder
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
#ifndef __AAWORLD_INC__
#define __AAWORLD_INC__
//
//
//
//
/*  INCLUDES    ------------------------------------------------------------ */

#include    <april/april.h>
#include    <april/abstracta/aamodule.h>

/*  INCLUDES    ============================================================ */
//
//
//
//
/*  DEFINITIONS    --------------------------------------------------------- */

namespace   april    {

class	AaTkString;

/*  DEFINITIONS    ========================================================= */
//
//
//
//
/*  CLASS    --------------------------------------------------------------- */

/**
*	@brief	Provides commands related to worlds
*/
class AaWorld		: public AaModule		{
	BBM_TRACK( AaWorld );

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
	AaWorld				( void );

	//! destructor;
	virtual				~AaWorld		( void );
	
protected:

	//! insert all commands (request from AbstractApril)
	virtual void		insertCommands	( void );

	//! remove all commands (request from AbstractApril)
	virtual void		removeCommands	( void );
	
	//! tell your name
	virtual QString		name			( void );


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
	static bool			listWorlds		(
			const QString &			s_cmd,
			const AaTkString &		atks,
			QString &				s_err
			);
			
			
	
	/*  FUNCTIONS    ======================================================= */
	//
	//
	//
	//

};	/*	class AaWorld	*/

/*  CLASS    =============================================================== */
//
//
//
//

}   //  namespace   april

#endif // __AAWORLD_INC__
/* ------------------------------------------------------------------------- */
/* ========================================================================= */