/* ========================================================================= */
/* ------------------------------------------------------------------------- */
/*!
  \file			eventline.cc
  \date			Apr 2013
  \author		TNick

  \brief		Contains the implementation of EventLine class


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

#include	"eventline.h"
#include	"world.h"

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
EventLine::EventLine	( World * w, ID id, unsigned int max_count )
	: Component(),
	world_( w ),
	id_( id ),
	event_data_(),
	last_( NULL ),
	max_count_( max_count )
{
	APRDBG_CDTOR;
	Q_ASSERT( max_count > 0 );
	w->addEventLine( this, id );
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
EventLine::~EventLine	( void )
{
	APRDBG_CDTOR;
	/* stub */
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void					EventLine::discardOldEntries		( void )
{
	EventData *	itr = firstEventData_(this);
	quint64 t = world_->time_;
	while ( itr != NULL )
	{
		if ( t >= itr->discardTime() )
		{
			event_data_.remove( itr );
			DEC_REF( itr, this );
			if ( last_ == itr )
			{
				last_ = NULL;
			}
		}
		itr = nextEventData_( itr );
	}
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool					EventLine::postActivity				( EventData * ed )
{ 
	Q_ASSERT( event_data_.contains( ed ) == false ); 
	if ( world()->isRunning() == false )
	{
		return false;
	}
	
	/* discard old entries to make room for new ones */
	if ( dataCount() >= max_count_ )
	{
		if ( last_ == NULL )
		{
			last_ = static_cast<EventData*>( event_data_.last() );
		}
		EventData * itr;
		do {
			if ( last_ == NULL )
				break;
			itr = prevEventData_( last_ );
			event_data_.remove( last_ );
			DEC_REF(last_,this);
			last_ = itr;
		} while ( dataCount() >= max_count_ );
	}
	
	INC_REF( ed, this );
	if ( ed->discardTime() == 0 )
	{
		ed->setDuration( world(), 1 );
	}
	if ( event_data_.count() == 0 )
	{
		last_ = ed;
	}
	event_data_.prepend( ed );
	return true;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
EventData *				EventLine::lastEventData			( void )
{
	if ( last_ == NULL && event_data_.count() > 0 )
	{
		last_ = static_cast<EventData*>( event_data_.last() );
	}
	return last_;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool					EventLine::save				( QSettings & stg ) const
{
	
	return true;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool					EventLine::load				( QSettings & stg )
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
