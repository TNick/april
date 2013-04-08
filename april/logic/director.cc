/* ========================================================================= */
/* ------------------------------------------------------------------------- */
/*!
  \file			director.cc
  \date			Apr 2013
  \author		TNick

  \brief		Contains the implementation of Director class


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

#include	"director.h"
#include	"world.h"
#include	"actor.h"
#include	"actorfactory.h"
#include	"eventsource.h"
#include	"eventfactory.h"
#include	"actuator.h"
#include	"actuatorfactory.h"
#include	"sensor.h"
#include	"sensorfactory.h"
#include	"brain.h"
#include	"brainfactory.h"
#include	"reflex.h"
#include	"reflexfactory.h"
#include	"eventline.h"

/*  INCLUDES    ============================================================ */
//
//
//
//
/*  DEFINITIONS    --------------------------------------------------------- */

using namespace april;

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
Director::Director	( World * w )
	: libbbb::RefCnt(), MemTrack(),
	w_( w )
{
	APRDBG_CDTOR;
	/* stub */
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
Director::~Director	( void )
{
	APRDBG_CDTOR;
	/* stub */
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void				Director::advance				( void )
{
	/* update time */
	stepTime();
	
	/* iterate in events and advance them */
	EventSource * e = w_->firstEvent();
	while ( e != NULL )
	{
		e->doSteps( 1 );
		e = nextEvent_( e );
	}
	
	/* iterate in actors and advance them */
	Actor * a = w_->firstActor();
	while ( a != NULL )
	{
		a->doSteps( 1 );
		a = nextActor_( a );
	}
	
	/* iterate in event lines and remove old ones */
	QMap<ID,EventLine*>::ConstIterator itr_event_lines = firstEventLine();
	QMap<ID,EventLine*>::ConstIterator itr_end_event_lines = endEventLine();
	while ( itr_event_lines != itr_end_event_lines )
	{
		itr_event_lines.value()->discardOldEntries();
		itr_event_lines++;
	}
	
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
QMap<ID,EventLine*>::ConstIterator	Director::firstEventLine	( void )
{
	return w_->firstEventLine();
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
QMap<ID,EventLine*>::ConstIterator	Director::endEventLine		( void )
{
	return w_->endEventLine();
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void				Director::stepTime			( void )
{
	w_->stepTime();
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool				Director::save				( QSettings & stg ) const
{
	
	return true;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool				Director::load				( QSettings & stg )
{
	
	
	return true;
}
/* ========================================================================= */

/*  CLASS    =============================================================== */
//
//
//
//
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
