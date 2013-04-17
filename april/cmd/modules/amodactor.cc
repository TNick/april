/* ========================================================================= */
/* ------------------------------------------------------------------------- */
/*!
  \file			amodactor.cc
  \date			Apr 2013
  \author		TNick
  
  \brief		Contains the implementation of AModActor class
  
  
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

#include	"amodactor.h"
#include	<april/aprillibrary.h>
#include	<april/logic/world.h>
#include	<april/logic/actor.h>
#include	<april/logic/genericactorfactory.h>
#include	<april/logic/aoutput.h>
#include	<april/cmd/apriltokenizer.h>
#include	<april/cmd/commandmap.h>
#include	<QObject>

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
AModActor::AModActor	( CommandMap * cmd_map )
	: AprilModule(cmd_map)
{
	APRDBG_CDTOR;
	/* stub */
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
AModActor::~AModActor	( void )
{
	APRDBG_CDTOR;
	/* stub */
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void			AModActor::insertCommands			( CommandMap * cm )
{
	/// @cond internal
	
	//! register a command from this package 
#define addOneCmd(c)	\
	cm->addCommand( QObject::tr( "a." stringify(c) ), AModActor::c##Actor )
	
	addOneCmd(new);
	addOneCmd(list);
	addOneCmd(kill);
	addOneCmd(kinds);
	
#undef addOneCmd
	//! @endcond
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void			AModActor::removeCommands			( CommandMap * cm )
{
	/// @cond internal
	
	//! unregister a command from this package @internal
#define remOneCmd(c)	\
	cm->remCommand( QObject::tr( "a." stringify(c) ), AModActor::c##Actor );
	
	remOneCmd(new);
	remOneCmd(list);
	remOneCmd(kill);
	remOneCmd(kinds);
	
#undef remOneCmd
	//! @endcond
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
QString			AModActor::name				( void )
{
	return QObject::tr( "Actor" );
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
static QString	do_new_actor				( 
		World * w, const QString & s_arg_1, const AaToken & tk1 )
{
	QString s;
	if ( tk1.isInteger() == true )
	{
		bool b;
		ID id = s_arg_1.toULongLong( &b );
		if ( b && ( id != InvalidId ) )
		{
			GenericActorFactory * gf = 
					GenericActorFactory::findMyself( w );
			Q_ASSERT( gf != NULL );
			
			DNA dna = gf->dna( id );
			if ( dna.isValid() )
			{
				Actor * a = w->createActor( id );
				if ( a != NULL )
				{
					s = QObject::tr( 
								"Actor for ID %1 was created.\n"
								).arg( id );
					DEC_REF(a,a);
				}
				else
				{
					s = QObject::tr( 
								"Failed to create actor for ID %1.\n"
								).arg( id );
				}
			}
			else
			{
				s = QObject::tr( 
							"DNA with ID %1 does not exists.\n"
							).arg( id );
			}
			DEC_REF(gf,gf);
			return s;
		}
	}
	AprilModule::errorIdExpected( s, s_arg_1 );
	return s;	
}
bool			AModActor::newActor			(
		const QString & s_cmd, const AaTkString & atks, QString & s_err )
{
	Q_ASSERT( s_cmd == "a.new" );
	return funcArg1W( s_cmd, atks, s_err, do_new_actor );
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
static QString	do_actor_list					( World * w )
{
	QString s = QObject::tr( 
				"List of actors in world <%1>:\n"
				).arg( w->name() );
	Actor * itr = w->firstActor();
	if ( itr == NULL )
	{
		s.append( QObject::tr( "none\n" ) );
	}
	else
	{
		QList<QStringList>	datao;
		QStringList			sl;
		sl.append( QObject::tr( "ID" ) );
		sl.append( QObject::tr( "Name" ) );
		sl.append( QObject::tr( "Birth" ) );
		sl.append( QObject::tr( "Death" ) );
		sl.append( QObject::tr( "Age" ) );
		sl.append( QObject::tr( "Energy" ) );
		datao.append( sl ); sl.clear();
		
		while ( itr != NULL )
		{
			sl.append( QString::number( itr->kind() ) );
			sl.append( itr->kindName() );
			sl.append( QString::number( itr->birth() ) );
			sl.append( QString::number( itr->death() ) );
			sl.append( QString::number( itr->age() ) );
			sl.append( QString::number( itr->totalEnergy() ) );
			datao.append( sl ); sl.clear();
			itr = nextActor_(itr);
		}
		AOutput::showInfo( s );
		AOutput::showTable( datao, true );
		s.clear();
	}
	return s;
}
bool			AModActor::listActor		(
		const QString & s_cmd, const AaTkString & atks, QString & s_err )
{
	Q_ASSERT( s_cmd == "a.list" );
	return funcArg0W( s_cmd, atks, s_err, do_actor_list );
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
static QString	do_kill_actor				( 
		World * w, const QString & s_arg_1, const AaToken & tk1 )
{
	QString s;
	if ( tk1.isInteger() == true )
	{
		bool b;
		int idx = s_arg_1.toInt( &b );
		if ( b && ( idx >= 0 ) )
		{
			Actor * a = w->actorAt( idx );
			if ( a == NULL )
			{
				s = QObject::tr( 
							"There is no actor at index %1.\n"
							).arg( idx );
			}
			else
			{
				w->killActor( a );
				s = QObject::tr( 
							"Actor at index %1 was killed.\n"
							).arg( idx );
			}
			return s;
		}
	}
	AprilModule::errorIntegerExpected( s, s_arg_1 );
	return s;	
}
bool			AModActor::killActor		(
		const QString & s_cmd, const AaTkString & atks, QString & s_err )
{
	Q_ASSERT( s_cmd == "a.kill" );
	return funcArg1W( s_cmd, atks, s_err, do_kill_actor );
}
/* ========================================================================= */


/* ------------------------------------------------------------------------- */
static QString	do_actors_kinds					( World * w )
{
	
	QList<QStringList>	datao;
	QStringList			sl;
	sl.append( QObject::tr( "ID" ) );
	sl.append( QObject::tr( "Name" ) );
	sl.append( QObject::tr( "Factory name" ) );
	datao.append( sl ); sl.clear();

	const QMap<ID,ActorFactory*> & sf = w->actorFactories();
	QMap<ID,ActorFactory*>::ConstIterator itr = sf.constBegin();
	QMap<ID,ActorFactory*>::ConstIterator itr_e = sf.constEnd();
	while ( itr != itr_e )
	{
		sl.append( QString::number( itr.key() ) );
		sl.append( w->nameForId( itr.key() ) );
		sl.append( itr.value()->factoryName() );
		itr++;
	}
	AOutput::showTable( datao, true, false );
	return QString();
}
bool			AModActor::kindsActor		(
		const QString & s_cmd, const AaTkString & atks, QString & s_err )
{
	Q_ASSERT( s_cmd == "a.kinds" );
	return funcArg0W( s_cmd, atks, s_err, do_actors_kinds );
}
/* ========================================================================= */


/*  CLASS    =============================================================== */
//
//
//
//
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
