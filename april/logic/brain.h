/* ========================================================================= */
/* ------------------------------------------------------------------------- */
/*!
  \file			brain.h
  \date			Apr 2013
  \author		TNick

  \brief		Contains the definition for Brain class


*//*


 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Please read COPYING and README files in root folder
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
#ifndef __BRAIN_INC__
#define __BRAIN_INC__
//
//
//
//
/*  INCLUDES    ------------------------------------------------------------ */

#include    <april/april.h>
#include    <april/logic/component.h>

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
	Brain		: public Component		{
	BBM_TRACK( Brain );

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


	/**
	*	@brief	constructor;
	*/
	Brain			( void );


	/**
	*	@brief	destructor;
	*/
	virtual				~Brain		( void );



	/*  FUNCTIONS    ======================================================= */
	//
	//
	//
	//

};	/*	class Brain	*/

/*  CLASS    =============================================================== */
//
//
//
//

}   //  namespace   april

#endif // __BRAIN_INC__
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
