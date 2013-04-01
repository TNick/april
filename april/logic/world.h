/* ========================================================================= */
/* ------------------------------------------------------------------------- */
/*!
  \file			world.h
  \date			Apr 2013
  \author		TNick

  \brief		Contains the definition for World class


*//*


 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Please read COPYING and README files in root folder
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
#ifndef __WORLD_INC__
#define __WORLD_INC__
//
//
//
//
/*  INCLUDES    ------------------------------------------------------------ */

#include    <april/april.h>

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
	World		: public libbbb::RefCnt, public MemTrack		{
	BBM_TRACK( World );

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

	/**
	*	@brief	running status
	*/
	bool					b_running_:1;
	
	
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
	World				( void );

protected:

	/**
	*	@brief	destructor;
	*/
	virtual				~World		( void );



	/* OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO */
	/** @name Running
	 */
	///@{

public:

	/**
	*	@brief	starts this world
	*/
	bool				start			( void )
	{ b_running_ = true; return true; }


	/**
	*	@brief	stops this world
	*/
	void				stop			( void )
	{ b_running_ = false; }


	/**
	*	@brief	tell if this world is running
	*/
	bool				isRunning		( void )
	{ return b_running_; }


	///@}
	/* ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo */


	/*  FUNCTIONS    ======================================================= */
	//
	//
	//
	//

};	/*	class World	*/

/*  CLASS    =============================================================== */
//
//
//
//

}   //  namespace   april

#endif // __WORLD_INC__
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
