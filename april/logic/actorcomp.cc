/* ========================================================================= */
/* ------------------------------------------------------------------------- */
/*!
  \file			actorcomp.cc
  \date			Apr 2013
  \author		TNick

  \brief		Contains the implementation of ActorComp class


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

#include	"actorcomp.h"
#include	"actor.h"
#include	<QSettings>

/*  INCLUDES    ============================================================ */
//
//
//
//
/*  DEFINITIONS    --------------------------------------------------------- */

using namespace april;

#define FUNC_ENTRY	APRDBG_FUNC(APRDBG_ACMP)

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
ActorComp::ActorComp	( Actor * actor )
	: Component(), 
	actor_( actor ),
	cost_( 0 ),
	energy_( 0 )
{
	APRDBG_CDTOR;
	/* stub */
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
ActorComp::ActorComp	( Actor * actor, quint64 cost, quint64 energy )
	: Component(), 
	actor_( actor ),
	cost_( cost ),
	energy_( energy )
{
	APRDBG_CDTOR;
	/* stub */
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
ActorComp::~ActorComp	( void )
{
	APRDBG_CDTOR;
	/* stub */
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool				ActorComp::save				( QSettings & stg ) const
{ FUNC_ENTRY;
	bool b = true;
	stg.beginGroup( "april-ActorComp" );
	
	for (;;)	{
		b = b & Component::save( stg );
		if ( !b ) break;
		
		/* it may not worth the trouble as these are cached */
		stg.setValue( "cost_", cost_ );
		stg.setValue( "energy_", energy_ );

		break;
	}
	stg.endGroup();
	
	return b;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool				ActorComp::load				( QSettings & stg )
{ FUNC_ENTRY;
	bool b = true;
	stg.beginGroup( "april-ActorComp" );
	
	for (;;)	{
		b = b & Component::load( stg );
		if ( !b ) break;
		
		cost_ = stg.value( "cost_" ).toULongLong( &b );
		if ( !b ) break;
		energy_ = stg.value( "energy_" ).toULongLong( &b );
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
