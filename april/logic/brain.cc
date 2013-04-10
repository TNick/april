/* ========================================================================= */
/* ------------------------------------------------------------------------- */
/*!
  \file			brain.cc
  \date			Apr 2013
  \author		TNick

  \brief		Contains the implementation of Brain class


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

#include	"brain.h"
#include	"brainfactory.h"
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
#define	_LG_(t)		APRDBG(APRDBG_B,t)
#define	FUNC_ENTRY	APRDBG_FUNC(APRDBG_B)

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
Brain::Brain	( Actor * actor )
	: ActorComp( actor )
{
	APRDBG_CDTOR;
	actor->addBrain( this );
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
Brain::Brain	( Actor * actor, quint64 cost, quint64 energy )
	: ActorComp( actor, cost, energy )
{
	APRDBG_CDTOR;
	actor->addBrain( this );
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
Brain *			Brain::fromStg				( Actor * a, QSettings & stg )
{ FUNC_ENTRY;
	QString			factory_name;
	Factory *		f;
	ID				id;
	BrainFactory *	brain_factory;
	Brain *		brain;
	bool			b;
	
	stg.beginGroup( "april-Brain" );
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
	else if ( f->factoryType() != FTyBrain )
	{
		DEC_REF(f,f);
		stg.endGroup();
		return NULL;
	}
	brain_factory = static_cast<BrainFactory*>(f);
	brain = brain_factory->create( a, id );
	if ( brain )
	{
		if ( brain->load( stg ) == false )
		{
			a->remBrain( brain );
			DEC_REF(brain,brain);
			brain = NULL;
		}
	}
	DEC_REF(f,f);
	return brain;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
Brain::~Brain	( void )
{
	APRDBG_CDTOR;
	/* stub */
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool				Brain::save				( QSettings & stg ) const
{ FUNC_ENTRY;
	bool b = true;
	stg.beginGroup( "april-Brain" );

	Factory * f = factory();
	if ( f == NULL )
	{
		stg.setValue( "factory_name", QString() );
		_LG_("  no factory set for brain");
	}
	else
	{
		stg.setValue( "factory_name", f->factoryName() );
		_LG2_("  factory for brain: ", f->factoryName() );
	}
	stg.setValue( "factory_id", identificator() );
	_LG2_("  factory id: ", identificator() );
	
	b = b & ActorComp::save( stg );
	
	stg.endGroup();
	return b;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool				Brain::load				( QSettings & stg )
{ FUNC_ENTRY;
	bool b = true;
	stg.beginGroup( "april-Brain" );

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
