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
#include	<QSettings>

/*  INCLUDES    ============================================================ */
//
//
//
//
/*  DEFINITIONS    --------------------------------------------------------- */

using namespace april;

//! @cond internal

#define	_LG2_(t1,t2)	APRDBG2(APRDBG_W,t1,t2)
#define	_LG3_(t1,t2,t3)	APRDBG3(APRDBG_W,t1,t2,t3)
#define	_LG_(t)		APRDBG(APRDBG_EL,t)
#define	FUNC_ENTRY	APRDBG_FUNC(APRDBG_EL)
//! @endcond

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
EventLine::EventLine	( World * w )
	: Component(),
	world_( w ),
	id_( InvalidId ),
	event_data_(),
	last_( NULL ),
	max_count_( 0 )
{
	APRDBG_CDTOR;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
EventLine *		EventLine::fromStg		( World * w, QSettings & stg )
{ FUNC_ENTRY;
	EventLine * ret = new EventLine( w );
	
	for ( ;; )	{
		if ( ret->load( stg ) == false )
			break;
		
		w->addEventLine( ret, ret->id_ );
		DEC_REF(ret,ret);
		return ret;
	}
	
	DEC_REF(ret,ret);
	return NULL;
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
{ FUNC_ENTRY;
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
{ FUNC_ENTRY; 
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
{ FUNC_ENTRY;
	if ( last_ == NULL && event_data_.count() > 0 )
	{
		last_ = static_cast<EventData*>( event_data_.last() );
	}
	return last_;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool					EventLine::save				( QSettings & stg ) const
{ FUNC_ENTRY;
	int		i_cnt;
	bool	b = true;
	stg.beginGroup( "april-EventLine" );
	
	for (;;)	{	
		stg.setValue( "id_", id_ );
		stg.setValue( "max_count_", max_count_ );
		
		stg.beginWriteArray( "event_data_", event_data_.count() );
		i_cnt = 0;
		EventData * ed = firstEventData_(this);
		while ( ed != NULL )
		{
			stg.setArrayIndex( i_cnt );
			b = b & ed->save( stg );
			ed = nextEventData_( ed );
			i_cnt++;
		}
		stg.endArray();
		if ( !b ) break;
		
		b = b & Component::save( stg );
		break;
	}
	stg.endGroup();
	
	return b;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool					EventLine::load				( QSettings & stg )
{ FUNC_ENTRY;
	bool	b = true;
	int		i_cnt;

	stg.beginGroup( "april-EventLine" );
	for(;;)		{
		b = b & Component::load( stg );
	
		id_ = stg.value( "id_" ).toULongLong( &b );
		if ( !b ) break;
		max_count_ = stg.value( "max_count_" ).toULongLong( &b );
		if ( !b ) break;

		i_cnt = stg.beginReadArray( "event_data_" );
		for ( int i = 0; i < i_cnt; i++ )
		{
			stg.setArrayIndex( i );
			if ( EventData::fromStg( this, stg ) == NULL )
			{
				b = false;
				break;
			}
		}
		stg.endArray();
		if ( !b ) break;
		
		break;
	}
	stg.endGroup();
	return b;
}
/* ========================================================================= */

/*  CLASS    =============================================================== */
//
//
//
//
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
