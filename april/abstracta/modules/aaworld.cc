/* ========================================================================= */
/* ------------------------------------------------------------------------- */
/*!
  \file			aaworld.cc
  \date			Apr 2013
  \author		TNick
  
  \brief		Contains the implementation of AaWorld class
  
  
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

#include	"aaworld.h"
#include	<april/abstracta/abstractapril.h>
#include	<april/abstracta/commandmap.h>
#include	<april/abstracta/aatokenizer.h>
#include	<april/abstracta/aaoutput.h>
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
static void		errorNumberOfArguments		( QString & s_err ) {
	s_err.append( 
				QObject::tr( 
					"Error! Invalid number of arguments.\n\n" 
					) );
}
static void		errorOneArgumentExpected	( QString & s_err ) {
	s_err.append(
				QObject::tr( 
					"Error! One argument expected.\n\n"
					) );
}
static void		errorNoAssocFile			( World * w, QString & s_err ) {
	s_err.append(
				QObject::tr( 
					"Error! World <%1> has no associated file.\n\n" 
					).arg( w->name() ) );
}
static void		errorEnergyInteger			( QString & s_err ) {
	s_err.append(
				QObject::tr( 
					"Error! Energy must be a positive integer.\n\n" 
					) );
}
static void		errorUnknownOprion			( QString & s_err, const QString & s_tk ) {
	s_err.append(
				QObject::tr( 
					"Error! Unknown option: %1.\n\n"
					).arg( s_tk ) );
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
	AaOutput::showInfo(
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
AaWorld::AaWorld	( void )
	: AaModule()
{
	APRDBG_CDTOR;
	/* stub */
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
AaWorld::~AaWorld	( void )
{
	APRDBG_CDTOR;
	/* stub */
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void			AaWorld::insertCommands			( void )
{
	AbstractApril::addCommand( QObject::tr( "w.new" ), AaWorld::newWorld );
	AbstractApril::addCommand( QObject::tr( "w.open" ), AaWorld::openWorld );
	AbstractApril::addCommand( QObject::tr( "w.save" ), AaWorld::saveWorld );
	AbstractApril::addCommand( QObject::tr( "w.close" ), AaWorld::closeWorld );
	AbstractApril::addCommand( QObject::tr( "w.list" ), AaWorld::listWorlds );
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void			AaWorld::removeCommands			( void )
{
	AbstractApril::remCommand( QObject::tr( "w.new" ), AaWorld::newWorld );
	AbstractApril::remCommand( QObject::tr( "w.open" ), AaWorld::openWorld );
	AbstractApril::remCommand( QObject::tr( "w.save" ), AaWorld::saveWorld );
	AbstractApril::remCommand( QObject::tr( "w.close" ), AaWorld::closeWorld );
	AbstractApril::remCommand( QObject::tr( "w.list" ), AaWorld::listWorlds );
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
QString			AaWorld::name					( void )
{
	return QObject::tr( "World" );
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool			AaWorld::newWorld				(
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
	s_err.append( QObject::tr( 
					  "Usage:\n"
					  "    w.new                  "
					  "creates a new world with default values\n"
					  "    w.new [name] [energy]  "
					  "creates a world with given name and energy\n"
					  "    w.new help             "
					  "prints usage instructions\n"
					  "\n"
					  "Options:\n"
					  "  name     the name of the world; this will identify the\n"
					  "           world in future dialogs; when no name is given\n"
					  "           an unique one is generated;\n"
					  "  energy   the ammount of energy in the world; this must be\n"
					  "           a positive integer. In order to set the energy\n"
					  "           you MUST set a name. By default the energy is set\n"
					  "           to 100000 units."
					  "\n"
					  ) );
	return false;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool			AaWorld::openWorld				(
		const QString & s_cmd, const AaTkString & atks, QString & s_err )
{
	Q_ASSERT( s_cmd == "w.open" );
	Q_UNUSED( s_cmd );
	Q_UNUSED( atks );
	Q_UNUSED( s_err );
	
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
		World * w = World::fromStg( arg1, s_err );
		if ( w != NULL )
		{
			s_err.append( QObject::tr( "World <%1> was opened.\n" ).arg( w->name()) );
			DEC_REF(w,w);
		}		
		return false;
	}
	
	/* print the usage */
	s_err.append( QObject::tr( 
					  "Usage:\n"
					  "    w.open <file-name>     "
					  "opens specified file and loads the world inside\n"
					  "    w.open help            "
					  "prints usage instructions\n"
					  "\n"
					  ) );
	return false;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool			AaWorld::saveWorld				(
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
	s_err.append( QObject::tr( 
					  "Usage:\n"
					  "    w.save [name] [file]   "
					  "saves specified world to a file\n"
					  "    w.save [index] [file]  "
					  "saves specified world to a file\n"
					  "    w.save help            "
					  "prints usage instructions\n"
					  "\n"
					  "Options:\n"
					  "  name     the name of the world;\n"
					  "  file     where to save; if not specified the \n"
					  "           file asociated with the world is used"
					  "\n"
					  "If the opperation is succefull the internl association\n"
					  "is also updated.\n"
					  "\n"
					  ) );
	return false;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool			AaWorld::closeWorld				(
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
	s_err.append( QObject::tr( 
					  "Usage:\n"
					  "    w.close <index>        "
					  "close the world at specified index\n"
					  "    w.close <name>         "
					  "close the world having that name\n"
					  "    w.close help           "
					  "prints usage instructions\n"
					  "\n"
					  ) );
	return false;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool			AaWorld::listWorlds				(
		const QString & s_cmd, const AaTkString & atks, QString & s_err )
{
	Q_ASSERT( s_cmd == "w.list" );
	Q_UNUSED( s_cmd );
	Q_UNUSED( atks );
	Q_UNUSED( s_err );
	
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
				AaOutput::showTable( datao, true );
				return true;
			}
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
	s_err.append( QObject::tr( 
					  "Usage:\n"
					  "    w.list                 "
					  "lists the worlds and basic properties\n"
					  "    w.list help            "
					  "prints usage instructions\n"
					  "\n"
					  ) );
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
