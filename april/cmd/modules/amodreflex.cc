/* ========================================================================= */
/* ------------------------------------------------------------------------- */
/*!
  \file			amodreflex.cc
  \date			Apr 2013
  \author		TNick

  \brief		Contains the implementation of AModReflex class


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

#include	"amodreflex.h"
#include	<april/aprillibrary.h>
#include	<april/logic/world.h>
#include	<april/logic/actor.h>
#include	<april/logic/reflex.h>
#include	<april/logic/reflexfactory.h>
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
AModReflex::AModReflex	( CommandMap * cmd_map )
	: AprilModule(cmd_map)
{
	APRDBG_CDTOR;
	/* stub */
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
AModReflex::~AModReflex	( void )
{
	APRDBG_CDTOR;
	/* stub */
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void			AModReflex::insertCommands			( CommandMap * cm )
{
	/// @cond internal
	
	//! register a command from this package 
#define addOneCmd(c)	\
	cm->addCommand( QObject::tr( "r." stringify(c) ), AModReflex::c##Reflex )
	
	addOneCmd(new);
	addOneCmd(list);
	addOneCmd(kinds);
	
#undef addOneCmd
	//! @endcond
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void			AModReflex::removeCommands			( CommandMap * cm )
{
	/// @cond internal
	
	//! unregister a command from this package @internal
#define remOneCmd(c)	\
	cm->remCommand( QObject::tr( "r." stringify(c) ), AModReflex::c##Reflex );
	
	remOneCmd(new);
	remOneCmd(list);
	remOneCmd(kinds);
	
#undef remOneCmd
	//! @endcond
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
QString			AModReflex::name				( void )
{
	return QObject::tr( "Reflex" );
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
static QString	do_new_reflex				( Actor * a, ID id )
{
	QString s;
	Reflex * sens = a->world()->createReflex( a, id );
	if ( sens == NULL )
	{
		s = QObject::tr( 
					"Can't create reflex ID %1.\n"
					).arg( id );
	}
	else
	{
		s = QObject::tr( 
					"Reflex ID %1 created.\n"
					).arg( id );
	}
	return s;
}
bool			AModReflex::newReflex		(
		const QString & s_cmd, const AaTkString & atks, QString & s_err )
{
	Q_ASSERT( s_cmd == "r.new" );
	return funcArg_AID( s_cmd, atks, s_err, do_new_reflex );
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
static QString	do_list_reflex				( Actor * a )
{
	QList<QStringList>	datao;
	QStringList			sl;
	sl.append( QObject::tr( "ID" ) );
	sl.append( QObject::tr( "Name" ) );
	sl.append( QObject::tr( "Cost" ) );
	sl.append( QObject::tr( "Energy" ) );
	datao.append( sl ); sl.clear();
	
	Reflex * iter = a->firstReflex();
	while ( iter != NULL )
	{
		sl.append( QString::number( iter->identificator() ) );
		sl.append( iter->myName() );
		sl.append( QString::number( iter->cost() ) );
		sl.append( QString::number( iter->energy() ) );
		datao.append( sl );  sl.clear();
		
		iter = nextReflex_(iter);
	}
	AOutput::showTable( datao, true );
	return QString();
}
bool			AModReflex::listReflex		(
		const QString & s_cmd, const AaTkString & atks, QString & s_err )
{
	Q_ASSERT( s_cmd == "r.list" );
	return funcArg_A0( s_cmd, atks, s_err, do_list_reflex );
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
static QString	do_kinds_reflex				( World * w )
{
	
	QList<QStringList>	datao;
	QStringList			sl;
	sl.append( QObject::tr( "ID" ) );
	sl.append( QObject::tr( "Name" ) );
	sl.append( QObject::tr( "Factory name" ) );
	datao.append( sl ); sl.clear();

	const QMap<ID,ReflexFactory*> & sf = w->reflexFactories();
	QMap<ID,ReflexFactory*>::ConstIterator itr = sf.constBegin();
	QMap<ID,ReflexFactory*>::ConstIterator itr_e = sf.constEnd();
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
bool			AModReflex::kindsReflex		(
		const QString & s_cmd, const AaTkString & atks, QString & s_err )
{
	Q_ASSERT( s_cmd == "r.kinds" );
	return funcArg0W( s_cmd, atks, s_err, do_kinds_reflex );
}
/* ========================================================================= */

/*  CLASS    =============================================================== */
//
//
//
//
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
