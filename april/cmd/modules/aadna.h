/* ========================================================================= */
/* ------------------------------------------------------------------------- */
/*!
  \file			aadna.h
  \date			Apr 2013
  \author		TNick

  \brief		Contains the definition for AaDNA class


*//*


 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Please read COPYING and README files in root folder
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
#ifndef __AADNA_INC__
#define __AADNA_INC__
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
*	@brief	Module that provides commands related to DNA
*/
class
	APRILSHARED_EXPORT
	AaDNA		: public AaModule		{
	BBM_TRACK( AaDNA );

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
	AaDNA				( CommandMap * cmd_map );

protected:

	//! destructor;
	virtual				~AaDNA			( void );

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



	/*  FUNCTIONS    ======================================================= */
	//
	//
	//
	//

};	/*	class AaDNA	*/

/*  CLASS    =============================================================== */
//
//
//
//

}   //  namespace   april

#endif // __AADNA_INC__
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
