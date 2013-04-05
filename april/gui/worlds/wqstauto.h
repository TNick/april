/* ========================================================================= */
/* ------------------------------------------------------------------------- */
/*!
  \file			wqstauto.h
  \date			Apr 2013
  \author		TNick

  \brief		Contains the definition for WqsTAuto class


*//*


 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Please read COPYING and README files in root folder
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
#ifndef __WQSTAUTO_INC__
#define __WQSTAUTO_INC__
//
//
//
//
/*  INCLUDES    ------------------------------------------------------------ */

#include    <april/april.h>
#include    <april/gui/worlds/worldqscene.h>

/*  INCLUDES    ============================================================ */
//
//
//
//
/*  DEFINITIONS    --------------------------------------------------------- */

namespace	april	{

namespace	Gui		{

/*  DEFINITIONS    ========================================================= */
//
//
//
//
/*  CLASS    --------------------------------------------------------------- */

/**
*	@brief	A world in a QGraphicsScene with a timer
*/
class
	APRILSHARED_EXPORT
	WqsTAuto		: public WorldQScene		{
	BBM_TRACK( WqsTAuto );

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

	//! counter for updating the gui
	int			update_counter_;
	
	//! number of steps after which the gui is updated
	int			update_len_;
	
	//! frequency of the timer
	int			frequency_;
	
	//! the id of the timer (0 if not running)
	int			timer_id_;

	/*  DATA    ============================================================ */
	//
	//
	//
	//
	/*  FUNCTIONS    ------------------------------------------------------- */

public:

	//! constructor;
	WqsTAuto			( QObject * parent = NULL );

	//! destructor;
	virtual				~WqsTAuto		( void );

	//! tell if the timer is running
	inline bool			isRunning		( void ) const
	{ return timer_id_ != 0; }

	//! tell the frequency of the timer
	inline int			frequency		( void ) const
	{ return frequency_; }

	//! number of ticks after which worldTick() is fired
	inline int			interval		( void ) const
	{ return update_len_; }
	
private:

	//! used to generate events in the underlying world object
	void				timerEvent		( QTimerEvent * );
	
public slots:
	
	//! change the frequency of the timer
	bool				changeFrequency	( int new_val );
	
	//! change number of ticks after which worldTick() is fired
	bool				changeInterval	( int new_val );

	//! start the internal timer
	bool				start			( void );
	
	//! stop the internal timer
	bool				stop			( void );


	/*  FUNCTIONS    ======================================================= */
	//
	//
	//
	//

};	/*	class WqsTAuto	*/

/*  CLASS    =============================================================== */
//
//
//
//

}   //  namespace Gui

}   //  namespace april

#endif // __WQSTAUTO_INC__
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
