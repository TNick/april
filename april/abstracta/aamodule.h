/* ========================================================================= */
/* ------------------------------------------------------------------------- */
/*!
  \file			aamodule.h
  \date			Apr 2013
  \author		TNick

  \brief		Contains the definition for AaModule class


*//*


 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Please read COPYING and README files in root folder
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
#ifndef __AAMODULE_INC__
#define __AAMODULE_INC__
//
//
//
//
/*  INCLUDES    ------------------------------------------------------------ */

#include    <april/april.h>
#include	<libbbb/1/refcnt.h>

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
*	@brief	Base class for all modules
*/
class AaModule		: public libbbb::RefCnt, public MemTrack		{
	BBM_TRACK( AaModule );

	//
	//
	//
	//
	/*  DEFINITIONS    ----------------------------------------------------- */

friend class AbstractApril;

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
	AaModule			( void );

protected:

	//! destructor;
	virtual				~AaModule		( void );

protected:

	//! insert all commands (request from AbstractApril)
	virtual void		insertCommands	( void ) = 0;

	//! remove all commands (request from AbstractApril)
	virtual void		removeCommands	( void ) = 0;

	//! tell your name
	virtual QString		name			( void ) = 0;

	/*  FUNCTIONS    ======================================================= */
	//
	//
	//
	//

};	/*	class AaModule	*/

/*  CLASS    =============================================================== */
//
//
//
//

}   //  namespace   april

#endif // __AAMODULE_INC__
/* ------------------------------------------------------------------------- */
/* ========================================================================= */