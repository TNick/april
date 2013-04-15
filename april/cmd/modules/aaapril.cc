/* ========================================================================= */
/* ------------------------------------------------------------------------- */
/*!
  \file			aaapril.cc
  \date			Apr 2013
  \author		TNick
  
  \brief		Contains the implementation of AaApril class
  
  
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

#include	"aaapril.h"
#include	<april/cmd/commandmap.h>
#include	<april/cmd/aatokenizer.h>
#include	<april/logic/aaoutput.h>
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
AaApril::AaApril	( CommandMap * cmd_map )
	: AaModule(cmd_map)
{
	APRDBG_CDTOR;
	/* stub */
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
AaApril::~AaApril	( void )
{
	APRDBG_CDTOR;
	/* stub */
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void			AaApril::insertCommands			( CommandMap * cm )
{
	/// @cond internal
	
	//! register a command from this package 
#define addOneCmd(c)	\
	cm->addCommand( QObject::tr( "april." stringify(c) ), AaApril::c )
	
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
void			AaApril::removeCommands			( CommandMap * cm )
{
	/// @cond internal
	
	//! unregister a command from this package @internal
#define remOneCmd(c)	\
	cm->remCommand( QObject::tr( "april." stringify(c) ), AaApril::c );
	
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
QString			AaApril::name				( void )
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
bool			AaApril::commands			(
		const QString & s_cmd, const AaTkString & atks, QString & s_err )
{
	
	Q_ASSERT( s_cmd == "april.commands" );
	return funcArg0( s_cmd, atks, s_err, do_commands );
}
/* ========================================================================= */
//	Q_UNUSED( s_cmd );

//	int arg_cnt = atks.tk_.count() - 1;
//	QString arg1;
//	for ( ;; )
//	{
//		if ( arg_cnt == 0 )
//		{
//			QStringList sl = AbstractApril::commands();
//			s_err.append( sl.join( QChar( '\n' ) ) );
//			return false;
//		}
//		else if ( arg_cnt == 1 )
//		{
//			arg1 = atks.getToken( 1 );
//			if ( arg1 == QObject::tr( "help" ) )
//				break;
//			errorUnknownOprion( s_err, arg1 );
//			break;
//		}
//		else
//		{
//			errorNumberOfArguments( s_err );
//			break;
//		}
//	}
//	/* print the usage */
//	s_err.append( QObject::tr( 
//					  "Usage:\n"
//					  "    april.commands         "
//					  "lists the commands\n"
//					  "    april.commands help    "
//					  "prints usage instructions\n"
//					  "\n"
//					  ) );
//	return false;

/* ------------------------------------------------------------------------- */
static QString	do_modules					( void )
{
	QStringList sl = CommandMap::defaultInstance()->modules();
	return sl.join( QChar( '\n' ) );
}
bool			AaApril::modules			(
		const QString & s_cmd, const AaTkString & atks, QString & s_err )
{
	Q_ASSERT( s_cmd == "april.modules" );
	return funcArg0( s_cmd, atks, s_err, do_modules );
}
/* ========================================================================= */

//	
//	Q_UNUSED( s_cmd );

//	int arg_cnt = atks.tk_.count() - 1;
//	QString arg1;
//	for ( ;; )
//	{
//		if ( arg_cnt == 0 )
//		{
//			QStringList sl = AbstractApril::modules();
//			s_err.append( sl.join( QChar( '\n' ) ) );
//			return false;
//		}
//		else if ( arg_cnt == 1 )
//		{
//			arg1 = atks.getToken( 1 );
//			if ( arg1 == QObject::tr( "help" ) )
//				break;
//			errorUnknownOprion( s_err, arg1 );
//			break;
//		}
//		else
//		{
//			errorNumberOfArguments( s_err );
//			break;
//		}
//	}
//	/* print the usage */
//	s_err.append( QObject::tr( 
//					  "Usage:\n"
//					  "    april.modules          "
//					  "lists the modules\n"
//					  "    april.modules help     "
//					  "prints usage instructions\n"
//					  "\n"
//					  ) );
//	return false;


/* ------------------------------------------------------------------------- */
static QString	do_version					( void )
{
	return QObject::tr( "April Version " APRIL_VER_STR "\n" );
}
bool			AaApril::version			(
		const QString & s_cmd, const AaTkString & atks, QString & s_err )
{
	Q_ASSERT( s_cmd == "april.version" );
	return funcArg0( s_cmd, atks, s_err, do_version );
}
/* ========================================================================= */

//	int arg_cnt = atks.tk_.count() - 1;
//	QString arg1;
//	for ( ;; )
//	{
//		if ( arg_cnt == 0 )
//		{
//			s_err.append( QObject::tr( "April Version " APRIL_VER_STR "\n" ) );
//			return false;
//		}
//		else if ( arg_cnt == 1 )
//		{
//			arg1 = atks.getToken( 1 );
//			if ( arg1 == QObject::tr( "help" ) )
//				break;
//			errorUnknownOprion( s_err, arg1 );
//			break;
//		}
//		else
//		{
//			errorNumberOfArguments( s_err );
//			break;
//		}
//	}
//	/* print the usage */
//	s_err.append( QObject::tr( 
//					  "Usage:\n"
//					  "    april.version          "
//					  "display the version\n"
//					  "    april.version help     "
//					  "prints usage instructions\n"
//					  "\n"
//					  ) );
//	return false;

/* ------------------------------------------------------------------------- */
static QString	do_copyright				( void )
{
	QString	s;
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
bool			AaApril::copyright			(
		const QString & s_cmd, const AaTkString & atks, QString & s_err )
{
	Q_ASSERT( s_cmd == "april.copyright" );
	return funcArg0( s_cmd, atks, s_err, do_copyright );
}
/* ========================================================================= */
	
//	Q_UNUSED( s_cmd );
	
//	int arg_cnt = atks.tk_.count() - 1;
//	QString arg1;
//	for ( ;; )
//	{
//		if ( arg_cnt == 0 )
//		{
//			if ( QDir().exists( "COPYING" ) )
//			{
//				QFile f( "COPYING" );
//				if ( f.open( QIODevice::ReadOnly ) )
//				{
//					QString	s( f.readAll() );
//					s_err.append( s );
//					f.close();
//					return false;
//				}
//			}
//			s_err.append( 
//						QObject::tr( 
//							"April project is distributed under the\n"
//							"3-clause (New) BSD license. You can read\n"
//							"more about it in COPYING file distributed\n"
//							"with the package or by searching the internet.\n"
//							) );
//			return false;
//		}
//		else if ( arg_cnt == 1 )
//		{
//			arg1 = atks.getToken( 1 );
//			if ( arg1 == QObject::tr( "help" ) )
//				break;
//			errorUnknownOprion( s_err, arg1 );
//			break;
//		}
//		else
//		{
//			errorNumberOfArguments( s_err );
//			break;
//		}
//	}
//	/* print the usage */
//	s_err.append( QObject::tr( 
//					  "Usage:\n"
//					  "    april.copyright        "
//					  "display information about copyright\n"
//					  "    april.copyright help   "
//					  "prints usage instructions\n"
//					  "\n"
//					  ) );
//	return false;

/* ------------------------------------------------------------------------- */
static QString	do_prompt				( 
		const QString & s_arg_1, const AaToken & tk1 )
{
	Q_UNUSED( tk1 );
	AaOutput::setPrompt( s_arg_1 );
	return QObject::tr( "Prompt changed to %1.\n" ).arg( s_arg_1 );
}
bool			AaApril::prompt			(
		const QString & s_cmd, const AaTkString & atks, QString & s_err )
{
	Q_ASSERT( s_cmd == "april.prompt" );
	return funcArg1( s_cmd, atks, s_err, do_prompt );
}
/* ========================================================================= */

//	Q_ASSERT( atks.tk_.count() >= 1 );
//	Q_ASSERT( s_cmd == "april.prompt" );
//	int arg_cnt = atks.tk_.count() - 1;
	
//	for ( ;; )
//	{
//		if ( arg_cnt != 1 )
//		{
//			errorOneArgumentExpected ( s_err );
//			break;
//		}
//		QString arg1 = atks.getToken( 1 );
//		if ( arg1 == QObject::tr( "help" ) )
//			break;
//		AaOutput::setPrompt( arg1 );
//		s_err.append( QObject::tr( "Prompt changed to %1.\n" ).arg( arg1 ) );
//		return false;
//	}
	
//	/* print the usage */
//	s_err.append( QObject::tr( 
//					  "Usage:\n"
//					  "    april.prompt \"new-one\" "
//					  "change the prompt to specified string\n"
//					  "    april.prompt help      "
//					  "prints usage instructions\n"
//					  "\n"
//					  ) );
//	return false;

/*  CLASS    =============================================================== */
//
//
//
//
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
