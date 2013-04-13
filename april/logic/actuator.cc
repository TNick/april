/* ========================================================================= */
/* ------------------------------------------------------------------------- */
/*!
  \file			actuator.cc
  \date			Apr 2013
  \author		TNick

  \brief		Contains the implementation of Actuator class


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

#include	"actuator.h"
#include	"actuatorfactory.h"
#include	"actor.h"
#include	<april/aprillibrary.h>


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
#define	_LG_(t)		APRDBG(APRDBG_AT,t)
#define	FUNC_ENTRY	APRDBG_FUNC(APRDBG_AT)
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
Actuator::Actuator	( Actor * actor )
	: ActorComp(actor)
{
	APRDBG_CDTOR;
	actor->addActuator( this );
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
Actuator::Actuator	( Actor * actor, quint64 cost, quint64 energy )
	: ActorComp( actor, cost, energy )
{
	APRDBG_CDTOR;
	actor->addActuator( this );
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
Actuator *			Actuator::fromStg				( Actor * a, QSettings & stg )
{ FUNC_ENTRY;
	QString			factory_name;
	Factory *		f;
	ID				id;
	ActuatorFactory *	actuator_factory;
	Actuator *		actuator;
	bool			b;
	
	stg.beginGroup( "april-Actuator" );
	factory_name = stg.value( "factory_name" ).toString();
	id = stg.value( "factory_id" ).toULongLong( &b );
	stg.endGroup();
	if ( !b ) return NULL;
	
	f = AprilLibrary::factoryForString( a->world(), factory_name );
	if ( f == NULL )
	{
		return NULL;
	}
	else if ( f->factoryType() != FTyActuator )
	{
		DEC_REF(f,f);
		return NULL;
	}
	actuator_factory = static_cast<ActuatorFactory*>(f);
	actuator = actuator_factory->create( a, id );
	if ( actuator )
	{
		if ( actuator->load( stg ) == false )
		{
			a->remActuator( actuator );
			DEC_REF(actuator,actuator);
			actuator = NULL;
		}
	}
	DEC_REF(f,f);
	return actuator;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
Actuator::~Actuator	( void )
{
	APRDBG_CDTOR;
	/* stub */
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool				Actuator::save				( QSettings & stg ) const
{ FUNC_ENTRY;
	bool b = true;
	stg.beginGroup( "april-Actuator" );

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
bool				Actuator::load				( QSettings & stg )
{ FUNC_ENTRY;
	bool b = true;
	stg.beginGroup( "april-Actuator" );

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
