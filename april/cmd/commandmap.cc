/* ========================================================================= */
/* ------------------------------------------------------------------------- */
/*!
  \file			commandmap.cc
  \date			Apr 2013
  \author		TNick
  
  \brief		Contains the implementation of CommandMap class
  
  
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

#include	"commandmap.h"
#include	"apriltokenizer.h"
#include	<april/logic/aoutput.h>
#include	<april/cmd/aprilmodule.h>

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

CommandMap *		CommandMap::def_inst_ = NULL;

/*  DATA    ================================================================ */
//
//
//
//
/*  CLASS    --------------------------------------------------------------- */

/* ------------------------------------------------------------------------- */
CommandMap::CommandMap	( void )
	: MemTrack(),
	  b_exit_(false)
{
	APRDBG_CDTOR;
	def_inst_ = this;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
CommandMap::~CommandMap	( void )
{
	APRDBG_CDTOR;
	if ( def_inst_ == this )
	{
		def_inst_ = NULL;
	}
	foreach( AprilModule * itr, modules_ )
	{
		DEC_REF(itr,this);
	}
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
CommandMap *	CommandMap::defaultInstance			( void )
{
	return def_inst_;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool				CommandMap::addCommand				(
		const QString & s_cmd, cmdCallBack kb )
{
	QString	s_actual_cmd = s_cmd.trimmed().toLower();
	if ( cmd_list_.contains( s_actual_cmd ) )
		return false;
	cmd_list_.insert( s_actual_cmd, kb );
	return true;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool				CommandMap::remCommand				(
		const QString & s_cmd, cmdCallBack kb )
{
	CmdIter itr = cmd_list_.find( s_cmd );
	if ( itr == cmd_list_.end() )
	{
		return false;
	}
	if ( itr.value() != kb )
	{
		return false;
	}
	cmd_list_.erase( itr );
	return true;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void				CommandMap::execute					( 
		const QString & s_input )
{
	AaTkString aas = AprilTokenizer::basicTk( s_input );
	QString s_err;
	int i_max = aas.tk_.count();
	if ( i_max > 0 )
	{
		const AaToken & cmd = aas.tk_.at( 0 );
		
		/* first thing should be a command */
		if ( cmd.hasLowCodes() | cmd.isAllWhite() | cmd.middleWhite() )
		{
			s_err = QObject::tr( 
						"Error! Improper command. The command may not\n" 
						"contain spaces and special codes."
						);
			AOutput::showError( s_err );
			return;
		}
		/* convert commands into an easier to read form */
		QString s_cmd = aas.getToken( cmd );
		if ( cmd.leadingWhite() | cmd.trailingWhite() )
		{
			s_cmd = s_cmd.trimmed();
		}
		if ( cmd.hasUpperCaseLetters() )
		{
			s_cmd = s_cmd.toLower();
		}
		
		/* is this an exit request? */
		if ( ( s_cmd == "exit" ) ||
			 ( s_cmd == "q") ||
			 ( s_cmd == "quit") )
		{
			b_exit_ = true;
		}
		else
		{
			cmdCallBack kb = cmd_list_.value( s_cmd, NULL );
			if ( kb == NULL )
			{
				s_err = QObject::tr( 
							"Error! Command %1 was not found."
							).arg( s_cmd );
				AOutput::showError( s_err );
			}
			else if ( kb( s_cmd, aas, s_err ) == false )
			{
				AOutput::showError( s_err );
			}
		}
	}
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
QStringList				CommandMap::commands		( void ) const
{
	QStringList sl = cmd_list_.keys();
	sl.sort();
	return sl;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool			CommandMap::addModule			( AprilModule * m )
{
	if ( modules_.contains( m ) )
	{
		return false;
	}
	modules_.append( m );
	m->insertCommands( this );
	INC_REF(m,this);
	return true;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool			CommandMap::remModule			( AprilModule * m )
{
	if ( modules_.contains( m ) == false )
	{
		return false;
	}
	modules_.removeOne( m );
	m->removeCommands( this );
	DEC_REF(m,this);
	return true;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
QStringList		CommandMap::modules				( void ) const
{
	QStringList sl;
	foreach( AprilModule * itr, modules_ )
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



