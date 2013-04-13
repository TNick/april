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

	//! has a world or is empty
	inline bool			hasWorld			( void ) const 
	{ return w_ != NULL; }

	//! open a world from a file
	/**
	 * The program loads new world and, if succesfull, discards discards 
	 * current world, if any.
	 * The call fails if the world is running.
	 *
	 * @param s_file The file to load
	 * @param s_err Return the errors in this parameter
	 * @return true if the new world was loaded
	 */
	bool				openWorld			 (
			const QString &		s_file,
			QString &			s_err
			);
	
	//! close current world; fails if the world is running
	bool				closeWorld			 ( QString & s_err );

	//! loads provided world
	/**
	 * The call fails if the current world is running.
	 *
	 * @param w The world to load
	 * @param s_err Return the errors in this parameter
	 * @return true if the new world was loaded
	 */
	bool				loadWorld			( World * w, QString & s_err );

	//! save to current file; if none is associated user is asked
	bool				save				( QString & s_err );

	//! save to current file; if none is associated user is asked
	bool				saveAs				( QString & s_err );

	//! associated file
	const QString &		associatedFile		( void ) const
	{ return w_->associatedFile(); }

	//! has associated file
	bool				hasAssociatedFile	( void ) const
	{ return w_->hasAssociatedFile(); }



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
