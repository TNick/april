/* ========================================================================= */
/* ------------------------------------------------------------------------- */
/*!
  \file			amodactuator.cc
  \date			Apr 2013
  \author		TNick

  \brief		Contains the implementation of AModActuator class


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

#include	"amodactuator.h"
#include	<april/aprillibrary.h>
#include	<april/logic/world.h>
#include	<april/logic/actor.h>
#include	<april/logic/actuator.h>
#include	<april/logic/actuatorfactory.h>
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
AModActuator::AModActuator	( CommandMap * cmd_map )
	: AprilModule(cmd_map)
{
	APRDBG_CDTOR;
	/* stub */
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
AModActuator::~AModActuator	( void )
{
	APRDBG_CDTOR;
	/* stub */
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void			AModActuator::insertCommands			( CommandMap * cm )
{
	/// @cond internal
	
	//! register a command from this package 
#define addOneCmd(c)	\
	cm->addCommand( QObject::tr( "ak." stringify(c) ), AModActuator::c##Actuator )
	
	addOneCmd(new);
	addOneCmd(list);
	addOneCmd(kinds);
	
#undef addOneCmd
	//! @endcond
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void			AModActuator::removeCommands			( CommandMap * cm )
{
	/// @cond internal
	
	//! unregister a command from this package @internal
#define remOneCmd(c)	\
	cm->remCommand( QObject::tr( "ak." stringify(c) ), AModActuator::c##Actuator );
	
	remOneCmd(new);
	remOneCmd(list);
	remOneCmd(kinds);
	
#undef remOneCmd
	//! @endcond
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
QString			AModActuator::name				( void )
{
	return QObject::tr( "Actuator" );
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
static QString	do_new_actuator				( Actor * a, ID id )
{
	QString s;
	Actuator * sens = a->world()->createActuator( a, id );
	if ( sens == NULL )
	{
		s = QObject::tr( 
					"Can't create actuator ID %1.\n"
					).arg( id );
	}
	else
	{
		s = QObject::tr( 
					"Actuator ID %1 created.\n"
					).arg( id );
	}
	return s;
}
bool			AModActuator::newActuator		(
		const QString & s_cmd, const AaTkString & atks, QString & s_err )
{
	Q_ASSERT( s_cmd == "ak.new" );
	return funcArg_AID( s_cmd, atks, s_err, do_new_actuator );
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
static QString	do_list_actuator				( Actor * a )
{
	QList<QStringList>	datao;
	QStringList			sl;
	sl.append( QObject::tr( "ID" ) );
	sl.append( QObject::tr( "Name" ) );
	sl.append( QObject::tr( "Cost" ) );
	sl.append( QObject::tr( "Energy" ) );
	datao.append( sl ); sl.clear();
	
	Actuator * iter = a->firstActuator();
	while ( iter != NULL )
	{
		sl.append( QString::number( iter->identificator() ) );
		sl.append( iter->myName() );
		sl.append( QString::number( iter->cost() ) );
		sl.append( QString::number( iter->energy() ) );
		datao.append( sl );  sl.clear();
		
		iter = nextActuator_(iter);
	}
	AOutput::showTable( datao, true );
	return QString();
}
bool			AModActuator::listActuator		(
		const QString & s_cmd, const AaTkString & atks, QString & s_err )
{
	Q_ASSERT( s_cmd == "ak.list" );
	return funcArg_A0( s_cmd, atks, s_err, do_list_actuator );
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
static QString	do_kinds_actuator				( World * w )
{
	
	QList<QStringList>	datao;
	QStringList			sl;
	sl.append( QObject::tr( "ID" ) );
	sl.append( QObject::tr( "Name" ) );
	sl.append( QObject::tr( "Factory name" ) );
	datao.append( sl ); sl.clear();

	const QMap<ID,ActuatorFactory*> & sf = w->actuatorFactories();
	QMap<ID,ActuatorFactory*>::ConstIterator itr = sf.constBegin();
	QMap<ID,ActuatorFactory*>::ConstIterator itr_e = sf.constEnd();
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
bool			AModActuator::kindsActuator		(
		const QString & s_cmd, const AaTkString & atks, QString & s_err )
{
	Q_ASSERT( s_cmd == "ak.kinds" );
	return funcArg0W( s_cmd, atks, s_err, do_kinds_actuator );
}
/* ========================================================================= */

/*  CLASS    =============================================================== */
//
//
//
//
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
