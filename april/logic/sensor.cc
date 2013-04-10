/* ========================================================================= */
/* ------------------------------------------------------------------------- */
/*!
  \file			sensor.cc
  \date			Apr 2013
  \author		TNick

  \brief		Contains the implementation of Sensor class


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

#include	"sensor.h"
#include	"sensorfactory.h"
#include	"actor.h"
#include	<april/aprillibrary.h>


/*  INCLUDES    ============================================================ */
//
//
//
//
/*  DEFINITIONS    --------------------------------------------------------- */

using namespace april;


#define	_LG2_(t1,t2)	APRDBG2(APRDBG_W,t1,t2)
#define	_LG3_(t1,t2,t3)	APRDBG3(APRDBG_W,t1,t2,t3)
#define	_LG_(t)		APRDBG(APRDBG_S,t)
#define	FUNC_ENTRY	APRDBG_FUNC(APRDBG_S)

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
Sensor::Sensor	( Actor * actor )
	: ActorComp( actor )
{
	APRDBG_CDTOR;
	actor->addSensor( this );
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
Sensor::Sensor	( Actor * actor, quint64 cost, quint64 energy )
	: ActorComp( actor, cost, energy )
{
	APRDBG_CDTOR;
	actor->addSensor( this );
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
Sensor *			Sensor::fromStg				( Actor * a, QSettings & stg )
{ FUNC_ENTRY;
	QString			factory_name;
	Factory *		f;
	ID				id;
	SensorFactory *	sensor_factory;
	Sensor *		sensor;
	bool			b;
	
	stg.beginGroup( "april-Sensor" );
	factory_name = stg.value( "factory_name" ).toString();
	id = stg.value( "factory_id" ).toULongLong( &b );
	stg.endGroup();
	if ( !b ) return NULL;
	
	f = AprilLibrary::factoryForString( a->world(), factory_name );
	if ( f == NULL )
	{
		stg.endGroup();
		return NULL;
	}
	else if ( f->factoryType() != FTySensor )
	{
		DEC_REF(f,f);
		stg.endGroup();
		return NULL;
	}
	sensor_factory = static_cast<SensorFactory*>(f);
	sensor = sensor_factory->create( a, id );
	if ( sensor )
	{
		if ( sensor->load( stg ) == false )
		{
			a->remSensor( sensor );
			DEC_REF(sensor,sensor);
			sensor = NULL;
		}
	}
	DEC_REF(f,f);
	return sensor;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
Sensor::~Sensor	( void )
{
	APRDBG_CDTOR;
	/* stub */
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool				Sensor::save				( QSettings & stg ) const
{ FUNC_ENTRY;
	bool b = true;
	stg.beginGroup( "april-Sensor" );

	Factory * f = factory();
	if ( f == NULL )
	{
		stg.setValue( "factory_name", QString() );
		_LG_("  no factory set for sensor");
	}
	else
	{
		stg.setValue( "factory_name", f->factoryName() );
		_LG2_("  factory for sensor: ", f->factoryName() );
	}
	stg.setValue( "factory_id", identificator() );
	_LG2_("  factory id: ", identificator() );

	b = b & ActorComp::save( stg );
	
	stg.endGroup();
	return b;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool				Sensor::load				( QSettings & stg )
{ FUNC_ENTRY;
	bool b = true;
	stg.beginGroup( "april-Sensor" );

	b = b & ActorComp::load( stg );
	
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
