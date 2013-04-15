/* ========================================================================= */
/* ------------------------------------------------------------------------- */
/*!
  \file			aprilmodule.cc
  \date			Apr 2013
  \author		TNick
  
  \brief		Contains the implementation of AprilModule class
  
  
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

#include	"aprilmodule.h"
#include	<april/logic/world.h>
#include	<april/cmd/apriltokenizer.h>
#include	<QObject>
#include	<QSettings>

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
AprilModule::AprilModule	( CommandMap * cmd_map )
	: libbbb::RefCnt(), MemTrack(),
	cmd_map_( cmd_map )
{
	APRDBG_CDTOR;
	/* stub */
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
AprilModule::~AprilModule	( void )
{
	APRDBG_CDTOR;
	/* stub */
}
/* ========================================================================= */

void		AprilModule::errorNumberOfArguments		( QString & s_err )
{
	s_err.append( 
				QObject::tr( 
					"Error! Invalid number of arguments.\n\n" 
					) );
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void		AprilModule::errorOneArgumentExpected		( QString & s_err )
{
	s_err.append(
				QObject::tr( 
					"Error! One argument expected.\n\n"
					) );
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void		AprilModule::errorNoAssocFile				( World * w, QString & s_err )
{
	s_err.append(
				QObject::tr( 
					"Error! World <%1> has no associated file.\n\n" 
					).arg( w->name() ) );
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void		AprilModule::errorEnergyInteger			( QString & s_err )
{
	s_err.append(
				QObject::tr( 
					"Error! Energy must be a positive integer.\n\n" 
					) );
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void		AprilModule::errorUnknownOprion			( 
		QString & s_err, const QString & s_tk )
{
	s_err.append(
				QObject::tr( 
					"Error! Unknown option: %1.\n\n"
					).arg( s_tk ) );
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void		AprilModule::errorIntegerExpected		( 
		QString & s_err, const QString & s_tk )
{
	s_err.append(
				QObject::tr( 
					"Error! An integer was expected instead of %1.\n\n"
					).arg( s_tk) );
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void		AprilModule::errorNoCurrentWorld		( 
		QString & s_err )
{
	s_err.append(
				QObject::tr( 
					"Error! No current world.\n\n"
					) );
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool		AprilModule::setUsage					( 
	const QString & s_name, 
	const QStringList & usage, const QStringList & usage_descr, 
	const QStringList & opts, const QList<QStringList> & opts_descr, 
	const QStringList & obs )
{
	Q_ASSERT( usage.count() == usage_descr.count() );
	Q_ASSERT( opts.count() == opts_descr.count() );
	
	/** @todo file from app settings */
	QSettings	stg( "help.dat", QSettings::IniFormat );
	if ( stg.isWritable() == false )
		return false;
	
	stg.beginGroup( s_name );
	stg.beginWriteArray( "Usage", usage.count() );
	int usg_max = usage.count();
	for ( int i = 0; i < usg_max; i++ )
	{
		stg.setArrayIndex( i );
		stg.setValue( "cmd", usage.at( i ) );
		stg.setValue( "descr", usage_descr.at( i ) );
	}
	stg.endArray(); // Usage
	
	stg.beginWriteArray( "Options", opts.count() );
	int opt_max = opts.count();
	for ( int i = 0; i < opt_max; i++ )
	{
		stg.setArrayIndex( i );
		stg.setValue( "opt", usage.at( i ) );
		stg.setValue( "descr", usage_descr.at( i ) );
	}
	stg.endArray(); // Options
	
	stg.setValue( "Observations", obs );
	
	stg.endGroup(); // command name
	return true;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
QString		AprilModule::getCLUsage				( const QString & s_name )
{
	QString s_usage;
	QString s_usage_descr;
	QString s_opt;
	QStringList s_opt_descr;
	QString s_ret;
	QStringList s_obs;
	
	/** @todo file from app settings */
	QSettings	stg( "help.dat", QSettings::IniFormat );
	stg.beginGroup( s_name );
	
	int usg_max = stg.beginReadArray( "Usage" );
	if ( usg_max == 0 )
		return QString();
	s_ret = QObject::tr( "Usage:\n" );
	for ( int i = 0; i < usg_max; i++ )
	{
		stg.setArrayIndex( i );
		s_usage = stg.value( "cmd" ).toString();
		s_usage_descr = stg.value( "descr" ).toString();
		
		s_ret.append( QChar( ' ' ) );
		s_ret.append( s_usage );
		s_ret.append( QString( qMax( 1, 20 - s_usage.length() ), QChar( ' ' ) ) );
		s_ret.append( s_usage_descr );
		s_ret.append( QChar( '\n' ) );
	}
	stg.endArray(); // Usage
	
	int opt_max = stg.beginReadArray( "Options" );
	if ( opt_max > 0 )
	{
		s_ret.append( QObject::tr( "\nOptions:\n" ) );
		for ( int i = 0; i < opt_max; i++ )
		{
			stg.setArrayIndex( i );
			s_opt = stg.value( "opt" ).toString();
			s_opt_descr = stg.value( "descr" ).toStringList();
			
			s_ret.append( "  " );
			s_ret.append( s_opt );
			s_ret.append( QString( qMax( 1, 10 - s_usage.length() ), QChar( ' ' ) ) );
			if ( s_opt_descr.count() == 0 )
				continue;
			s_ret.append( s_opt_descr.at( 0 ) );
			s_ret.append( QChar( '\n' ) );
			for ( int j = 1; i < s_opt_descr.count(); j++ )
			{
				s_ret.append( QString( 11, QChar( ' ' ) ) );
				s_ret.append( s_opt_descr.at( j ) );
				s_ret.append( QChar( '\n' ) );
			}
		}
	}
	stg.endArray(); // Options
	
	s_obs = stg.value( "Observations" ).toStringList();
	if ( s_obs.count() > 0 )
	{
		s_ret.append( QObject::tr( "\nObservations:\n" ) );
		for ( int j = 1; j < s_obs.count(); j++ )
		{
			s_ret.append( QChar( ' ' ) );
			s_ret.append( s_opt_descr.at( j ) );
			s_ret.append( QChar( '\n' ) );
		}
	}
	
	stg.endGroup(); // command name
	
	return s_ret;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool		AprilModule::funcArg0					(
		const QString & s_cmd, const AaTkString & atks, 
		QString & s_err, AprilModule::arg0Func kb )
{
	Q_ASSERT( atks.tk_.count() >= 1 );
	Q_ASSERT( kb != NULL );
	int arg_cnt = atks.tk_.count() - 1;
	QString arg1;
	for ( ;; )
	{
		if ( arg_cnt == 0 )
		{
			s_err.append( kb() );
			return false;
		}
		else if ( arg_cnt == 1 )
		{
			arg1 = atks.getToken( 1 );
			if ( arg1 == QObject::tr( "help" ) )
				break;
			errorUnknownOprion( s_err, arg1 );
			break;
		}
		else
		{
			errorNumberOfArguments( s_err );
			break;
		}
	}
	/* print the usage */
	s_err.append( getCLUsage( s_cmd ) );
	return false;	
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool		AprilModule::funcArg1					(
		const QString & s_cmd, const AaTkString & atks, 
		QString & s_err, AprilModule::arg1Func kb )
{
	Q_ASSERT( atks.tk_.count() >= 1 );
	Q_ASSERT( kb != NULL );
	int arg_cnt = atks.tk_.count() - 1;
	
	for ( ;; )
	{
		if ( arg_cnt != 1 )
		{
			errorOneArgumentExpected ( s_err );
			break;
		}
		QString arg1 = atks.getToken( 1 );
		if ( arg1 == QObject::tr( "help" ) )
			break;
		s_err.append( kb( arg1, atks.tk_.at( 1 ) ) );
		return false;
	}
	s_err.append( getCLUsage( s_cmd ) );
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
