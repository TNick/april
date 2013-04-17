/* ========================================================================= */
/* ------------------------------------------------------------------------- */
/*!
  \file			amodworld.cc
  \date			Apr 2013
  \author		TNick
  
  \brief		Contains the implementation of AModWorld class
  
  
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

#include	"amodworld.h"
#include	<april/cmd/commandmap.h>
#include	<april/cmd/apriltokenizer.h>
#include	<april/logic/aoutput.h>
#include	<april/logic/world.h>
#include	<april/aprillibrary.h>
#include	<QObject>
#include	<QStringList>

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
/*  SUPPORT  --------------------------------------------------------------- */

/* ------------------------------------------------------------------------- */
static void		errorAlreadyStarted			( QString & s_err ) {
	s_err.append(
				QObject::tr( 
					"Error! The world is already started.\n\n"
					) );
}
static void		errorAlreadyStopped			( QString & s_err ) {
	s_err.append(
				QObject::tr( 
					"Error! The world is already stopped.\n\n"
					) );
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
static World *		getWorldFromArg				(	
		const QString & s_tk, const AaToken & tk, QString & s_err )
{
	World * w;
	if ( tk.isInteger() )
	{
		bool b;
		int i = s_tk.toInt( &b );
		if ( b )
		{
			if ( ( i >= 0 ) && ( i < AprilLibrary::worldsCount() ) )
			{
				return AprilLibrary::worldAt(i);
			}
		}
	}
	w = AprilLibrary::findWorld( s_tk );
	if ( w == NULL )
	{
		s_err.append(
					QObject::tr( 
						"Error! World <%1> was not found.\n" 
						).arg( s_tk ) );
	}
	return w;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
static void		closeW			( World * w, QString & s_err )
{
	
	Q_ASSERT( w != NULL );
	
	s_err.append( QObject::tr( "World <%1> was closed.\n").arg( w->name() ) );
	if ( w->isRunning() )
	{
		w->stop();
	}
	AprilLibrary::remWorld( w );
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
static void			saveW					(
		World * w, const QString & s_file, QString & s_err )
{
	if ( w->saveAsStg( s_file, s_err ) )
	{
		w->setAssociatedFile( s_file );
		s_err.append( QObject::tr( "World <%1> was saved.\n").arg( w->name() ) );
	}
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
static bool		createWorld						( 
		const QString & s_name, int energy, QString & s_err )
{
	Q_UNUSED( s_err );
	World * w = new World( s_name, energy );
	DEC_REF(w,w);
	AOutput::showInfo(
				QObject::tr( 
					"New world <%1> was created with %2 units of energy.\n"
					).arg( s_name ).arg( energy ) );
	return true;
}
/* ========================================================================= */

/*  SUPPORT  =============================================================== */
//
//
//
//
/*  CLASS    --------------------------------------------------------------- */


/* ------------------------------------------------------------------------- */
AModWorld::AModWorld	( CommandMap * cmd_map )
	: AprilModule(cmd_map)
{
	APRDBG_CDTOR;
	/* stub */
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
AModWorld::~AModWorld	( void )
{
	APRDBG_CDTOR;
	/* stub */
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void			AModWorld::insertCommands			( CommandMap * cm )
{
/// @cond internal

//! register a command from this package 
#define addOneCmd(c)	\
	cm->addCommand( QObject::tr( "w." stringify(c) ), AModWorld::c##World )
	
	addOneCmd(new);
	addOneCmd(open);
	addOneCmd(save);
	addOneCmd(close);
	addOneCmd(list);
	addOneCmd(start);
	addOneCmd(stop);
	addOneCmd(adv);
	addOneCmd(crt);
	
#undef addOneCmd
//! @endcond
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void			AModWorld::removeCommands			( CommandMap * cm )
{
/// @cond internal

//! unregister a command from this package @internal
#define remOneCmd(c)	\
	cm->remCommand( QObject::tr( "w." stringify(c) ), AModWorld::c##World );

	remOneCmd(new);
	remOneCmd(open);
	remOneCmd(save);
	remOneCmd(close);
	remOneCmd(list);
	remOneCmd(start);
	remOneCmd(stop);
	remOneCmd(adv);
	remOneCmd(crt);
	
#undef remOneCmd
//! @endcond
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
QString			AModWorld::name					( void )
{
	return QObject::tr( "World" );
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool			AModWorld::dOpenWorld				(
		const QString & s_file, QString & s_err )
{
	World * w = World::fromStg( s_file, s_err );
	if ( w != NULL )
	{
		s_err.append( QObject::tr( "World <%1> was opened.\n" ).arg( w->name()) );
		DEC_REF(w,w);
		return true;
	}
	return false;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool			AModWorld::newWorld				(
		const QString & s_cmd, const AaTkString & atks, QString & s_err )
{
	Q_ASSERT( atks.tk_.count() >= 1 );
	Q_ASSERT( s_cmd == "w.new" );
	Q_UNUSED( s_cmd );
	
	int arg_cnt = atks.tk_.count() - 1;
	QString arg1;
	int energy = -1;
	bool b;
	for ( ;; )
	{
		if ( arg_cnt == 0 )
		{ /* default to all arguments */
			arg1 = AprilLibrary::uniqueWorldName( QObject::tr( "World%1" ) );
			energy = 100000;
			return createWorld( arg1, energy, s_err );
		}
		else if ( arg_cnt == 1 )
		{ /* either help or name */
			arg1 = atks.getToken( 1 );
			if ( atks.isString( 1 ) && ( arg1 == QObject::tr( "help" ) ) )
				break;
			/* the name was provided */
			energy = 100000;
			return createWorld( arg1, energy, s_err );
		}
		else if ( arg_cnt == 2 )
		{ /* name and energy */
			arg1 = atks.getToken( 1 );
			for ( ;; )	{
				if ( atks.isInteger( 2 ) )
				{
					energy = atks.getToken( 2 ).toInt( &b, 10 );
					if ( ( b == false ) || ( energy <= 0 ) )
						break;
				}
				else if ( atks.isHexInteger( 2 ) )
				{
					energy = atks.getToken( 2 ).toInt( &b, 16 );
					if ( ( b == false ) || ( energy <= 0 ) )
						break;
				}
				else
				{
					break;
				}
				return createWorld( arg1, energy, s_err );
			}
			errorEnergyInteger( s_err );
			break;
		}
		else
		{
			errorNumberOfArguments( s_err );
			break;
		}
	} /* for ( ;; ) */
	
	/* print the usage */
	s_err.append( getCLUsage( s_cmd ) );
	return false;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool			AModWorld::openWorld				(
		const QString & s_cmd, const AaTkString & atks, QString & s_err )
{
	Q_ASSERT( s_cmd == "w.open" );
	Q_UNUSED( s_cmd );
	
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
		dOpenWorld( arg1, s_err );
		return false;
	}
	
	/* print the usage */
	s_err.append( getCLUsage( s_cmd ) );
	return false;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool			AModWorld::saveWorld				(
		const QString & s_cmd, const AaTkString & atks, QString & s_err )
{
	Q_ASSERT( s_cmd == "w.save" );
	Q_UNUSED( s_cmd );
	
	int arg_cnt = atks.tk_.count() - 1;
	QString arg1;
	QString arg2;
	World * w;
	
	for ( ;; )
	{
		if ( arg_cnt == 1 )
		{ /* only name/index */
			arg1 = atks.getToken( 1 );
			if ( arg1 == QObject::tr( "help" ) )
				break;
			w = getWorldFromArg( arg1, atks.tk_.at( 1 ), s_err );
			if ( w == NULL )
				break;
			arg2 = w->associatedFile();
			if ( arg2.isEmpty() )
			{
				errorNoAssocFile( w, s_err );
				break;
			}
			saveW( w, arg2, s_err );
			return false;
		}
		else if ( arg_cnt == 2 )
		{ /* name/index and file */
			arg1 = atks.getToken( 1 );
			arg2 = atks.getToken( 2 );
			w = getWorldFromArg( arg1, atks.tk_.at( 1 ), s_err );
			if ( w == NULL )
				break;
			
			saveW( w, arg2, s_err );
			return false;
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
bool			AModWorld::closeWorld				(
		const QString & s_cmd, const AaTkString & atks, QString & s_err )
{
	Q_ASSERT( s_cmd == "w.close" );
	Q_UNUSED( s_cmd );
	
	int arg_cnt = atks.tk_.count() - 1;
	
	for ( ;; )
	{
		if ( arg_cnt != 1 )
		{
			errorOneArgumentExpected( s_err );
			break;
		}
		QString arg1 = atks.getToken( 1 );
		if ( arg1 == QObject::tr( "help" ) )
			break;
		World * w = getWorldFromArg( arg1, atks.tk_.at( 1 ), s_err );
		if ( w == NULL )
			break;
		closeW( w, s_err );
		return false;
	}
	
	/* print the usage */
	s_err.append( getCLUsage( s_cmd ) );
	return false;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool			AModWorld::listWorld				(
		const QString & s_cmd, const AaTkString & atks, QString & s_err )
{
	Q_ASSERT( s_cmd == "w.list" );
	Q_UNUSED( s_cmd );
	
	int arg_cnt = atks.tk_.count() - 1;
	QString arg1;
	for ( ;; )
	{
		if ( arg_cnt == 0 )
		{
			World * iter = AprilLibrary::firstWorld();
			if ( iter == NULL )
			{
				s_err.append( QObject::tr( 
								  "No worlds loaded.\n"
								  ) );
				return false;
			}
			else
			{
				QList<QStringList>	datao;
				QStringList			sl;
				
				sl.append( QObject::tr( "Name" ) );
				sl.append( QObject::tr( "Bounded" ) );
				sl.append( QObject::tr( "Free" ) );
				sl.append( QObject::tr( "Time" ) );
				sl.append( QObject::tr( "Status" ) );
				datao.append( sl ); sl.clear();
				
				while ( iter != NULL )
				{
					sl.append( iter->name() );
					sl.append( QString::number( iter->energyBounded() ) );
					sl.append( QString::number( iter->energyFree() ) );
					sl.append( QString::number( iter->currentTime() ) );
					sl.append( iter->isRunning() ? "Running" : "Stopped" );
					datao.append( sl );  sl.clear();
					
					iter = nextWorld_(iter);
				}
				AOutput::showTable( datao, true );
				return true;
			}
		}
		else if ( arg_cnt == 1 )
		{
			arg1 = atks.getToken( 1 );
			if ( arg1 == QObject::tr( "help" ) )
				break;
			errorUnknownOption( s_err, arg1 );
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
bool			AModWorld::startWorld				(
		const QString & s_cmd, const AaTkString & atks, QString & s_err )
{
	Q_ASSERT( s_cmd == "w.start" );
	Q_UNUSED( s_cmd );
	
	int arg_cnt = atks.tk_.count() - 1;
	for ( ;; )
	{
		if ( arg_cnt != 1 )
		{
			errorOneArgumentExpected( s_err );
			break;
		}
		QString arg1 = atks.getToken( 1 );
		if ( arg1 == QObject::tr( "help" ) )
			break;
		World * w = getWorldFromArg( arg1, atks.tk_.at( 1 ), s_err );
		if ( w == NULL )
			break;
		if ( w->isRunning() )
		{
			errorAlreadyStarted( s_err );
			return false;
		}
		w->start();
		s_err.append( 
					QObject::tr( 
						"World <%1> was started.\n" 
						).arg( w->name() ) );
		return false;
	}
	/* print the usage */
	s_err.append( getCLUsage( s_cmd ) );
	return false;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool			AModWorld::stopWorld				(
		const QString & s_cmd, const AaTkString & atks, QString & s_err )
{
	Q_ASSERT( s_cmd == "w.stop" );
	Q_UNUSED( s_cmd );
	
	int arg_cnt = atks.tk_.count() - 1;
	for ( ;; )
	{
		if ( arg_cnt != 1 )
		{
			errorOneArgumentExpected( s_err );
			break;
		}
		QString arg1 = atks.getToken( 1 );
		if ( arg1 == QObject::tr( "help" ) )
			break;
		World * w = getWorldFromArg( arg1, atks.tk_.at( 1 ), s_err );
		if ( w == NULL )
			break;
		if ( w->isRunning() == false )
		{
			errorAlreadyStopped( s_err );
			return false;
		}
		w->stop();
		s_err.append( 
					QObject::tr( 
						"World <%1> was stopped.\n" 
						).arg( w->name() ) );
		return false;
	}
	/* print the usage */
	s_err.append( getCLUsage( s_cmd ) );
	return false;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool			AModWorld::advWorld				(
		const QString & s_cmd, const AaTkString & atks, QString & s_err )
{
	Q_ASSERT( s_cmd == "w.adv" );
	Q_UNUSED( s_cmd );
	
	int arg_cnt = atks.tk_.count() - 1;
	for ( ;; )
	{
		if ( ( arg_cnt != 1 ) && ( arg_cnt != 2) )
		{
			errorOneArgumentExpected( s_err );
			break;
		}
		QString arg1 = atks.getToken( 1 );
		QString arg2;
		if ( arg1 == QObject::tr( "help" ) )
			break;
		World * w = getWorldFromArg( arg1, atks.tk_.at( 1 ), s_err );
		if ( w == NULL )
			break;
		int i = 1;
		if ( arg_cnt == 2 )
		{
			i = -1;
			const AaToken & tk2 = atks.tk_.at( 2 );
			arg2 = atks.getToken( tk2 );
			if ( tk2.isInteger() )
			{
				bool b;
				i = arg2.toInt( &b );
				if ( b == false || i <= 0 )
				{
					i = -1;
				}
			}
		}
		if ( i == -1 )
		{
			errorIntegerExpected( s_err, arg2 );
			break;
		}
		if ( w->isRunning() == false )
		{
			w->start();
			s_err.append( 
						QObject::tr( 
							"World <%1> was started.\n" 
							).arg( w->name() ) );
		}
		while ( i > 0 )
		{
			w->advance();
			i--;
		}
		s_err.append( 
					QObject::tr( 
						"Time in world <%1> is now %2.\n" 
						).arg( w->name() ).arg( w->currentTime() ) );
		return false;
	}
	/* print the usage */
	s_err.append( getCLUsage( s_cmd ) );
	return false;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool			AModWorld::crtWorld				(
		const QString & s_cmd, const AaTkString & atks, QString & s_err )
{
	
	Q_ASSERT( atks.tk_.count() >= 1 );
	Q_ASSERT( s_cmd == "w.crt" );
	int arg_cnt = atks.tk_.count() - 1;
	
	for ( ;; )
	{
		if ( arg_cnt == 0 )
		{
			World * w = AprilLibrary::crtWorld();
			if ( w == NULL )
			{
				s_err.append( 
							QObject::tr( 
								"(no current world)\n" 
								) );
			}
			else
			{
				s_err.append( 
							QObject::tr( 
								"<%1>\n" 
								).arg( w->name() ) );
			}
			return false;
		}
		else if ( arg_cnt != 1 )
		{
			errorOneArgumentExpected ( s_err );
			break;
		}
		QString arg1 = atks.getToken( 1 );
		if ( arg1 == QObject::tr( "help" ) )
			break;
	
		World * w = getWorldFromArg( arg1, atks.tk_.at( 1 ), s_err );
		if ( w == NULL )
			break;
		AprilLibrary::setCrtWorld( w );
		s_err.append( 
					QObject::tr( 
						"World <%1> was made current.\n" 
						).arg( w->name() ) );
		return false;
	}
	
	/* print the usage */
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
