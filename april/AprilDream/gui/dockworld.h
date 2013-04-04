/* ========================================================================= */
/* ------------------------------------------------------------------------- */
/*!
  \file			dockworld.h
  \date			Apr 2013
  \author		TNick

  \brief		Contains the definition for DockWorld class


*//*


 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Please read COPYING and README files in root folder
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
#ifndef __DOCKWORLD_INC__
#define __DOCKWORLD_INC__
//
//
//
//
/*  INCLUDES    ------------------------------------------------------------ */

#include    <april/april.h>
#include    <april/AprilDream/gui/dock.h>

/*  INCLUDES    ============================================================ */
//
//
//
//
/*  DEFINITIONS    --------------------------------------------------------- */

namespace   april	{

namespace	Gui		{

class	MW;
class	DockWorld_p;

/*  DEFINITIONS    ========================================================= */
//
//
//
//
/*  CLASS    --------------------------------------------------------------- */

/**
*	@brief	Informations about the world
*/
class DockWorld		: public Dock		{
	BBM_TRACK( DockWorld );

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

	//! data only allocated when visible
	DockWorld_p *		d_;


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
	DockWorld			( MW * mw );

	/**
	*	@brief	destructor;
	*/
	virtual				~DockWorld				( void );

protected:

	//! used to construct the widget
	void				construct				( void );

	//! used to destruct the widget
	void				deconstruct				( void );


	/*  FUNCTIONS    ======================================================= */
	//
	//
	//
	//

};	/*	class DockWorld	*/

/*  CLASS    =============================================================== */
//
//
//
//

}   //  namespace   Gui
}   //  namespace   april

#endif // __DOCKWORLD_INC__
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
