/* ========================================================================= */
/* ------------------------------------------------------------------------- */
/*!
  \file			aprildream-main.cc
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

#include	<QString>
#include	<QTranslator>
#include	<QDir>
#include	<QApplication>
#include	<QMessageBox>
#include	<QSettings>
#include	<iostream>
#include	<argtable2.h>

#include	<april/aprillibrary.h>
#include	<april/AprilDream/gui/mw.h>
#include	<libbbb/2/doevents.h>

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
	ARG_INIT_FILES,	/**< initial files */
	
	ARG_END,		/**< end marker */
	ARG_MAX			/**< error checking */
};

//!@{
//! easy access to argtable members

#define a__help		((struct arg_lit *)argtable[ARG_HELP])
#define a__ver		((struct arg_lit *)argtable[ARG_VER])
#define a__init		((struct arg_file *)argtable[ARG_INIT_FILES])
#define a__end		((struct arg_end *)argtable[ARG_END])

//!@}

//!@{
//! application macros

#define	APRILDREAM_NAME		"AprilDream"
#define	LANG_FILE_PREFIX	APRILDREAM_NAME "_"
#define	LANG_FILE_SUFFIX	".qm"
#define	LANG_FILE(loc)		(LANG_FILE_PREFIX + loc + LANG_FILE_SUFFIX)

//!@}

using namespace	april;
using namespace std;

/*  DEFINITIONS    ========================================================= */
//
//
//
//
/*  DATA    ---------------------------------------------------------------- */

//! the one and only main window
Gui::MW *			mw = NULL;

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
		qApp->installTranslator( translator );
	}
	else
	{
		qDebug() << "Language file was not loded: " << s_file;
	}
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
//! initialisation method for the application
int			mainInit		( int argc, char *argv[] )
{

	/* prepare the ground for easy access to settings */
	QCoreApplication::setOrganizationName( "TNick" );
	QCoreApplication::setOrganizationDomain( "april.github.com/" );
	QCoreApplication::setApplicationName( APRILDREAM_NAME );

	translatable();

	/* table of arguments */
	void *				argtable[ARG_MAX];
	int					nerrors;

	argtable[ARG_HELP] = arg_lit0(
				NULL, "help",
				QObject::tr( "print this help and exit" ).toLatin1()
				);

	argtable[ARG_VER] = arg_lit0(
				NULL, "version",
				QObject::tr( "print version information and exit" ).toLatin1()
				);

	argtable[ARG_INIT_FILES] = arg_file0(
				NULL, NULL,  NULL, "source"
				);

	argtable[ARG_END] = arg_end( 20 );

	if ( arg_nullcheck( argtable ) != 0 )
	{
		QMessageBox::warning(
					NULL, QObject::tr( APRILDREAM_NAME " initialisation error" ),
					QObject::tr( "Insufficient memory!\n" ),
					QMessageBox::Ok );
		return 1;
	}

	/* parse arguments */
	nerrors = arg_parse( argc, argv, argtable );

	if( a__help->count > 0 )
	{
		cout << QObject::tr( "Usage: " APRILDREAM_NAME ).toLatin1().constBegin() << endl;
		arg_print_syntax( stdout, argtable, "\n" );
		cout << QObject::tr(
					"The program runs artificial worlds.\n" )
				.toLatin1().constBegin()
			 << endl;
		arg_print_glossary( stdout, argtable, "  %-10s %s\n" );
		return 0;
	}
	if( a__ver->count > 0 )
	{
		cout << QString( APRILDREAM_NAME " version %1.%2.%3\n" )
				.arg( APRIL_VERSION_MAJOR )
				.arg( APRIL_VERSION_MINOR )
				.arg( APRIL_VERSION_REV )
				.toLatin1().constBegin()
			 << endl;
		return 0;
	}
	if( nerrors > 0 )
	{
		arg_print_errors( stdout, a__end, APRILDREAM_NAME );
		cerr << QString(
					"\nTry '" APRILDREAM_NAME " --help' for more information.\n" )
				.toLatin1().constBegin()
				<< endl;
		return 1;
	}

	if ( initAprilLibrary() == false )
	{
		QMessageBox::warning(
					NULL, QObject::tr( APRILDREAM_NAME " initialisation error" ),
					QObject::tr( "Could not initialise april library!\n" ),
					QMessageBox::Ok );
		return -1;
	}


	/* do your thing */
	mw = new Gui::MW();
	mw->show();
	mw->setAttribute( Qt::WA_DeleteOnClose );

	/* files that should be loaded at startup
	QStringList	sl;
	for ( int i = 0; i < a__init->count; i++ )
	{
		if ( mw->openFile( a__init->filename[i] ) == false )
		{
			sl.append(	QObject::tr( "The file %1\ncould not be opened." )
						.arg( argv[i] ) );
		}
	}
	if ( sl.count() > 0 )
	{
		QMessageBox::warning(
					mw, QObject::tr( "Error opening file(s)" ),
					sl.join( "\n" ) + "\n",
					QMessageBox::Ok );
	}
	*/
	return 0;
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
	QApplication apl( argc, argv );

	i_ret = mainInit( argc, argv );
	if ( i_ret == 0 )
	{
		i_ret = apl.exec();
		mainEnd();
	}

	return i_ret;
}
/* ========================================================================= */

/*
Shortcut table (for the ones assigned by hand)


CTRL		CTRL+		CTRL+
			SHIFT		ALT

*/


/*  FUNCTIONS    =========================================================== */
//
//
//
//
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
