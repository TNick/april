/* ========================================================================= */
/* ------------------------------------------------------------------------- */
/*!
  \file			world.cc
  \date			Apr 2013
  \author		TNick

  \brief		Contains the implementation of World class


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

#include	"world.h"
#include	"actor.h"
#include	"event.h"
#include	<april/aprillibrary.h>

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
World::World	( const QString & name, quint64 tot_energ )
	: libbbb::RefCnt(), MemTrack(),
	b_running_( false ),
	s_name_(name),
	time_(0),
	energy_all_(tot_energ),
	energy_free_(tot_energ),
	actors_(),
	uid_(name),
	actor_factories_(),
	actuator_factories_(),
	brain_factories_(),
	sensor_factories_()
{
	APRDBG_CDTOR;
	
	AprilLibrary::addWorld( this );
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
World::~World	( void )
{
	APRDBG_CDTOR;
	AprilLibrary::remWorld( this );
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool				World::setTotEnergy			( quint64 new_val )
{
	if ( energy_free_ > new_val )
		return false;
	energy_all_ = new_val;
	return true;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void				World::advance				( void )
{
	if  ( b_running_ == false )
		return;
		
	time_++;


}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool				World::addActor				( Actor * act )
{
	Q_ASSERT( actors_.contains( act ) == false );
	Q_ASSERT( act != NULL );
	
	INC_REF( act, this );
	actors_.append( act );
	return true;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool				World::remActor				( Actor * act )
{
	Q_ASSERT( actors_.contains( act ) == true );
	
	actors_.removeOne( act );
	DEC_REF( act, this );
	return true;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool				World::addEvent				( Event * ev )
{
	Q_ASSERT( events_.contains( ev ) == false );
	
	events_.append( ev );
	return true;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool				World::remEvent				( Event * ev )
{
	Q_ASSERT( events_.contains( ev ) == true );
	
	events_.removeOne( ev );
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
