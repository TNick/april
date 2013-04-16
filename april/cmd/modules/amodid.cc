/* ========================================================================= */
/* ------------------------------------------------------------------------- */
/*!
  \file			amodid.cc
  \date			Apr 2013
  \author		TNick
  
  \brief		Contains the implementation of AModId class
  
  
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

#include	"amodid.h"
#include	<april/aprillibrary.h>
#include	<april/logic/world.h>
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
AModId::AModId	( CommandMap * cmd_map )
	: AprilModule(cmd_map)
{
	APRDBG_CDTOR;
	/* stub */
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
AModId::~AModId	( void )
{
	APRDBG_CDTOR;
	/* stub */
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void			AModId::insertCommands			( CommandMap * cm )
{
	/// @cond internal
	
	//! register a command from this package 
#define addOneCmd(c)	\
	cm->addCommand( QObject::tr( "id." stringify(c) ), AModId::c##ID )
	
	addOneCmd(new);
	addOneCmd(list);
	addOneCmd(info);
	
#undef addOneCmd
	//! @endcond
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void			AModId::removeCommands			( CommandMap * cm )
{
	/// @cond internal
	
	//! unregister a command from this package @internal
#define remOneCmd(c)	\
	cm->remCommand( QObject::tr( "id." stringify(c) ), AModId::c##ID );
	
	remOneCmd(new);
	remOneCmd(list);
	remOneCmd(info);
	
#undef remOneCmd
	//! @endcond
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
QString			AModId::name					( void )
{
	return QObject::tr( "ID" );
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
static QString	do_new_id				( 
		World * w, const QString & s_arg_1, const AaToken & tk1 )
{
	Q_UNUSED( tk1 );
	ID id = w->idValue( s_arg_1 );
	if ( id != InvalidId )
	{
		return QObject::tr( "Name %1 already associated with id %2.\n" )
				.arg( s_arg_1 ).arg( id );
	}
	id = w->addNewId( s_arg_1 );
	return QObject::tr( "Name %1 was associated with id %2.\n" )
			.arg( s_arg_1 ).arg( id );
}
bool			AModId::newID				(
		const QString & s_cmd, const AaTkString & atks, QString & s_err )
{
	Q_ASSERT( s_cmd == "id.new" );
	return funcArg1W( s_cmd, atks, s_err, do_new_id );
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
static QString	do_list_id				( 
		World * w )
{
	QString s = QObject::tr( "List of allocated IDs in world %1:\n" )
			.arg( w->name() );
	QList<ID> idlst = w->allocatedIds();
	foreach( ID id, idlst )
	{
		s.append( QString( 4, QChar( ' ' ) ) );
		s.append( QString::number( id ) );
		s.append( QString( 2, QChar( ' ' ) ) );
		s.append( w->nameForId( id ) );
		s.append( QChar( '\n' ) );
	}
	return s;
}
bool			AModId::listID				(
		const QString & s_cmd, const AaTkString & atks, QString & s_err )
{
	Q_ASSERT( s_cmd == "id.list" );
	return funcArg0W( s_cmd, atks, s_err, do_list_id );
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
static QString	do_info_id				( 
		World * w, const QString & s_arg_1, const AaToken & tk1 )
{
	QString s;
	if ( tk1.isInteger() == true )
	{
		bool b;
		ID id = s_arg_1.toULongLong( &b );
		if ( b && ( id != InvalidId ) )
		{
			s = w->nameForId( id );
			if ( s.isEmpty() )
			{
				return QObject::tr( 
							"Id %1 is not associated with any name in world <%2>.\n"
							).arg( id ).arg( w->name() );
			}
			else
			{
				return QObject::tr( 
							"Id %1 is associated with name %2 in world <%3>.\n"
							).arg( id ).arg( s ).arg( w->name() );
			}
		}
	}
	AprilModule::errorIdExpected( s, s_arg_1 );
	return s;
}
bool			AModId::infoID				(
		const QString & s_cmd, const AaTkString & atks, QString & s_err )
{
	Q_ASSERT( s_cmd == "id.info" );
	return funcArg1W( s_cmd, atks, s_err, do_info_id );
}
/* ========================================================================= */

/*  CLASS    =============================================================== */
//
//
//
//
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
