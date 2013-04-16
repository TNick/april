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
	cm->addCommand( QObject::tr( "a." stringify(c) ), AModSensor::c##Sensor )
	
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
	cm->remCommand( QObject::tr( "a." stringify(c) ), AModSensor::c##Sensor );
	
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
bool			AModSensor::newSensor		(
		const QString & s_cmd, const AaTkString & atks, QString & s_err )
{
	Q_ASSERT( s_cmd == "s.new" );
	return false;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool			AModSensor::listSensor		(
		const QString & s_cmd, const AaTkString & atks, QString & s_err )
{
	Q_ASSERT( s_cmd == "s.list" );
	return false;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool			AModSensor::kindsSensor		(
		const QString & s_cmd, const AaTkString & atks, QString & s_err )
{
	Q_ASSERT( s_cmd == "s.kinds" );
	return false;
}
/* ========================================================================= */

/*  CLASS    =============================================================== */
//
//
//
//
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
