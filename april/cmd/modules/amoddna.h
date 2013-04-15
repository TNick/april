/* ========================================================================= */
/* ------------------------------------------------------------------------- */
/*!
  \file			amoddna.h
  \date			Apr 2013
  \author		TNick

  \brief		Contains the definition for AModDNA class


*//*


 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Please read COPYING and README files in root folder
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
#ifndef __AMODDNA_INC__
#define __AMODDNA_INC__
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
*	@brief	Module that provides commands related to DNA
*/
class
	APRILSHARED_EXPORT
	AModDNA		: public AprilModule		{
	BBM_TRACK( AModDNA );

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
	AModDNA				( CommandMap * cmd_map );

protected:

	//! destructor;
	virtual				~AModDNA			( void );

	//! insert all commands
	virtual void		insertCommands	( CommandMap * cm );

	//! remove all commands
	virtual void		removeCommands	( CommandMap * cm );
	
	//! tell your name
	virtual QString		name			( void );
	
private:

	//! create a new kind in current world
	static bool			newDNA			(
			const QString &			s_cmd,
			const AaTkString &		atks,
			QString &				s_err
			);
			
	//! list the kinds of DNA in this world
	static bool			listDNA			(
			const QString &			s_cmd,
			const AaTkString &		atks,
			QString &				s_err
			);
			
	//! add a sensor to an existing kind
	static bool			sDNA		(
			const QString &			s_cmd,
			const AaTkString &		atks,
			QString &				s_err
			);
			
	//! add a actuator to an existing kind
	static bool			aDNA		(
			const QString &			s_cmd,
			const AaTkString &		atks,
			QString &				s_err
			);
			
	//! add a brain to an existing kind
	static bool			bDNA		(
			const QString &			s_cmd,
			const AaTkString &		atks,
			QString &				s_err
			);
			
	//! add a reflex to an existing kind
	static bool			rDNA		(
			const QString &			s_cmd,
			const AaTkString &		atks,
			QString &				s_err
			);



	/*  FUNCTIONS    ======================================================= */
	//
	//
	//
	//

};	/*	class AModDNA	*/

/*  CLASS    =============================================================== */
//
//
//
//

}   //  namespace   april

#endif // __AMODDNA_INC__
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
