/* ========================================================================= */
/* ------------------------------------------------------------------------- */
/*!
  \file			target.cc
  \date			Jun 2013
  \author		TNick
  
  \brief		Contains the implementation of Target class
  
  
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

#include	"target.h"
#include	"cmdtest.h"
#include	"doevents.h"
#include	<QDebug>
#include	<QDir>
#include	<QFileInfo>
#include	<QStandardPaths>

/*  INCLUDES    ============================================================ */
//
//
//
//
/*  DEFINITIONS    --------------------------------------------------------- */

using namespace cmd_test;

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
Target::Target	( const QString & command )
	: QProcess(),
	  s_name_( command ),
	  i_failed_( 0 ),
	  i_success_( 0 )
{
	CmdTest::log( CmdTest::LOG_TARGETS,
				  QString( "Target %1 created" ).arg( command ) );
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
Target::~Target	( void )
{
	/* stub */
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool				Target::start				( const QStringList & args )
{
	QString s_path;
	QFileInfo fi( s_name_ );
	if ( fi.exists() == false )
	{
		s_path = QStandardPaths::findExecutable( s_name_ );
		if ( s_path.isEmpty() )
		{
			CmdTest::error( QString( "Executable %1 does not exists %1" )
							.arg( fi.absoluteFilePath() ) );
			return false;
		}
		fi.setFile( s_path );
	}
	else
	{
		s_path = fi.absoluteFilePath();
	}
	if ( fi.isExecutable() == false )
	{
		CmdTest::error( QString( "File %1 exists but is not executable" )
		.arg( fi.absoluteFilePath() ) );
		return false;
	}
	dbgtext2l( "Executable path: ", s_path );
	
	QProcess::start( s_path, args );
	DoEvents::wait( 1000 );
	
	bool b = waitForStarted( 50000 );
	debugPrint();
	if ( b == false )
	{
		CmdTest::error( QString( "Can't start process %1\n%2" )
		.arg( s_name_ ).arg( errorString() ) );
		return false;
	}
	return true;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void				Target::debugPrint			( void )
{
	qDebug() << "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<";
	qDebug() << this;
	qDebug() << "program " << program();
	qDebug() << "arguments " << arguments();
	qDebug() << "readChannelMode " << readChannelMode();
	qDebug() << "processChannelMode " << processChannelMode();
	qDebug() << "readChannel " << readChannel();
	qDebug() << "workingDirectory " << workingDirectory();
	qDebug() << "environment " << environment();
	qDebug() << "processEnvironment " << processEnvironment().toStringList();
	qDebug() << "error " << error();
	qDebug() << "errorString " << errorString();
	qDebug() << "state " << state();
	qDebug() << "pid " << pid();
	qDebug() << "readAllStandardOutput " << readAllStandardOutput();
	qDebug() << "readAllStandardError " << readAllStandardError();
	qDebug() << "exitCode " << exitCode();
	qDebug() << "exitStatus " << exitStatus();
	qDebug() << "bytesAvailable " << bytesAvailable();
	qDebug() << "bytesToWrite " << bytesToWrite();
	qDebug() << "isSequential " << isSequential();
	qDebug() << "canReadLine " << canReadLine();
	qDebug() << "atEnd " << atEnd();
	qDebug() << "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<";
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void				Target::activate			( void )
{
	CmdTest::log( CmdTest::LOG_TARGETS,
				  QString( "Switcing to target %1" ).arg( name() ) );
	
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool				Target::testRunning			( void )
{
	if ( state() != QProcess::Running )
	{
		CmdTest::failedTest( this, 
							 QString( "Target %1 is not running" )
							 .arg( name() ) );
		return false;
	}
	return true;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void				Target::discardContent			( void )
{
	if ( state() != QProcess::Running )
	{
		return;
	}
	QByteArray inp = readAll();
	dbgtext3l( 
				"DISCARDED CONTENT: vvvvvvvvvvvvvvvvvvvvv \n", 
				inp.constBegin() ,
				"\nDISCARDED CONTENT: ^^^^^^^^^^^^^^^^^^^^^ \n"
				);
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool				Target::sendCommand			( const QString & s_cmd )
{
	debugPrint();
	if ( testRunning() == false )
		return true;
	discardContent();
	CmdTest::log( CmdTest::LOG_COMMANDS,
				  QString( "Command %1 to %2" ).arg( s_cmd ).arg( name() ) );
	
	write( s_cmd.toLatin1() );
	
	return true;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool				Target::expectOutput		( const QString & s_out )
{
	if ( testRunning() == false )
		return true;
	QRegExp rex( s_out );
	Q_UNUSED( rex );
	CmdTest::log( CmdTest::LOG_COMMANDS,
				  QString( "Expect %1 from %2" ).arg( s_out ).arg( name() ) );
	int time_out = 5;
	
	if ( waitForReadyRead( time_out * 1000 ) == false )
	{
		CmdTest::failedTest( 
					this, 
					QString( "Timed out (%1 sec) expecting for %2" )
					.arg( time_out )
					.arg( s_out )  );
	}
	else 
	{
		QString out = readAll();
		if ( rex.indexIn( out ) )
		{
			CmdTest::successTest( 
						this, 
						QString( "Found pattern %1 in output" )
						.arg( s_out ) 
						);
		}
		else
		{
			CmdTest::failedTest( 
						this, 
						QString( "Not found pattern %1 in output" )
						.arg( s_out )
						);
		}
	}
	
	return true;
}
/* ========================================================================= */



/*  CLASS    =============================================================== */
//
//
//
//
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
