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
	cm->addCommand( QObject::tr( "a." stringify(c) ), AModBrain::c##Brain )
	
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
	cm->remCommand( QObject::tr( "a." stringify(c) ), AModBrain::c##Brain );
	
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
bool			AModBrain::newBrain		(
		const QString & s_cmd, const AaTkString & atks, QString & s_err )
{
	Q_ASSERT( s_cmd == "b.new" );
	return false;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool			AModBrain::listBrain		(
		const QString & s_cmd, const AaTkString & atks, QString & s_err )
{
	Q_ASSERT( s_cmd == "b.list" );
	return false;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool			AModBrain::kindsBrain		(
		const QString & s_cmd, const AaTkString & atks, QString & s_err )
{
	Q_ASSERT( s_cmd == "b.kinds" );
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
