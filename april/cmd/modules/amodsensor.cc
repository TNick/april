/* ========================================================================= */
/* ------------------------------------------------------------------------- */
/*!
  \file			amodsensor.cc
  \date			Apr 2013
  \author		TNick
  
  \brief		Contains the implementation of AModSensor class
  
  
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

#include	"amodsensor.h"
#include	<april/aprillibrary.h>
#include	<april/logic/world.h>
#include	<april/logic/actor.h>
#include	<april/logic/genericactorfactory.h>
#include	<april/logic/aoutput.h>
#include	<april/logic/sensor.h>
#include	<april/logic/sensorfactory.h>
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
AModSensor::AModSensor	( CommandMap * cmd_map )
	: AprilModule(cmd_map)
{
	APRDBG_CDTOR;
	/* stub */
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
AModSensor::~AModSensor	( void )
{
	APRDBG_CDTOR;
	/* stub */
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void			AModSensor::insertCommands			( CommandMap * cm )
{
	/// @cond internal
	
	//! register a command from this package 
#define addOneCmd(c)	\
	cm->addCommand( QObject::tr( "s." stringify(c) ), AModSensor::c##Sensor )
	
	addOneCmd(new);
	addOneCmd(list);
	addOneCmd(kinds);
	
#undef addOneCmd
	//! @endcond
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void			AModSensor::removeCommands			( CommandMap * cm )
{
	/// @cond internal
	
	//! unregister a command from this package @internal
#define remOneCmd(c)	\
	cm->remCommand( QObject::tr( "s." stringify(c) ), AModSensor::c##Sensor );
	
	remOneCmd(new);
	remOneCmd(list);
	remOneCmd(kinds);
	
#undef remOneCmd
	//! @endcond
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
QString			AModSensor::name				( void )
{
	return QObject::tr( "Sensor" );
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
static QString	do_new_sensor				( Actor * a, ID id )
{
	QString s;
	Sensor * sens = a->world()->createSensor( a, id );
	if ( sens == NULL )
	{
		s = QObject::tr( 
					"Can't create sensor ID %1.\n"
					).arg( id );
	}
	else
	{
		s = QObject::tr( 
					"Sensor ID %1 created.\n"
					).arg( id );
	}
	return s;
}
bool			AModSensor::newSensor		(
		const QString & s_cmd, const AaTkString & atks, QString & s_err )
{
	Q_ASSERT( s_cmd == "s.new" );
	return funcArg_AID( s_cmd, atks, s_err, do_new_sensor );
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
static QString	do_list_sensor				( Actor * a )
{
	
	QList<QStringList>	datao;
	QStringList			sl;
	sl.append( QObject::tr( "ID" ) );
	sl.append( QObject::tr( "Name" ) );
	sl.append( QObject::tr( "Cost" ) );
	sl.append( QObject::tr( "Energy" ) );
	datao.append( sl ); sl.clear();
	
	Sensor * iter = a->firstSensor();
	while ( iter != NULL )
	{
		sl.append( QString::number( iter->identificator() ) );
		sl.append( iter->myName() );
		sl.append( QString::number( iter->cost() ) );
		sl.append( QString::number( iter->energy() ) );
		datao.append( sl );  sl.clear();
		
		iter = nextSensor_(iter);
	}
	AOutput::showTable( datao, true );
	return QString();
}
bool			AModSensor::listSensor		(
		const QString & s_cmd, const AaTkString & atks, QString & s_err )
{
	Q_ASSERT( s_cmd == "s.list" );
	return funcArg_A0( s_cmd, atks, s_err, do_list_sensor );
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
static QString	do_kinds_sensor				( World * w )
{
	
	QList<QStringList>	datao;
	QStringList			sl;
	sl.append( QObject::tr( "ID" ) );
	sl.append( QObject::tr( "Name" ) );
	sl.append( QObject::tr( "Factory name" ) );
	datao.append( sl ); sl.clear();

	const QMap<ID,SensorFactory*> & sf = w->sensorFactories();
	QMap<ID,SensorFactory*>::ConstIterator itr = sf.constBegin();
	QMap<ID,SensorFactory*>::ConstIterator itr_e = sf.constEnd();
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
bool			AModSensor::kindsSensor		(
		const QString & s_cmd, const AaTkString & atks, QString & s_err )
{
	Q_ASSERT( s_cmd == "s.kinds" );
	return funcArg0W( s_cmd, atks, s_err, do_kinds_sensor );
}
/* ========================================================================= */

/*  CLASS    =============================================================== */
//
//
//
//
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
