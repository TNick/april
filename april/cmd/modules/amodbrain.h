/* ========================================================================= */
/* ------------------------------------------------------------------------- */
/*!
  \file			amodbrain.h
  \date			Apr 2013
  \author		TNick

  \brief		Contains the definition for AModBrain class


*//*


 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Please read COPYING and README files in root folder
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
#ifndef __AMODBRAIN_INC__
#define __AMODBRAIN_INC__
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
*	@brief	Module that provides commands related to brains
*/
class AModBrain		: public AprilModule		{
	BBM_TRACK( AModBrain );

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
	AModBrain			( CommandMap * cmd_map );

protected:

	//! destructor;
	virtual				~AModBrain		( void );

	//! insert all commands
	virtual void		insertCommands	( CommandMap * cm );

	//! remove all commands
	virtual void		removeCommands	( CommandMap * cm );
	
	//! tell your name
	virtual QString		name			( void );

private:

	//! create a new component
	static bool			newBrain		(
			const QString &			s_cmd,
			const AaTkString &		atks,
			QString &				s_err
			);

	//! list existing components
	static bool			listBrain		(
			const QString &			s_cmd,
			const AaTkString &		atks,
			QString &				s_err
			);

	//! list available components
	static bool			kindsBrain		(
			const QString &			s_cmd,
			const AaTkString &		atks,
			QString &				s_err
			);


	/*  FUNCTIONS    ======================================================= */
	//
	//
	//
	//

};	/*	class AModBrain	*/

/*  CLASS    =============================================================== */
//
//
//
//

}   //  namespace   april

#endif // __AMODBRAIN_INC__
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
