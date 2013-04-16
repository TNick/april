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
	cm->addCommand( QObject::tr( "a." stringify(c) ), AModReflex::c##Reflex )
	
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
	cm->remCommand( QObject::tr( "a." stringify(c) ), AModReflex::c##Reflex );
	
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
bool			AModReflex::newReflex		(
		const QString & s_cmd, const AaTkString & atks, QString & s_err )
{
	Q_ASSERT( s_cmd == "r.new" );
	return false;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool			AModReflex::listReflex		(
		const QString & s_cmd, const AaTkString & atks, QString & s_err )
{
	Q_ASSERT( s_cmd == "r.list" );
	return false;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool			AModReflex::kindsReflex		(
		const QString & s_cmd, const AaTkString & atks, QString & s_err )
{
	Q_ASSERT( s_cmd == "r.kinds" );
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
