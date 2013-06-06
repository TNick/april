/* ========================================================================= */
/* ------------------------------------------------------------------------- */
/*!
  \file			abstracta-main.cc
  \date			March 2013
  \author		TNick
  
  \brief		Contains application's entry point
  
  
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

#include	<april/april.h>
#include	<april/aprillibrary.h>
#include	<libbbb/2/doevents.h>

#include	<QString>
#include	<QTranslator>
#include	<QDir>
#include	<QSettings>
#include	<QCoreApplication>

#include	<iostream>
#include	<argtable2.h>

#include	<april/logic/aoutput.h>
#include	<april/cmd/commandmap.h>
#include	"abstractapril.h"

using namespace std;

/*  INCLUDES    ============================================================ */
//
//
//
//
/*  DEFINITIONS    --------------------------------------------------------- */

//! components of the arguments table
enum		ArgsTable		{
	ARG_HELP = 0,	/**< present help */
	ARG_VER,		/**< present version */
	ARG_COMMANDS,	/**< commands to execute then exit */
	ARG_CMDFILE,	/**< execute commands in file then exit */
	ARG_INIT_FILES,	/**< initial files */
	
	ARG_END,		/**< end marker */
	ARG_MAX			/**< error checking */
};

//!@{
//! direct access to arguments
#define a__help		((struct arg_lit *)argtable[ARG_HELP])
#define a__ver		((struct arg_lit *)argtable[ARG_VER])
#define a__init		((struct arg_file *)argtable[ARG_INIT_FILES])
#define a__cmds		((struct arg_str *)argtable[ARG_COMMANDS])
#define a__cmdfile	((struct arg_str *)argtable[ARG_CMDFILE])
#define a__end		((struct arg_end *)argtable[ARG_END])
//!@}

//!@{
//! application macro
#define	ABSTRACTA_NAME		"abstracta"
#define	LANG_FILE_PREFIX	ABSTRACTA_NAME "_"
#define	LANG_FILE_SUFFIX	".qm"
#define	LANG_FILE(loc)		(LANG_FILE_PREFIX + loc + LANG_FILE_SUFFIX)
//!@}

//! exit codes used by routins in this file
enum		ExitCode		{
	ExitOkBreak = -1,	/**< all went fine and should quit the program */
	ExitOk = 0,			/**< all went fine and should continue */
	ExitArgError,		/**< provided arguments were wrong */
	ExitFail,			/**< the command(s) failed to execute properly */
	
	ExitMax				/**< bounds check */
};

//! the program exited normally
#define EXIT_OK				0

//! exit is ok and should continue
#define EXIT_CONTINUE		-1

using namespace	april;
using namespace std;

/*  DEFINITIONS    ========================================================= */
//
//
//
//
/*  DATA    ---------------------------------------------------------------- */

//! table of arguments
void *				argtable[ARG_MAX];

//! files to load at start-up
QStringList			sl_init_load;

/*  DATA    ================================================================ */
//
//
//
//
/*  FUNCTIONS    ----------------------------------------------------------- */

