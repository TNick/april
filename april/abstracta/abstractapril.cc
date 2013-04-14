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
#include	"aamodule.h"
#include	"aaoutput.h"
#include	"aatokenizer.h"
#include	"modules/aaapril.h"
#include	"modules/aaworld.h"
#include	"modules/aaplugins.h"
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
	foreach( AaModule * itr, modules_ )
	{
		DEC_REF(itr,this);
	}
	AaOutput::end();
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void			AbstractApril::init					( void )
{
	/* load build-in modules */
	
	AaApril * module_april = new AaApril();
	addModule( module_april );
	REMOVE_CONSTRUCTOR_REF(module_april);
	
	AaWorld * module_w = new AaWorld();
	addModule( module_w );
	REMOVE_CONSTRUCTOR_REF(module_w);

	AaPlugIns * module_p = new AaPlugIns();
	addModule( module_p );
	REMOVE_CONSTRUCTOR_REF(module_p);

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
	if ( uniq_->modules_.contains( m ) )
	{
		return false;
	}
	uniq_->modules_.append( m );
	m->insertCommands();
	INC_REF(m,uniq_);
	return true;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool			AbstractApril::remModule			( AaModule * m )
{
	if ( uniq_->modules_.contains( m ) == false )
	{
		return false;
	}
	uniq_->modules_.removeOne( m );
	m->removeCommands();
	DEC_REF(m,uniq_);
	return true;
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
	QStringList sl;
	foreach( AaModule * itr, uniq_->modules_ )
	{
		sl.append( itr->name() );
	}
	return sl;
}
/* ========================================================================= */

/*  CLASS    =============================================================== */
//
//
//
//
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
