/* ========================================================================= */
/* ------------------------------------------------------------------------- */
/*!
  \file			abstractapril.cc
  \date			Apr 2013
  \author		TNick
  
  \brief		Contains the implementation of AbstractApril class
  
  
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

#include	"abstractapril.h"
#include	<iostream>

#include	<april/cmd/aamodule.h>
#include	<april/cmd/aatokenizer.h>
#include	<april/cmd/modules/aaapril.h>
#include	<april/cmd/modules/aaworld.h>
#include	<april/cmd/modules/aaplugins.h>
#include	<april/cmd/modules/aadna.h>
#include	<april/logic/aaoutput.h>

#include	<QFile>

/*  INCLUDES    ============================================================ */
//
//
//
//
/*  DEFINITIONS    --------------------------------------------------------- */

using namespace april;
using namespace std;

/*  DEFINITIONS    ========================================================= */
//
//
//
//
/*  DATA    ---------------------------------------------------------------- */

AbstractApril *		AbstractApril::uniq_ = NULL;

/*  DATA    ================================================================ */
//
//
//
//
/*  CLASS    --------------------------------------------------------------- */

/* ------------------------------------------------------------------------- */
AbstractApril::AbstractApril	( void )
	: MemTrack(),
	  cmd_map(),
	  exit_code_(0)
{
	APRDBG_CDTOR;
	AaOutput::init();
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
AbstractApril::~AbstractApril	( void )
{
	APRDBG_CDTOR;
	AaOutput::end();
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void			AbstractApril::init					( void )
{
	/* load build-in modules */
	
	AaApril * module_april = new AaApril( &cmd_map );
	addModule( module_april );
	REMOVE_CONSTRUCTOR_REF(module_april);
	
	AaWorld * module_w = new AaWorld( &cmd_map );
	addModule( module_w );
	REMOVE_CONSTRUCTOR_REF(module_w);
	
	AaPlugIns * module_p = new AaPlugIns( &cmd_map );
	addModule( module_p );
	REMOVE_CONSTRUCTOR_REF(module_p);
	
	AaDNA * module_dna = new AaDNA( &cmd_map );
	addModule( module_dna );
	REMOVE_CONSTRUCTOR_REF(module_dna);
	
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
int				AbstractApril::executeCommands		( const QString & cmds )
{
	/* create the one and only instance */
	uniq_ = new AbstractApril();
	uniq_->init();
	
	QStringList	cmd_list = cmds.split( "&&",QString::SkipEmptyParts );
	foreach( QString iter, cmd_list )
	{
		uniq_->cmd_map.execute( iter );
		if ( uniq_->cmd_map.shouldExit() )
			break;
	}
	
	int i_ret = uniq_->exit_code_;
	delete uniq_;
	uniq_ = NULL;
	return i_ret;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
int				AbstractApril::executeFile			( const QString & cmds )
{
	/* create the one and only instance */
	uniq_ = new AbstractApril();
	uniq_->init();
	
	QFile	f( cmds );
	if ( f.open( QIODevice::ReadOnly ) )
	{
		QString	s( f.readAll() );
		QStringList sl = s.split( QChar( '\n' ), QString::SkipEmptyParts );
		foreach( QString iter, sl )
		{
			iter = iter.trimmed();
			if ( iter.startsWith( QChar( '#' ) ) == false )
			{
				uniq_->cmd_map.execute( iter );
				if ( uniq_->cmd_map.shouldExit() )
					break;
			}
		}
	}
	else
	{
		AaOutput::showError( 
					QObject::tr( "Failed to execute file" ), 
					f.errorString() );
		uniq_->exit_code_ = 1;
	}
	
	int i_ret = uniq_->exit_code_;
	delete uniq_;
	uniq_ = NULL;
	return i_ret;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
int				AbstractApril::runMainLoop			( 
		const QStringList & sl_init_files )
{
	/* create the one and only instance */
	uniq_ = new AbstractApril();
	uniq_->init();
	
	/* loop-open the worlds in command line arguments */
	QString s_err;
	foreach( QString iter, sl_init_files )
	{
		AaWorld::dOpenWorld( iter, s_err );
		AaOutput::showInfo( s_err );
	}
	
	/* prepare the prompt */
	std::string buffer;
	for ( ;; )
	{
		AaOutput::showPrompt();
		getline (cin, buffer);
		uniq_->cmd_map.execute( QString::fromStdString( buffer ) );
		if ( uniq_->cmd_map.shouldExit() )
			break;
	}
	
	int i_ret = uniq_->exit_code_;
	delete uniq_;
	uniq_ = NULL;
	return i_ret;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool			AbstractApril::addModule			( AaModule * m )
{
	return uniq_->cmd_map.addModule( m );
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool			AbstractApril::remModule			( AaModule * m )
{
	return uniq_->cmd_map.remModule( m );
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
QStringList		AbstractApril::commands				( void )
{
	return uniq_->cmd_map.commands();
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
QStringList		AbstractApril::modules				( void )
{
	return uniq_->cmd_map.modules();
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool			AbstractApril::addCommand			(
		const QString & s_cmd, cmdCallBack kb )
{ 
	return uniq_->cmd_map.addCommand( s_cmd, kb ); 
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool			AbstractApril::remCommand			(
		const QString & s_cmd, cmdCallBack kb )
{ 
	return uniq_->cmd_map.remCommand( s_cmd, kb );
}
/* ========================================================================= */


/*  CLASS    =============================================================== */
//
//
//
//
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
