/* ========================================================================= */
/* ------------------------------------------------------------------------- */
/*!
  \file			dock.h
  \date			Apr 2013
  \author		TNick

  \brief		Contains the definition for Dock class


*//*


 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Please read COPYING and README files in root folder
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
#ifndef __DOCK_INC__
#define __DOCK_INC__
//
//
//
//
/*  INCLUDES    ------------------------------------------------------------ */

#include    <april/april.h>
#include	<QDockWidget>
#include	<QAction>

/*  INCLUDES    ============================================================ */
//
//
//
//
/*  DEFINITIONS    --------------------------------------------------------- */

namespace   april	{

namespace   Gui		{

class	MW;

/*  DEFINITIONS    ========================================================= */
//
//
//
//
/*  CLASS    --------------------------------------------------------------- */

/**
*	@brief	Represents the base class for a docking panel
*/
class Dock		: public QObject, public MemTrack		{
	Q_OBJECT
	BBM_TRACK( Dock );

	//
	//
	//
	//
	/*  DEFINITIONS    ----------------------------------------------------- */

	//! add an integer unbounded property
#	define DOCK_ADD_IPROP(id,name) \
	d_->props_[id] = d_->intManager->addProperty(name); \
	d_->props_[id]->setEnabled( false ); \
	d_->tree_->addProperty( d_->props_[id] );
	
	//! add an integer bounded property
#	define DOCK_ADD_IPROP_B(id,name,i_min,i_max) \
	d_->props_[id] = d_->intManager->addProperty( name ); \
	d_->props_[id]->setEnabled( false ); \
	d_->tree_->addProperty( d_->props_[id] ); \
	d_->intManager->setMinimum( d_->props_[id], i_min ); \
	d_->intManager->setMaximum( d_->props_[id], i_max );
 

	/*  DEFINITIONS    ===================================================== */
	//
	//
	//
	//
	/*  DATA    ------------------------------------------------------------ */

private:

	//! parent widget
	MW *					mw_;

	//! the action used to show-hide the widget
	QDockWidget *			wdok_;
	
	//! embedded action for showing/hiding the widget
	QAction					act_sh_;

	//! the side where it should be shown
	Qt::DockWidgetArea		side_;

	//! prevent overlapping
	bool					b_flip_;

	//! timer id
	int						id_;
	
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
	Dock				( MW * mw, const QString & s_text );


	/**
	*	@brief	destructor;
	*/
	virtual				~Dock		( void );

	//! the embedded action
	QAction *			action		( void )
	{ return &act_sh_; }

	//! parent main window
	MW *				mainWindow	( void ) const
	{ return mw_; }
	
	//! the action used to show-hide the widget
	QDockWidget *		dock		( void ) const
	{ return wdok_; }

	

private slots:

	//! informed about the change in visibility
	void				changeVisibility		( bool b_vis );
	
	//! we're saving the side using this slot
	void				saveDockLoc				( Qt::DockWidgetArea );
	
	//! only used when the dock is hidden
	void				dockVisibilityChanged	( bool b );
	
private:
	
	//! timer to find out if we've been really hidden
	void				timerEvent				( QTimerEvent * );
	
protected:
	
	//! used to construct the widget
	virtual void		construct				( void ) = 0;
	
	//! used to destruct the widget
	virtual void		deconstruct				( void ) = 0;
	
	/*  FUNCTIONS    ======================================================= */
	//
	//
	//
	//

};	/*	class Dock	*/

/*  CLASS    =============================================================== */
//
//
//
//

}   //  namespace   Gui
}   //  namespace   april

#endif // __DOCK_INC__
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
