/* ========================================================================= */
/* ------------------------------------------------------------------------- */
/*!
  \file			eventsource.cc
  \date			Apr 2013
  \author		TNick

  \brief		Contains the implementation of EventSource class


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

#include	"eventsource.h"
#include	"eventfactory.h"
#include	"world.h"
#include	<QSettings>
#include	<april/aprillibrary.h>

/*  INCLUDES    ============================================================ */
//
//
//
//
/*  DEFINITIONS    --------------------------------------------------------- */

using namespace april;

#define FUNC_ENTRY	APRDBG_FUNC(APRDBG_ES)

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
EventSource::EventSource	( World * w )
	: Component(),
	world_( w )
{
	APRDBG_CDTOR;
	w->addEvent( this );
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
EventSource *		EventSource::fromStg		( World * w, QSettings & stg )
{ FUNC_ENTRY;
	QString			factory_name;
	Factory *		f;
	ID				id;
	EventFactory *	event_factory;
	EventSource *	event;
	bool			b;
	
	stg.beginGroup( "april-Event" );
	factory_name = stg.value( "factory_name" ).toString();
	id = stg.value( "factory_id" ).toULongLong( &b );
	stg.endGroup();
	if ( !b ) return NULL;
	
	f = AprilLibrary::factoryForString( w, factory_name );
	if ( f == NULL )
	{
		stg.endGroup();
		return NULL;
	}
	else if ( f->factoryType() != FTyWorld )
	{
		DEC_REF(f,f);
		stg.endGroup();
		return NULL;
	}
	event_factory = static_cast<EventFactory*>(f);
	event = event_factory->create( id );
	if ( event != NULL )
	{
		if ( event->load( stg ) == false )
		{
			w->remEvent( event );
			DEC_REF(event,event);
			event = NULL;
		}
	}
	DEC_REF(f,f);
	return event;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
EventSource::~EventSource	( void )
{
	APRDBG_CDTOR;
	/* stub */
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool				EventSource::save				( QSettings & stg ) const
{ FUNC_ENTRY;
	bool b = true;
	stg.beginGroup( "april-EventSource" );

	b = b & Component::save( stg );
	
	stg.endGroup();
	return b;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool				EventSource::load				( QSettings & stg )
{ FUNC_ENTRY;
	bool b = true;
	stg.beginGroup( "april-EventSource" );

	b = b & Component::load( stg );
	
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
