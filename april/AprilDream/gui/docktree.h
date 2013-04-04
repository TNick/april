/* ========================================================================= */
/* ------------------------------------------------------------------------- */
/*!
  \file			docktree.h
  \date			Apr 2013
  \author		TNick

  \brief		Contains the definition for DockTree class


*//*


 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Please read COPYING and README files in root folder
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
#ifndef __DOCKTREE_INC__
#define __DOCKTREE_INC__
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
class	DockTree_p;

/*  DEFINITIONS    ========================================================= */
//
//
//
//
/*  CLASS    --------------------------------------------------------------- */

/**
*	@brief	The tree of the world listing all objects
*/
class DockTree		: public Dock		{
	BBM_TRACK( DockTree );

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
	DockTree_p *		d_;


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
	DockTree			( MW * mw );

	/**
	*	@brief	destructor;
	*/
	virtual				~DockTree				( void );

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

};	/*	class DockTree	*/

/*  CLASS    =============================================================== */
//
//
//
//

}   //  namespace   Gui
}   //  namespace   april

#endif // __DOCKTREE_INC__
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
