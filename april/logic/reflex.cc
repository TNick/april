/* ========================================================================= */
/* ------------------------------------------------------------------------- */
/*!
  \file			reflex.cc
  \date			Apr 2013
  \author		TNick

  \brief		Contains the implementation of Reflex class


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

#include	"reflex.h"
#include	"reflexfactory.h"
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
#define	_LG_(t)		APRDBG(APRDBG_R,t)
#define	FUNC_ENTRY	APRDBG_FUNC(APRDBG_R)
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
Reflex::Reflex	( Actor * actor )
	: ActorComp( actor )
{
	APRDBG_CDTOR;
	actor->addReflex( this );
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
Reflex::Reflex	( Actor * actor, quint64 cost, quint64 energy )
	: ActorComp( actor, cost, energy )
{
	APRDBG_CDTOR;
	actor->addReflex( this );
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
Reflex *			Reflex::fromStg				( Actor * a, QSettings & stg )
{ FUNC_ENTRY;
	QString			factory_name;
	Factory *		f;
	ID				id;
	ReflexFactory *	reflex_factory;
	Reflex *		reflex;
	bool			b;
	
	stg.beginGroup( "april-Reflex" );
	factory_name = stg.value( "factory_name" ).toString();
	id = stg.value( "factory_id" ).toULongLong( &b );
	stg.endGroup();
	if ( !b ) return NULL;
	
	f = AprilLibrary::factoryForString( a->world(), factory_name );
	if ( f == NULL )
	{
		return NULL;
	}
	else if ( f->factoryType() != FTyReflex )
	{
		DEC_REF(f,f);
		return NULL;
	}
	reflex_factory = static_cast<ReflexFactory*>(f);
	reflex = reflex_factory->create( a, id );
	if ( reflex )
	{
		if ( reflex->load( stg ) == false )
		{
			a->remReflex( reflex );
			DEC_REF(reflex,reflex);
			reflex = NULL;
		}
	}
	DEC_REF(f,f);
	return reflex;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
Reflex::~Reflex	( void )
{
	APRDBG_CDTOR;
	/* stub */
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool				Reflex::save				( QSettings & stg ) const
{ FUNC_ENTRY;
	bool b = true;
	stg.beginGroup( "april-Reflex" );

	Factory * f = factory();
	if ( f == NULL )
	{
		stg.setValue( "factory_name", QString() );
		_LG_("  no factory set for reflex");
	}
	else
	{
		stg.setValue( "factory_name", f->factoryName() );
		_LG2_("  factory for reflex: ", f->factoryName() );
	}
	stg.setValue( "factory_id", identificator() );
	_LG2_("  factory id: ", identificator() );

	b = b & ActorComp::save( stg );
	
	stg.endGroup();
	return b;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool				Reflex::load				( QSettings & stg )
{ FUNC_ENTRY;
	bool b = true;
	stg.beginGroup( "april-Reflex" );

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
