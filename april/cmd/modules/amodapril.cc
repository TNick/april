/* ========================================================================= */
/* ------------------------------------------------------------------------- */
/*!
  \file			amodapril.cc
  \date			Apr 2013
  \author		TNick
  
  \brief		Contains the implementation of AModApril class
  
  
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

#include	"amodapril.h"
#include	<april/cmd/commandmap.h>
#include	<april/cmd/apriltokenizer.h>
#include	<april/logic/aoutput.h>
#include	<april/logic/world.h>
#include	<april/plugins/aprilplugininterf.h>
#include	<april/aprillibrary.h>
#include	<QObject>
#include	<QStringList>
#include	<QDir>


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
AModApril::AModApril	( CommandMap * cmd_map )
	: AprilModule(cmd_map)
{
	APRDBG_CDTOR;
	/* stub */
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
AModApril::~AModApril	( void )
{
	APRDBG_CDTOR;
	/* stub */
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void			AModApril::insertCommands			( CommandMap * cm )
{
	/// @cond internal
	
	//! register a command from this package 
#define addOneCmd(c)	\
	cm->addCommand( QObject::tr( "april." stringify(c) ), AModApril::c )
	
	addOneCmd(commands);
	addOneCmd(modules);
	addOneCmd(version);
	addOneCmd(copyright);
	addOneCmd(prompt);
	
#undef addOneCmd
	//! @endcond
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void			AModApril::removeCommands			( CommandMap * cm )
{
	/// @cond internal
	
	//! unregister a command from this package @internal
#define remOneCmd(c)	\
	cm->remCommand( QObject::tr( "april." stringify(c) ), AModApril::c );
	
	remOneCmd(commands);
	remOneCmd(modules);
	remOneCmd(version);
	remOneCmd(copyright);
	remOneCmd(prompt);
	
#undef remOneCmd
	//! @endcond
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
QString			AModApril::name				( void )
{
	return QObject::tr( "April" );
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
static QString	do_commands					( void )
{
	QStringList sl = CommandMap::defaultInstance()->commands();
	return sl.join( QChar( '\n' ) );
}
bool			AModApril::commands			(
		const QString & s_cmd, const AaTkString & atks, QString & s_err )
{
	
	Q_ASSERT( s_cmd == "april.commands" );
	return funcArg0( s_cmd, atks, s_err, do_commands );
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
static QString	do_modules					( void )
{
	QStringList sl = CommandMap::defaultInstance()->modules();
	return sl.join( QChar( '\n' ) );
}
bool			AModApril::modules			(
		const QString & s_cmd, const AaTkString & atks, QString & s_err )
{
	Q_ASSERT( s_cmd == "april.modules" );
	return funcArg0( s_cmd, atks, s_err, do_modules );
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
static QString	do_version					( void )
{
	return QObject::tr( "April Version " APRIL_VER_STR "\n" );
}
bool			AModApril::version			(
		const QString & s_cmd, const AaTkString & atks, QString & s_err )
{
	Q_ASSERT( s_cmd == "april.version" );
	return funcArg0( s_cmd, atks, s_err, do_version );
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
static QString	do_copyright				( void )
{
	if ( QDir().exists( "COPYING" ) )
	{
		QFile f( "COPYING" );
		if ( f.open( QIODevice::ReadOnly ) )
		{
			QString	s = QString( f.readAll() );
			f.close();
			return s;
		}
	}
	return QObject::tr( 
				"April project is distributed under the\n"
				"3-clause (New) BSD license. You can read\n"
				"more about it in COPYING file distributed\n"
				"with the package or by searching the internet.\n"
				) ;
}
bool			AModApril::copyright			(
		const QString & s_cmd, const AaTkString & atks, QString & s_err )
{
	Q_ASSERT( s_cmd == "april.copyright" );
	return funcArg0( s_cmd, atks, s_err, do_copyright );
}
/* ========================================================================= */
	
/* ------------------------------------------------------------------------- */
static QString	do_prompt				( 
		const QString & s_arg_1, const AaToken & tk1 )
{
	Q_UNUSED( tk1 );
	AOutput::setPrompt( s_arg_1 );
	return QObject::tr( "Prompt changed to %1.\n" ).arg( s_arg_1 );
}
bool			AModApril::prompt			(
		const QString & s_cmd, const AaTkString & atks, QString & s_err )
{
	Q_ASSERT( s_cmd == "april.prompt" );
	return funcArg1( s_cmd, atks, s_err, do_prompt );
}
/* ========================================================================= */

/*  CLASS    =============================================================== */
//
//
//
//
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
