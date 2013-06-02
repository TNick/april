/* ========================================================================= */
/* ------------------------------------------------------------------------- */
/*!
  \file			cmdtest.cc
  \date			Jun 2013
  \author		TNick
  
  \brief		Contains the implementation of CmdTest class
  
  
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

#include	"cmdtest.h"
#include	"target.h"
#include	<QFile>
#include	<QDebug>

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

CmdTest *	CmdTest::uniq_ = NULL;

/*  DATA    ================================================================ */
//
//
//
//
/*  CLASS    --------------------------------------------------------------- */

/* ------------------------------------------------------------------------- */
CmdTest::CmdTest	( void ) :
	targets_(),
	files_(),
	t_crt_( NULL ),
	file_crt_( -1 ),
	log_types_( LOG_ALL ) //,
  //	target_regex_( "^\\s*TARGET\\s+(.*)\\s*" ),
  //	command_regex_( "^\\s*COMMAND\\s+(.*)\\s*" ),
  //	expect_regex_( "^\\s*EXPECT\\s+(.*)\\s*" ),
  //	include_regex_( "^\\s*INCLUDE\\s+(.*)\\s*" ),
  //	white_regex_( "^\\s*$" ),
  //	comment_regex_( "^\\s*#" )
{
	Q_ASSERT( uniq_ == NULL );
	uniq_ = this;
	
	
	CmdEntry cmd;
	
	cmd.rex_.setPattern( "^\\s*#" );
	cmd.call_ = commandComments;
	commands_.append( cmd );
	
	cmd.rex_.setPattern( "^\\s*$" );
	cmd.call_ = commandWhites;
	commands_.append( cmd );
	
	cmd.rex_.setPattern( "^\\s*TARGET\\s+(.*)\\s+ARGS\\s+(.*)\\s*" );
	cmd.call_ = commandTargetArgs;
	commands_.append( cmd );
	
	cmd.rex_.setPattern( "^\\s*TARGET\\s+(.*)\\s*" );
	cmd.call_ = commandTarget;
	commands_.append( cmd );
	
	cmd.rex_.setPattern( "^\\s*SWITCH\\s+TO\\s+(.*)\\s*" );
	cmd.call_ = commandSwitch;
	commands_.append( cmd );
	
	cmd.rex_.setPattern( "^\\s*END\\s+TARGET(\\s+(.*)\\s*)*" );
	cmd.call_ = commandEndTarget;
	commands_.append( cmd );
	
	cmd.rex_.setPattern( "^\\s*COMMAND\\s+(.*)\\s*" );
	cmd.call_ = commandCommand;
	commands_.append( cmd );
	
	cmd.rex_.setPattern( "^\\s*EXPECTE\\s+(.*)\\s*" );
	cmd.call_ = commandExpectE;
	commands_.append( cmd );
	
	cmd.rex_.setPattern( "^\\s*EXPECTO\\s+(.*)\\s*" );
	cmd.call_ = commandExpectO;
	commands_.append( cmd );
	
	cmd.rex_.setPattern( "^\\s*EXPECT\\s+(.*)\\s*" );
	cmd.call_ = commandExpect;
	commands_.append( cmd );
	
	cmd.rex_.setPattern( "^\\s*INCLUDE\\s+(.*)\\s*" );
	cmd.call_ = commandInclude;
	commands_.append( cmd );
	
	cmd.rex_.setPattern( "^\\s*EXIT\\s+CODE\\s+NOT\\s+(.*)\\s*" );
	cmd.call_ = commandExitNot;
	commands_.append( cmd );
	
	cmd.rex_.setPattern( "^\\s*EXIT\\s+CODE\\s+(.*)\\s*" );
	cmd.call_ = commandExit;
	commands_.append( cmd );
	
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
CmdTest::~CmdTest	( void )
{
	Q_ASSERT( uniq_ == this );
	foreach( Target * t, targets_ )
	{
		t->deleteLater();
	}
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool				CmdTest::init			( void )
{
	if (  uniq_ == NULL )
		new CmdTest();
	return true;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void				CmdTest::end			( void )
{
	if ( uniq_ != NULL )
	{
		delete uniq_;
	}
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
QString				CmdTest::crtFile		( void )
{
	if ( uniq_->file_crt_ == -1 )
		return QString();
	else
		return uniq_->files_.at( uniq_->file_crt_ );
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool				CmdTest::get_file_contents		(
		const QString & filename, QStringList & contents )
{
	QFile file( filename );
	if ( !file.open(QIODevice::ReadOnly) ) 
	{
		return false;
	}
	QTextStream in( &file );
	contents = in.readAll().split( "\n" );
	return true;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool				CmdTest::processFile	( const QString & s_file )
{
	log( LOG_FILES, QString( "Including file %1" ).arg( s_file ) );
	if ( uniq_->files_.contains( s_file, Qt::CaseInsensitive ) )
	{
		error( QString( "Including file %1 would cause an infinite loop." )
			   .arg( s_file )
			   );
		return false;
	}
	uniq_->file_crt_ = uniq_->files_.count();
	uniq_->files_.append( s_file );
	
	QStringList file_contents;
	if ( get_file_contents( s_file, file_contents ) == false )
	{
		error( QString( "Can't read file %1!" ).arg( s_file ) );
		return false;
	}
	int i_line = 0;
	int i_max = file_contents.count();
	int i_cmd_max = uniq_->commands_.count();
	while ( i_line < i_max )
	{
		QString s_line = file_contents.at( i_line );
		bool b_found = false;
		for ( int i_cmd = 0; i_cmd < i_cmd_max; i_cmd++ )
		{
			const CmdEntry & cmd = uniq_->commands_.at( i_cmd );
			if ( cmd.rex_.indexIn( s_line ) != -1 )
			{
				cmd.call_( cmd );
				b_found = true;
				break;
			}
		}
		if ( b_found == false )
		{
			fileError( "Line was not understood" );
		}
		i_line++;
	}
	return true;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
int					CmdTest::findTargetId	( const QString & s_name )
{
	Q_ASSERT( uniq_ != NULL );
	int i = 0;
	foreach( Target * t, uniq_->targets_ )
	{
		if ( !QString::compare( t->name(), s_name, Qt::CaseInsensitive ) )
		{
			return i;
		}
		i++;
	}
	return -1;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
int					CmdTest::findTargetId	( const Target * trg )
{
	Q_ASSERT( uniq_ != NULL );
	return uniq_->targets_.indexOf( (Target*)trg );
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
Target *			CmdTest::findTarget		( const QString & s_name )
{
	Q_ASSERT( uniq_ != NULL );
	int i = findTargetId( s_name );
	if ( i == -1 )
		return NULL;
	return uniq_->targets_.at( i );
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
Target *			CmdTest::getTarget		( const QString & s_name )
{
	Q_ASSERT( uniq_ != NULL );
	Target * ret; /* = findTarget( s_name );
	if ( ret != NULL )
	{
		ret->activate();
		uniq_->t_crt_ = ret;
		return NULL;
	}*/
	
	ret = new Target( s_name );
	uniq_->targets_.append( ret );
	uniq_->t_crt_ = ret;
	ret->start();
	return ret;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool				CmdTest::sendCommand	( const QString & s_cmd )
{
	Q_ASSERT( uniq_ != NULL );
	if ( uniq_->t_crt_ == NULL )
	{
		error( 
					"There is no current target.\n"
					"Set a target first using TARGET directive\n"
					);
		return false;
	}
	return uniq_->t_crt_->sendCommand( s_cmd );
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool				CmdTest::expectOutput	( const QString & s_out )
{
	Q_ASSERT( uniq_ != NULL );
	if ( uniq_->t_crt_ == NULL )
	{
		error( 
					"There is no current target.\n"
					"Set a target first using TARGET directive\n"
					);
		return false;
	}
	return uniq_->t_crt_->expectOutput( s_out );
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void				CmdTest::error			( const QString & s_text )
{
	qDebug() << "Error! " << s_text.toLatin1().constBegin();
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void				CmdTest::errorContin	( const QString & s_text )
{
	qDebug() << s_text.toLatin1().constBegin();
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void				CmdTest::error			( 
		const QString & s_file, int i_line, 
		const QString & s_line, const QString & s_text )
{
	qDebug() << s_file.toLatin1().constBegin() 
			 << "[" << i_line << "] Error! " 
			 << s_text.toLatin1().constBegin() << ":\n" 
			 << s_line.toLatin1().constBegin() << "\n";
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void				CmdTest::log			( LogTypes ty, const QString & s_text )
{
	if ( ( ty & uniq_->log_types_ ) != 0 )
	{
		qDebug() << s_text.toLatin1().constBegin();
	}
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void				CmdTest::successTest	( 
		Target * target, const QString & s_text )
{
	Q_ASSERT( uniq_ != NULL );
	Q_ASSERT( target != NULL );
	target->incSuccessTest();
	log( LOG_SUCCESS, s_text );
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void				CmdTest::failedTest	( 
		Target * target, const QString & s_text )
{
	Q_ASSERT( uniq_ != NULL );
	Q_ASSERT( target != NULL );
	target->incFailedTest();
	log( LOG_FAILURE, s_text );
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool				CmdTest::commandWhites	( const CmdEntry & cmd )
{
	Q_UNUSED( cmd );
	dbgtextl( "empty line" );
	return true;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool				CmdTest::commandComments( const CmdEntry & cmd )
{
	Q_UNUSED( cmd );
	dbgtext2l( "comment line: ", cmd.rex_.cap( 0 ) );
	return true;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool				CmdTest::commandTarget	( const CmdEntry & cmd )
{
	QString s_trm = cmd.rex_.cap(1).trimmed();
	Target * new_trg = getTarget( s_trm );
	if( new_trg == NULL )
	{
		return false;
	}
	return true;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool				CmdTest::commandCommand	( const CmdEntry & cmd )
{
	QString s_trm = cmd.rex_.cap(1).trimmed();
	if ( sendCommand( s_trm ) == false )
	{
		return false;
	}
	return true;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool				CmdTest::commandExpect	( const CmdEntry & cmd )
{
	QString s_trm = cmd.rex_.cap(1).trimmed();
	if ( expectOutput( s_trm ) == false )
	{
		return false;
	}
	return true;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool				CmdTest::commandInclude	( const CmdEntry & cmd )
{
	QString s_trm = cmd.rex_.cap(1).trimmed();
	int i_crt = uniq_->file_crt_;
	bool b = processFile( s_trm );
	uniq_->file_crt_ = i_crt;
	if ( b == false )
	{
		errorContin( QString( "    from: %1" ).arg( crtFile() ) );
		return false;
	}
	
	return true;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool				CmdTest::commandSwitch	( const CmdEntry & cmd )
{
	Q_ASSERT( uniq_ != NULL );
	QString s_trm = cmd.rex_.cap(1).trimmed();
	Target * ret = findTarget( s_trm );
	if ( ret != NULL )
	{
		error( QString( "Can't start process %1" ).arg( cmd.rex_.cap(0) ) );
		return false;
	}
	log( LOG_TARGETS, QString( "Switched to %1" ).arg( ret->name() ) );
	uniq_->t_crt_ = ret;
	return true;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool				CmdTest::commandTargetArgs	( const CmdEntry & cmd )
{
	Q_ASSERT( uniq_ != NULL );
	QString s_trm = cmd.rex_.cap(1).trimmed();
	QStringList s_args = cmd.rex_.cap(2).trimmed().split( "," );
	Target * ret;
	ret = new Target( s_trm );
	uniq_->targets_.append( ret );
	uniq_->t_crt_ = ret;
	return ret->start( s_args );
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool				CmdTest::commandExpectE		( const CmdEntry & cmd )
{
	QString s_trm = cmd.rex_.cap(1).trimmed();
	
	
	
	
	//	if ( expectOutput( s_trm ) == false )
	//	{
	//		return false;
	//	}
	return true;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool				CmdTest::commandExpectO		( const CmdEntry & cmd )
{
	QString s_trm = cmd.rex_.cap(1).trimmed();
	
	
	
	
	//	if ( expectOutput( s_trm ) == false )
	//	{
	//		return false;
	//	}
	return true;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool				CmdTest::commandEndTarget	( const CmdEntry & cmd )
{
	QString s_trm = cmd.rex_.cap(1).trimmed();
	
	Target * ret;
	if ( s_trm.isEmpty() == false )
	{
		ret = findTarget( s_trm );
		if ( ret == NULL )
		{
			error( QString( "Can't find target %1" ).arg( s_trm ) );
			return false;
		}
	}
	else
	{
		ret = uniq_->t_crt_;
		if ( ret == NULL )
		{
			error( QString( "No current target is set" ) );
			return false;
		}
	}
	ret->discardContent();
	
	if ( ret->state() == QProcess::NotRunning )
	{
		successTest( ret, 
					 QString( "Target %1 ended" )
					 .arg( ret->name() ) );
	}
	else
	{
		failedTest( ret, 
					QString( "Target %1 failed to end" )
					.arg( ret->name() ) );
	}
	
	return true;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool				CmdTest::commandExit		( const CmdEntry & cmd )
{
	QString s_trm = cmd.rex_.cap(1).trimmed();
	Target * ret;
	
	bool b = false;
	int exit_code = s_trm.toInt( &b );
	if ( !b )
	{
		error( QString( "EXIT CODE expects a numeric argument" ) );
		return false;
	}
	
	ret = uniq_->t_crt_;
	if ( ret == NULL )
	{
		error( QString( "No current target is set" ) );
		return false;
	}
	ret->discardContent();
	
	if ( ret->state() == QProcess::NotRunning )
	{
		if ( ret->exitCode() == exit_code )
		{
			successTest( ret, 
						 QString( "Target %1 ended with code %2" )
						 .arg( ret->name() ) 
						 .arg( exit_code ) 
						 );
		}
		else
		{
			failedTest( ret, 
						QString( "Target %1 ended with code %2; expected %3" )
						.arg( ret->name() )
						.arg( ret->exitCode() )
						.arg( exit_code )
						);
		}
	}
	else
	{
		failedTest( ret, 
					QString( "Target %1 failed to end" )
					.arg( ret->name() ) );
	}

	return true;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool				CmdTest::commandExitNot		( const CmdEntry & cmd )
{
	QString s_trm = cmd.rex_.cap(1).trimmed();
	Target * ret;
	
	bool b = false;
	int exit_code = s_trm.toInt( &b );
	if ( !b )
	{
		error( QString( "EXIT CODE expects a numeric argument" ) );
		return false;
	}
	
	ret = uniq_->t_crt_;
	if ( ret == NULL )
	{
		error( QString( "No current target is set" ) );
		return false;
	}
	ret->discardContent();
	
	if ( ret->state() == QProcess::NotRunning )
	{
		if ( ret->exitCode() != exit_code )
		{
			successTest( ret, 
						 QString( "Target %1 ended with code %2" )
						 .arg( ret->name() ) 
						 .arg( exit_code ) 
						 );
		}
		else
		{
			failedTest( ret, 
						QString( "Target %1 ended with code %2; expected not to" )
						.arg( ret->name() )
						.arg( ret->exitCode() )
						.arg( exit_code )
						);
		}
	}
	else
	{
		failedTest( ret, 
					QString( "Target %1 failed to end" )
					.arg( ret->name() ) );
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
