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

/* ------------------------------------------------------------------------- */
bool			AaWorld::newWorld				(
		const QString & s_cmd, const AaTkString & atks, QString & s_err )
{
	Q_ASSERT( atks.tk_.count() >= 1 );
	Q_ASSERT( s_cmd == "w.new" );
	Q_UNUSED( s_cmd );
	Q_UNUSED( atks );
	Q_UNUSED( s_err );
	
	int arg_cnt = atks.tk_.count() - 1;
	QString arg_1;
	int energy = -1;
	bool b;
	for ( ;; )
	{
		if ( arg_cnt == 0 )
		{ /* default to all arguments */
			arg_1 = AprilLibrary::uniqueWorldName( QObject::tr( "World%1" ) );
			energy = 100000;
			return createWorld( arg_1, energy, s_err );
		}
		else if ( arg_cnt == 1 )
		{ /* either help or name */
			arg_1 = atks.getToken( 1 );
			if ( atks.isString( 1 ) && ( arg_1 == "help" ) )
				break;
			/* the name was provided */
			energy = 100000;
			return createWorld( arg_1, energy, s_err );
		}
		else if ( arg_cnt == 2 )
		{ /* name and energy */
			arg_1 = atks.getToken( 1 );
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
				return createWorld( arg_1, energy, s_err );
			}
			s_err.append( QObject::tr( "Error! Energy must be a positive integer.\n\n" ) );
			break;
		}
		else
		{
			s_err.append( QObject::tr( "Error! Invalid number of arguments.\n\n" ) );
			break;
		}
	} /* for ( ;; ) */
	
	/* print the usage */
	s_err.append( QObject::tr( 
					  "Usage:\n"
					  "    w.new                  creates a new world with default values\n"
					  "    w.new [name] [energy]  creates a world with given name and energy\n"
					  "    w.new help             prints usage instructions\n"
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
	
	return true;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool			AaWorld::saveWorld				(
		const QString & s_cmd, const AaTkString & atks, QString & s_err )
{
	Q_ASSERT( s_cmd == "w.save" );
	Q_UNUSED( s_cmd );
	Q_UNUSED( atks );
	Q_UNUSED( s_err );
	
	return true;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool			AaWorld::closeWorld				(
		const QString & s_cmd, const AaTkString & atks, QString & s_err )
{
	Q_ASSERT( s_cmd == "w.close" );
	Q_UNUSED( s_cmd );
	Q_UNUSED( atks );
	Q_UNUSED( s_err );
	
	return true;
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
