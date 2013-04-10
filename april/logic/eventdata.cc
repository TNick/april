/* ========================================================================= */
/* ------------------------------------------------------------------------- */
/*!
  \file			eventdata.cc
  \date			Apr 2013
  \author		TNick

  \brief		Contains the implementation of EventData class


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

#include	"eventdata.h"
#include	"world.h"
#include	"eventline.h"
#include	<QSettings>

/*  INCLUDES    ============================================================ */
//
//
//
//
/*  DEFINITIONS    --------------------------------------------------------- */

using namespace april;


#define	_LG2_(t1,t2)	APRDBG2(APRDBG_W,t1,t2)
#define	_LG3_(t1,t2,t3)	APRDBG3(APRDBG_W,t1,t2,t3)
#define	_LG_(t)		APRDBG(APRDBG_ED,t)
#define	FUNC_ENTRY	APRDBG_FUNC(APRDBG_ED)

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
EventData::EventData	( void )
	: Component(),
	discard_time_(0)
{
	APRDBG_CDTOR;
	/* stub */
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
EventData::EventData	( World * w, quint64 dt )
	: Component()
{
	APRDBG_CDTOR;
	setDuration( w, dt );
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
EventData *		EventData::fromStg			( EventLine * line, QSettings & stg )
{ FUNC_ENTRY;
	EventData * ret = new EventData();
	
	for ( ;; )	{
		if ( ret->load( stg ) == false )
			break;
		
		line->postActivity( ret );
		DEC_REF(ret,ret);
		return ret;
	}
	
	DEC_REF(ret,ret);
	return NULL;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
EventData::~EventData	( void )
{
	APRDBG_CDTOR;
	/* stub */
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void			EventData::setDuration		( World * w, quint64 dt )
{ FUNC_ENTRY;
	setDiscardTime( w->currentTime() + dt );
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool			EventData::save				( QSettings & stg ) const
{ FUNC_ENTRY;
	bool	b = true;
	stg.beginGroup( "april-EventData" );
	
	for (;;)	{	
		stg.setValue( "discard_time_", discard_time_ );
		b = b & Component::save( stg );
		break;
	}
	stg.endGroup();
	
	return b;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool			EventData::load				( QSettings & stg )
{ FUNC_ENTRY;
	bool	b = true;

	stg.beginGroup( "april-EventData" );
	for(;;)		{
	
		discard_time_ = stg.value( "discard_time_" ).toULongLong( &b );
		if ( !b ) break;
		
		b = b & Component::load( stg );
		
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