/* ------------------------------------------------------------------------- */
//! load proper language file based on application location and settings
void		translatable		( void )
{
	/* application is translatable */
	QString locale = QSettings().value(
				"language",
				QLocale::system().name()
				).toString();
	QTranslator * translator = new QTranslator();
	QDir	d;
	QString s_file = d.absoluteFilePath( LANG_FILE( locale ) );
	if ( translator->load( s_file ) )
	{
		QCoreApplication::instance()->installTranslator( translator );
	}
#ifndef	QT_NO_DEBUG
	else
	{
		qDebug() << "Language file was not loded: " << s_file;
	}
#endif
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
//! initialisation method for the application
int			mainInit		( int argc, char *argv[] )
{
	
	/* prepare the ground for easy access to settings */
	QCoreApplication::setOrganizationName( "TNick" );
	QCoreApplication::setOrganizationDomain( "april.github.com/" );
	QCoreApplication::setApplicationName( ABSTRACTA_NAME );
	QByteArray	ba_help = QObject::tr( "print this help and exit" ).toLatin1();
	QByteArray	ba_ver = QObject::tr( "print version information and exit" ).toLatin1();
	QByteArray	ba_src = QObject::tr( "the world(s) to load" ).toLatin1();
	QByteArray	ba_cmd = QObject::tr( "execute these commands then exit" ).toLatin1();
	QByteArray	ba_cmdfile = QObject::tr( "execute commands in the file then exit" ).toLatin1();

	translatable();
	
	int					nerrors;
	
	argtable[ARG_HELP] = arg_lit0(
				NULL, "help",
				ba_help.constBegin()
				);
	
	argtable[ARG_VER] = arg_lit0(
				NULL, "version",
				ba_ver.constBegin()
				);
	
	argtable[ARG_INIT_FILES] = arg_file0(
				NULL, NULL,  "worlds", ba_src.constBegin()
				);
	
	argtable[ARG_COMMANDS] = arg_str0(
				"c", "commands",  NULL, ba_cmd.constBegin()
				);
				
	argtable[ARG_CMDFILE] = arg_str0(
				"f", "file",  NULL, ba_cmdfile.constBegin()
				);
	
	argtable[ARG_END] = arg_end( 20 );
	
	if ( arg_nullcheck( argtable ) != 0 )
	{
		AOutput::showError(
					QObject::tr( ABSTRACTA_NAME " initialisation error" ),
					QObject::tr( "Insufficient memory!\n" ) 
					);
		return ExitFail;
	}
	
	/* parse arguments */
	nerrors = arg_parse( argc, argv, argtable );
	
	if( a__help->count > 0 )
	{
		/* todo: should use AOutput */
		cout << QObject::tr( "Usage: " ABSTRACTA_NAME ).toLatin1().constBegin() << endl;
		arg_print_syntax( stdout, argtable, "\n" );
		cout << QObject::tr(
					"The program runs artificial worlds.\n" )
				.toLatin1().constBegin()
			 << endl;
		arg_print_glossary( stdout, argtable, "  %-10s %s\n" );
		return ExitOkBreak;
	}
	if( a__ver->count > 0 )
	{
		AOutput::showInfo( QString( ABSTRACTA_NAME " version %1.%2.%3\n" )
							.arg( APRIL_VERSION_MAJOR )
							.arg( APRIL_VERSION_MINOR )
							.arg( APRIL_VERSION_REV )
							.toLatin1().constBegin() );
		return ExitOkBreak;
	}
	if( nerrors > 0 )
	{
		/* todo: should use AOutput */
		arg_print_errors( stdout, a__end, ABSTRACTA_NAME );
		cerr << QString(
					"\nTry '" ABSTRACTA_NAME " --help' for more information.\n" )
				.toLatin1().constBegin()
			 << endl;
		return ExitArgError;
	}
	
	if ( initAprilLibrary() == false )
	{
		AOutput::showError( QObject::tr( ABSTRACTA_NAME " initialisation error" ), 
							 QObject::tr( "Could not initialise april library!\n" ) );
		return ExitFail;
	}
	
	/* files that should be loaded at startup */
	for ( int i = 0; i < a__init->count; i++ )
	{
		sl_init_load.append( a__init->filename[i] );
	}

	return ExitOk;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
//! ending function for the application
void			mainEnd			( void )
{
	
	endAprilLibrary();
	libbbb::DoEvents::wait(10);
	
#ifndef	QT_NO_DEBUG
#ifdef	BB_MEMTRACK
	/* check for memory leaks */
	MemTrackMng::dumpAllocated();
#endif
#endif
	
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
//! application entry point
int			main			( int argc, char *argv[] )
{
	int i_ret;
	
	/* prepare to start */
	QCoreApplication apl( argc, argv );
	Q_UNUSED( apl );
	
	i_ret = mainInit( argc, argv );
	if ( i_ret == ExitOk )
	{
		
		if ( a__cmds->count > 0 )
		{
			i_ret = AbstractApril::executeCommands( a__cmds->sval[0] );
		}
		else if ( a__cmdfile->count > 0 )
		{
			i_ret = AbstractApril::executeFile( a__cmdfile->sval[0] );
		}
		else
		{
			i_ret = AbstractApril::runMainLoop( sl_init_load );
		}
		mainEnd();
	}
	
	return i_ret;
}
/* ========================================================================= */

/*  FUNCTIONS    =========================================================== */
//
//
//
//
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
