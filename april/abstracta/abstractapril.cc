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

#include	<april/logic/aoutput.h>
#include	<april/cmd/aprilmodule.h>
#include	<april/cmd/apriltokenizer.h>
#include	<april/cmd/modules/amodapril.h>
#include	<april/cmd/modules/amodworld.h>
#include	<april/cmd/modules/amodplugins.h>
#include	<april/cmd/modules/amoddna.h>
#include	<april/cmd/modules/amodid.h>
#include	<april/cmd/modules/amodactor.h>
#include	<april/cmd/modules/amodactuator.h>
#include	<april/cmd/modules/amodsensor.h>
#include	<april/cmd/modules/amodbrain.h>
#include	<april/cmd/modules/amodreflex.h>
#include	<april/cmd/modules/amodevents.h>

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
	AOutput::init();
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
AbstractApril::~AbstractApril	( void )
{
	APRDBG_CDTOR;
	AOutput::end();
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void			AbstractApril::init					( void )
{
	/* load build-in modules */
	
	AModApril * module_april = new AModApril( &cmd_map );
	addModule( module_april );
	REMOVE_CONSTRUCTOR_REF(module_april);
	
	AModWorld * module_w = new AModWorld( &cmd_map );
	addModule( module_w );
	REMOVE_CONSTRUCTOR_REF(module_w);
	
	AModPlugIns * module_p = new AModPlugIns( &cmd_map );
	addModule( module_p );
	REMOVE_CONSTRUCTOR_REF(module_p);
	
	AModDNA * module_dna = new AModDNA( &cmd_map );
	addModule( module_dna );
	REMOVE_CONSTRUCTOR_REF(module_dna);
	
	AModId * module_id = new AModId( &cmd_map );
	addModule( module_id );
	REMOVE_CONSTRUCTOR_REF(module_id);
	
	AModActor * module_a = new AModActor( &cmd_map );
	addModule( module_a );
	REMOVE_CONSTRUCTOR_REF(module_a);
	
	AModSensor * module_s = new AModSensor( &cmd_map );
	addModule( module_s );
	REMOVE_CONSTRUCTOR_REF(module_s);
	
	AModReflex * module_r = new AModReflex( &cmd_map );
	addModule( module_r );
	REMOVE_CONSTRUCTOR_REF(module_r);
	
	AModBrain * module_b = new AModBrain( &cmd_map );
	addModule( module_b );
	REMOVE_CONSTRUCTOR_REF(module_b);
	
	AModActuator * module_ak = new AModActuator( &cmd_map );
	addModule( module_ak );
	REMOVE_CONSTRUCTOR_REF(module_ak);
	
	AModEvent * module_e = new AModEvent( &cmd_map );
	addModule( module_e );
	REMOVE_CONSTRUCTOR_REF(module_e);
	
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
		AOutput::showError( 
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
		AModWorld::dOpenWorld( iter, s_err );
		AOutput::showInfo( s_err );
	}
	
	/* prepare the prompt */
	std::string buffer;
	for ( ;; )
	{
		AOutput::showPrompt();
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
bool			AbstractApril::addModule			( AprilModule * m )
{
	return uniq_->cmd_map.addModule( m );
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool			AbstractApril::remModule			( AprilModule * m )
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
