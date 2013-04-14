/* ========================================================================= */
/* ------------------------------------------------------------------------- */
/*!
  \file			genericactorfactory.cc
  \date			Apr 2013
  \author		TNick
  
  \brief		Contains the implementation of GenericActorFactory class
  
  
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

#include	"genericactorfactory.h"
#include	<QSettings>
#include	<april/logic/actor.h>
#include	<april/logic/world.h>

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
GenericActorFactory::GenericActorFactory	( World * w )
	: ActorFactory( w )
{
	APRDBG_CDTOR;
	/* stub */
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
GenericActorFactory::~GenericActorFactory	( void )
{
	APRDBG_CDTOR;
	/* stub */
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
Actor *			GenericActorFactory::create		( ID id )
{
	IdDnaMapIterC itr = list_.find( id );
	if ( itr == list_.constEnd() )
	{
		return NULL;
		}
	
	Actor * a = new Actor( world() );
	setDNA( a, itr.value() );
	return a;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool			GenericActorFactory::save		( QSettings & stg ) const
{
	bool b = true;
	b = b & ActorFactory::save( stg );
	stg.beginGroup( "GenericActorFactory" );
	stg.beginWriteArray( "list_", list_.count() );
	
	int i = 0;
	IdDnaMapIterC itr = list_.constBegin();
	IdDnaMapIterC itr_end = list_.constEnd();
	while ( itr != itr_end )
	{
		stg.setArrayIndex( i );
		stg.setValue( "ID", itr.key() );
		itr.value().save( stg );
		itr++; i++;
	}
	
	stg.endArray();
	stg.endGroup();
	return b;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool			GenericActorFactory::load		( QSettings & stg )
{
	bool b = true;
	
	b = ActorFactory::load( stg );
	if ( !b ) return false;
	
	stg.beginGroup( "GenericActorFactory" );
	for(;;) {
		
		int	i_max = stg.beginReadArray( "list_" );
		ID	id;
		DNA	dna;
		for( int i = 0; i < i_max; i++ )
		{
			stg.setArrayIndex( i );
			id = stg.value( "ID", InvalidId ).toULongLong( &b );
			b = b & dna.load( stg );
			if ( !b ) break;
			list_.insert( id, dna );
		}
		stg.endArray();
		
		break;
	}
	stg.endGroup();
	
	return b;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
GenericActorFactory *		GenericActorFactory::findMyself		( World * w )
{
	GenericActorFactory * gf;
	ActorFactory * f = w->findActorFactory( staticName() );
	if ( ( f == NULL ) || ( f->factoryType() != FTyGenericActor ) )
	{
		gf = new GenericActorFactory( w );
	}
	else
	{
		gf = static_cast<GenericActorFactory*>( f );
		INC_REF(gf,gf);
	}
	return gf;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void						GenericActorFactory::addNewKind		(
		const DNA::InitData & data ) 
{
	DNA	new_dna;
	initDNA( new_dna, data );
	list_.insert( data.kind_, new_dna );
}
/* ========================================================================= */

/*  CLASS    =============================================================== */
//
//
//
//
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
