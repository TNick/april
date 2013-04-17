/* ========================================================================= */
/* ------------------------------------------------------------------------- */
/*!
  \file			amodbrain.cc
  \date			Apr 2013
  \author		TNick

  \brief		Contains the implementation of AModBrain class


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

#include	"amodbrain.h"
#include	<april/aprillibrary.h>
#include	<april/logic/world.h>
#include	<april/logic/actor.h>
#include	<april/logic/brain.h>
#include	<april/logic/brainfactory.h>
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
AModBrain::AModBrain	( CommandMap * cmd_map )
	: AprilModule(cmd_map)
{
	APRDBG_CDTOR;
	/* stub */
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
AModBrain::~AModBrain	( void )
{
	APRDBG_CDTOR;
	/* stub */
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void			AModBrain::insertCommands			( CommandMap * cm )
{
	/// @cond internal
	
	//! register a command from this package 
#define addOneCmd(c)	\
	cm->addCommand( QObject::tr( "b." stringify(c) ), AModBrain::c##Brain )
	
	addOneCmd(new);
	addOneCmd(list);
	addOneCmd(kinds);
	
#undef addOneCmd
	//! @endcond
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void			AModBrain::removeCommands			( CommandMap * cm )
{
	/// @cond internal
	
	//! unregister a command from this package @internal
#define remOneCmd(c)	\
	cm->remCommand( QObject::tr( "b." stringify(c) ), AModBrain::c##Brain );
	
	remOneCmd(new);
	remOneCmd(list);
	remOneCmd(kinds);
	
#undef remOneCmd
	//! @endcond
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
QString			AModBrain::name				( void )
{
	return QObject::tr( "Brain" );
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
static QString	do_new_brain				( Actor * a, ID id )
{
	QString s;
	Brain * sens = a->world()->createBrain( a, id );
	if ( sens == NULL )
	{
		s = QObject::tr( 
					"Can't create brain ID %1.\n"
					).arg( id );
	}
	else
	{
		s = QObject::tr( 
					"Brain ID %1 created.\n"
					).arg( id );
	}
	return s;
}
bool			AModBrain::newBrain		(
		const QString & s_cmd, const AaTkString & atks, QString & s_err )
{
	Q_ASSERT( s_cmd == "b.new" );
	return funcArg_AID( s_cmd, atks, s_err, do_new_brain );
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
static QString	do_list_brain				( Actor * a )
{
	QList<QStringList>	datao;
	QStringList			sl;
	sl.append( QObject::tr( "ID" ) );
	sl.append( QObject::tr( "Name" ) );
	sl.append( QObject::tr( "Cost" ) );
	sl.append( QObject::tr( "Energy" ) );
	datao.append( sl ); sl.clear();
	
	Brain * iter = a->firstBrain();
	while ( iter != NULL )
	{
		sl.append( QString::number( iter->identificator() ) );
		sl.append( iter->myName() );
		sl.append( QString::number( iter->cost() ) );
		sl.append( QString::number( iter->energy() ) );
		datao.append( sl );  sl.clear();
		
		iter = nextBrain_(iter);
	}
	AOutput::showTable( datao, true );
	return QString();
}
bool			AModBrain::listBrain		(
		const QString & s_cmd, const AaTkString & atks, QString & s_err )
{
	Q_ASSERT( s_cmd == "b.list" );
	return funcArg_A0( s_cmd, atks, s_err, do_list_brain );
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
static QString	do_kinds_brain				( World * w )
{
	
	QList<QStringList>	datao;
	QStringList			sl;
	sl.append( QObject::tr( "ID" ) );
	sl.append( QObject::tr( "Name" ) );
	sl.append( QObject::tr( "Factory name" ) );
	datao.append( sl ); sl.clear();

	const QMap<ID,BrainFactory*> & sf = w->brainFactories();
	QMap<ID,BrainFactory*>::ConstIterator itr = sf.constBegin();
	QMap<ID,BrainFactory*>::ConstIterator itr_e = sf.constEnd();
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
bool			AModBrain::kindsBrain		(
		const QString & s_cmd, const AaTkString & atks, QString & s_err )
{
	Q_ASSERT( s_cmd == "b.kinds" );
	return funcArg0W( s_cmd, atks, s_err, do_kinds_brain );
}
/* ========================================================================= */

/*  CLASS    =============================================================== */
//
//
//
//
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
