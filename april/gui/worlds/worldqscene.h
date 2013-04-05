/* ========================================================================= */
/* ------------------------------------------------------------------------- */
/*!
  \file			worldqscene.h
  \date			Apr 2013
  \author		TNick

  \brief		Contains the definition for WorldQScene class


*//*


 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Please read COPYING and README files in root folder
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
#ifndef __WORLDQSCENE_INC__
#define __WORLDQSCENE_INC__
//
//
//
//
/*  INCLUDES    ------------------------------------------------------------ */

#include    <april/april.h>
#include    <QGraphicsScene>
#include	<april/logic/world.h>

/*  INCLUDES    ============================================================ */
//
//
//
//
/*  DEFINITIONS    --------------------------------------------------------- */

namespace   april	{

namespace   Gui		{

/*  DEFINITIONS    ========================================================= */
//
//
//
//
/*  CLASS    --------------------------------------------------------------- */

/**
*	@brief	A world in a QGraphicsScene
*/
class
	APRILSHARED_EXPORT
	WorldQScene		: public QGraphicsScene, public MemTrack		{
	BBM_TRACK( WorldQScene );

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

	//! the world
	World *			w_;

	/*  DATA    ============================================================ */
	//
	//
	//
	//
	/*  FUNCTIONS    ------------------------------------------------------- */

public:


	//! constructor;
	WorldQScene			( QObject * parent = NULL );

	//! destructor;
	virtual				~WorldQScene		( void );

	//! underlying world object
	inline World *		world				( void ) const 
	{ return w_; }


	/*  FUNCTIONS    ======================================================= */
	//
	//
	//
	//

};	/*	class WorldQScene	*/

/*  CLASS    =============================================================== */
//
//
//
//

}   //  namespace Gui

}   //  namespace april

#endif // __WORLDQSCENE_INC__
/* ------------------------------------------------------------------------- */
/* ========================================================================= */