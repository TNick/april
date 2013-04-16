/* ========================================================================= */
/* ------------------------------------------------------------------------- */
/*!
  \file			amodid.h
  \date			Apr 2013
  \author		TNick

  \brief		Contains the definition for AModId class


*//*


 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Please read COPYING and README files in root folder
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
#ifndef __AMODID_INC__
#define __AMODID_INC__
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
*	@brief	Module that provides commands related to IDs
*/
class
	APRILSHARED_EXPORT
	AModId		: public AprilModule		{
	BBM_TRACK( AModId );

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
	AModId			( CommandMap * cmd_map );

protected:

	//! destructor;
	virtual			~AModId		( void );

	//! insert all commands
	virtual void		insertCommands	( CommandMap * cm );

	//! remove all commands
	virtual void		removeCommands	( CommandMap * cm );
	
	//! tell your name
	virtual QString		name			( void );

private:

	//! create a new id in current world
	static bool			newID			(
			const QString &			s_cmd,
			const AaTkString &		atks,
			QString &				s_err
			);
			
	//! list the ids of DNA in this world
	static bool			listID			(
			const QString &			s_cmd,
			const AaTkString &		atks,
			QString &				s_err
			);
			
	//! information about a particular DNA
	static bool			infoID			(
			const QString &			s_cmd,
			const AaTkString &		atks,
			QString &				s_err
			);

	/*  FUNCTIONS    ======================================================= */
	//
	//
	//
	//
	
};	/*	class AModId	*/

/*  CLASS    =============================================================== */
//
//
//
//

}   //  namespace   april

#endif // __AMODID_INC__
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
