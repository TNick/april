/* ========================================================================= */
/* ------------------------------------------------------------------------- */
/*!
  \file			sensorfactory.cc
  \date			Apr 2013
  \author		TNick

  \brief		Contains the implementation of SensorFactory class


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

#include	"sensorfactory.h"
#include	"sensor.h"
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
#define	_LG_(t)		APRDBG(APRDBG_FS,t)
#define	FUNC_ENTRY	APRDBG_FUNC(APRDBG_FS)
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
SensorFactory::SensorFactory	( World * w )
	: Factory( w )
{
	APRDBG_CDTOR;
	/* stub */
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
SensorFactory::~SensorFactory	( void )
{
	APRDBG_CDTOR;
	/* stub */
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
Sensor *			SensorFactory::create			( Actor * ag, ID id )
{
	Q_UNUSED( id );
	if ( world() == NULL )
		return NULL;
	
	Sensor * ret = new Sensor( ag, 1, 10 );
	return ret;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool				SensorFactory::addMyself		( ID id )
{ FUNC_ENTRY;
	Q_ASSERT( id != InvalidId );
	return world()->addSensorFactory( this, id );
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool				SensorFactory::save				( QSettings & stg ) const
{ FUNC_ENTRY;
	bool b = true;
	stg.beginGroup( "april-SensorFactory" );
	
	for (;;)	{
		b = b & Factory::save( stg );
		if ( !b ) break;
		
		break;
	}
	stg.endGroup();
	
	return b;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool				SensorFactory::load				( QSettings & stg )
{ FUNC_ENTRY;
	bool b = true;
	stg.beginGroup( "april-SensorFactory" );
	
	for (;;)	{
		b = b & Factory::load( stg );
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
