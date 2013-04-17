/* ========================================================================= */
/* ------------------------------------------------------------------------- */
/*!
  \file			amodevents.cc
  \date			Apr 2013
  \author		TNick

  \brief		Contains the implementation of AModEvents class


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

#include	"amodevents.h"
#include	<april/aprillibrary.h>
#include	<april/logic/world.h>
#include	<april/logic/actor.h>
#include	<april/logic/genericactorfactory.h>
#include	<april/logic/aoutput.h>
#include	<april/logic/eventsource.h>
#include	<april/logic/eventfactory.h>
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
AModEvent::AModEvent	( CommandMap * cmd_map )
	: AprilModule(cmd_map)
{
	APRDBG_CDTOR;
	/* stub */
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
AModEvent::~AModEvent	( void )
{
	APRDBG_CDTOR;
	/* stub */
}
/* ========================================================================= */


/* ------------------------------------------------------------------------- */
void			AModEvent::insertCommands			( CommandMap * cm )
{
	/// @cond internal
	
	//! register a command from this package 
#define addOneCmd(c)	\
	cm->addCommand( QObject::tr( "e." stringify(c) ), AModEvent::c##Event )
	
	addOneCmd(new);
	addOneCmd(list);
	addOneCmd(kinds);
	
#undef addOneCmd
	//! @endcond
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void			AModEvent::removeCommands			( CommandMap * cm )
{
	/// @cond internal
	
	//! unregister a command from this package @internal
#define remOneCmd(c)	\
	cm->remCommand( QObject::tr( "e." stringify(c) ), AModEvent::c##Event );
	
	remOneCmd(new);
	remOneCmd(list);
	remOneCmd(kinds);
	
#undef remOneCmd
	//! @endcond
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
QString			AModEvent::name				( void )
{
	return QObject::tr( "Event" );
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
static QString	do_new_event				( 
		World * w, const QString & s_arg_1, const AaToken & tk1 )
{
	QString s;
	if ( tk1.isInteger() == true )
	{
		bool b;
		ID id = s_arg_1.toULongLong( &b );
		if ( b && ( id != InvalidId ) )
		{
			EventSource * e = w->createEvent( id );
			if ( e == NULL )
			{
				s = QObject::tr( 
							"Can't create event source ID %1.\n"
							).arg( id );
			}
			else
			{
				s = QObject::tr( 
							"Event source ID %1 created.\n"
							).arg( id );
				DEC_REF(e,e);
			}
			return s;
		}
	}
	AprilModule::errorIdExpected( s, s_arg_1 );
	return s;	
}
bool			AModEvent::newEvent			(
		const QString & s_cmd, const AaTkString & atks, QString & s_err )
{
	Q_ASSERT( s_cmd == "e.new" );
	return funcArg1W( s_cmd, atks, s_err, do_new_event );
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
static QString	do_event_list					( World * w )
{
	QString s = QObject::tr( 
				"List of events in world <%1>:\n"
				).arg( w->name() );
	EventSource * itr = w->firstEvent();
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
	
		while ( itr != NULL )
		{
			sl.append( QString::number( itr->identificator() ) );
			sl.append( w->nameForId( itr->identificator() ) );
			datao.append( sl ); sl.clear();
			itr = nextEvent_(itr);
		}
		AOutput::showInfo( s );
		AOutput::showTable( datao, true );
		s.clear();
	
	}
	return s;
}
bool			AModEvent::listEvent		(
		const QString & s_cmd, const AaTkString & atks, QString & s_err )
{
	Q_ASSERT( s_cmd == "e.list" );
	return funcArg0W( s_cmd, atks, s_err, do_event_list );
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
static QString	do_event_kinds					( World * w )
{
	
	QList<QStringList>	datao;
	QStringList			sl;
	sl.append( QObject::tr( "ID" ) );
	sl.append( QObject::tr( "Name" ) );
	sl.append( QObject::tr( "Factory name" ) );
	datao.append( sl ); sl.clear();

	const QMap<ID,EventFactory*> & sf = w->eventFactories();
	QMap<ID,EventFactory*>::ConstIterator itr = sf.constBegin();
	QMap<ID,EventFactory*>::ConstIterator itr_e = sf.constEnd();
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
bool			AModEvent::kindsEvent		(
		const QString & s_cmd, const AaTkString & atks, QString & s_err )
{
	Q_ASSERT( s_cmd == "e.kinds" );
	return funcArg0W( s_cmd, atks, s_err, do_event_kinds );
}
/* ========================================================================= */

/*  CLASS    =============================================================== */
//
//
//
//
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
