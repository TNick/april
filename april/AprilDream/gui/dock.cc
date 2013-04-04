/* ========================================================================= */
/* ------------------------------------------------------------------------- */
/*!
  \file			dock.cc
  \date			Apr 2013
  \author		TNick
  
  \brief		Contains the implementation of Dock class
  
  
*//*


 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Please read COPYING and README files in root folder
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
//
//
//
//
/*  INCLUDES    ------------------------------------------------------------ */

#include	"dock.h"
#include	"mw.h"
#include	<QDebug>

/*  INCLUDES    ============================================================ */
//
//
//
//
/*  DEFINITIONS    --------------------------------------------------------- */

using namespace april;
using namespace april::Gui;

/*  DEFINITIONS    ========================================================= */
//
//
//
//
/*  DATA    ---------------------------------------------------------------- */

/*  DATA    ================================================================ */
//
//
//
//
/*  CLASS    --------------------------------------------------------------- */

/* ------------------------------------------------------------------------- */
Dock::Dock	( MW * mw, const QString & s_text )
	: QObject(), MemTrack(),
	  mw_( mw ),
	  wdok_( NULL ),
	  act_sh_( s_text, NULL ),
	  b_flip_( false ),
	  id_(0)
{
	APRDBG_CDTOR;
	act_sh_.setCheckable( true );
	
	connect( &act_sh_, SIGNAL( triggered(bool) ),
			 this, SLOT( changeVisibility(bool) ) );
	side_ = Qt::RightDockWidgetArea;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
Dock::~Dock	( void )
{
	APRDBG_CDTOR;
	if ( wdok_ != NULL )
	{
		wdok_->deleteLater();
	}
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void				Dock::changeVisibility		( bool b_vis )
{
	if ( b_vis )
	{
		if ( wdok_ == NULL )
		{
			wdok_ = new QDockWidget( act_sh_.text(), mw_ );
			if ( side_ == Qt::NoDockWidgetArea )
			{
				mw_->addDockWidget( Qt::RightDockWidgetArea, wdok_, Qt::Horizontal );
				wdok_->setFloating( true );
			}
			else
			{
				mw_->addDockWidget( side_, wdok_, Qt::Horizontal );
			}
			connect( wdok_, SIGNAL( dockLocationChanged(Qt::DockWidgetArea) ),
					 this, SLOT( saveDockLoc(Qt::DockWidgetArea) ) );
			connect( wdok_, SIGNAL( visibilityChanged(bool) ),
					 this, SLOT( dockVisibilityChanged(bool) ) );
					 
		}
		else
		{
			/* already constructed */
			wdok_->show();
		}
	}
	else
	{
		if ( wdok_ == NULL )
		{
			/* already hidden */
		}
		else
		{
			wdok_->hide();
			wdok_->deleteLater();
			wdok_ = NULL;
		}
	}
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void				Dock::saveDockLoc			( Qt::DockWidgetArea a )
{
	side_ = a;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void				Dock::dockVisibilityChanged	( bool b )
{
	if ( b == false )
	{
		id_ = startTimer( 500 );
	}
	b_flip_ = b;
	act_sh_.setChecked( b );
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void				Dock::timerEvent			( QTimerEvent * )
{
	killTimer( id_ );
	id_ = 0;
	if ( ( b_flip_ == false ) && ( wdok_ != NULL ) )
	{
		wdok_->deleteLater();
		wdok_ = NULL;
	}
}
/* ========================================================================= */

/*  CLASS    =============================================================== */
//
//
//
//
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
