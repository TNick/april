/* ========================================================================= */
/* ------------------------------------------------------------------------- */
/*!
  \file			aaplugins.cc
  \date			Apr 2013
  \author		TNick

  \brief		Contains the implementation of AaPlugIns class


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

#include	"aaplugins.h"
#include	<april/cmd/commandmap.h>
#include	<april/cmd/aatokenizer.h>
#include	<april/logic/aaoutput.h>
#include	<april/logic/world.h>
#include	<april/plugins/aprilplugininterf.h>
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
static AprilPluginLoader *		getPlginFromArg				(	
		const QString & s_tk, const AaToken & tk, QString & s_err )
{
	AprilPluginLoader * w;
	if ( tk.isInteger() )
	{
		bool b;
		int i = s_tk.toInt( &b );
		if ( b )
		{
			if ( ( i >= 0 ) && ( i < AprilLibrary::pluginsCount() ) )
			{
				return AprilLibrary::pluginAt(i);
			}
		}
	}
	w = AprilLibrary::findPlugInLoaderRel( s_tk );
	if ( w == NULL )
	{
		s_err.append(
					QObject::tr( 
						"Error! Plug-in <%1> was not found.\n" 
						).arg( s_tk ) );
	}
	return w;
}
/* ========================================================================= */

/*  SUPPORT  =============================================================== */
//
//
//
//
/*  CLASS    --------------------------------------------------------------- */

/* ------------------------------------------------------------------------- */
AaPlugIns::AaPlugIns	( CommandMap * cmd_map )
	: AaModule(cmd_map)
{
	APRDBG_CDTOR;
	/* stub */
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
AaPlugIns::~AaPlugIns	( void )
{
	APRDBG_CDTOR;
	/* stub */
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void			AaPlugIns::insertCommands			( CommandMap * cm )
{
/// @cond internal

//! register a command from this package 
#define addOneCmd(c)	\
	cm->addCommand( QObject::tr( "p." stringify(c) ), AaPlugIns::c##PlugIn )
	
	addOneCmd(load);
	addOneCmd(unload);
	addOneCmd(list);
	
#undef addOneCmd
//! @endcond
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void			AaPlugIns::removeCommands			( CommandMap * cm )
{
/// @cond internal

//! unregister a command from this package @internal
#define remOneCmd(c)	\
	cm->remCommand( QObject::tr( "p." stringify(c) ), AaPlugIns::c##PlugIn );

	remOneCmd(load);
	remOneCmd(unload);
	remOneCmd(list);
	
#undef remOneCmd
//! @endcond
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
QString			AaPlugIns::name					( void )
{
	return QObject::tr( "Plug-Ins" );
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool			AaPlugIns::loadPlugIn			(
		const QString & s_cmd, const AaTkString & atks, QString & s_err )
{
	Q_ASSERT( atks.tk_.count() >= 1 );
	Q_ASSERT( s_cmd == "p.load" );
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
		
		AprilPluginInterf * found = AprilLibrary::findPlugInRel( arg1 );
		if  ( found != NULL )
		{
			s_err.append( QObject::tr( "Plug-in <%1> is already loaded.\n" ).arg( arg1 ) );
			return false;
		}
		found = AprilLibrary::loadPlugIn( arg1 );
		if  ( found == NULL )
		{
			s_err.append( QObject::tr( "Failed to load plug-in <%1>.\n" ).arg( arg1 ) );
			return false;
		}
		else
		{
			s_err.append( QObject::tr( "Plug-in <%1> was loaded.\n" ).arg( arg1 ) );
		}		
		return false;
	}
	
	/* print the usage */
	s_err.append( QObject::tr( 
					  "Usage:\n"
					  "    p.load <file-name>     "
					  "loads specified plug-in file\n"
					  "    p.load help            "
					  "prints usage instructions\n"
					  "\n"
					  ) );
	return false;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool			AaPlugIns::unloadPlugIn			(
		const QString & s_cmd, const AaTkString & atks, QString & s_err )
{
	Q_ASSERT( atks.tk_.count() >= 1 );
	Q_ASSERT( s_cmd == "p.unload" );
	
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
		AprilPluginLoader * pin = getPlginFromArg( arg1, atks.tk_.at( 1 ), s_err );
		if ( pin == NULL )
			break;
		arg1 = pin->name();
		AprilLibrary::unloadPlugIn( pin );
		s_err.append( QObject::tr( "Plug-in <%1> was unloaded.\n").arg( arg1 ) );
		return false;
	}
	
	/* print the usage */
	s_err.append( QObject::tr( 
					  "Usage:\n"
					  "    p.unload <index>       "
					  "unloads the plug-in at specified index\n"
					  "    p.unload <name>        "
					  "unloads the plug-in having that name\n"
					  "    p.unload help          "
					  "prints usage instructions\n"
					  "\n"
					  ) );
	return false;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool			AaPlugIns::listPlugIn			(
		const QString & s_cmd, const AaTkString & atks, QString & s_err )
{
	Q_ASSERT( atks.tk_.count() >= 1 );
	Q_ASSERT( s_cmd == "p.list" );
	int arg_cnt = atks.tk_.count() - 1;
	QString arg1;
	for ( ;; )
	{
		if ( arg_cnt == 0 )
		{
			AprilPluginLoader * iter = AprilLibrary::firstPlugin();
			if ( iter == NULL )
			{
				s_err.append( QObject::tr( 
								  "No plug-ins loaded.\n"
								  ) );
				return false;
			}
			else
			{
				QList<QStringList>	datao;
				QStringList			sl;
				
				sl.append( QObject::tr( "Name" ) );
				sl.append( QObject::tr( "Path" ) );
				datao.append( sl ); sl.clear();
				
				while ( iter != NULL )
				{
					sl.append( iter->name() );
					sl.append( iter->fileName() );
					datao.append( sl );  sl.clear();
					
					iter = nextPlugin_(iter);
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
					  "    p.list                 "
					  "lists the plug-ins and their paths\n"
					  "    p.list help            "
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
