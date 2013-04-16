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
	cm->addCommand( QObject::tr( "a." stringify(c) ), AModActuator::c##Actuator )
	
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
	cm->remCommand( QObject::tr( "a." stringify(c) ), AModActuator::c##Actuator );
	
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
bool			AModActuator::newActuator		(
		const QString & s_cmd, const AaTkString & atks, QString & s_err )
{
	Q_ASSERT( s_cmd == "ak.new" );
	return false;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool			AModActuator::listActuator		(
		const QString & s_cmd, const AaTkString & atks, QString & s_err )
{
	Q_ASSERT( s_cmd == "ak.list" );
	return false;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool			AModActuator::kindsActuator		(
		const QString & s_cmd, const AaTkString & atks, QString & s_err )
{
	Q_ASSERT( s_cmd == "ak.kinds" );
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
