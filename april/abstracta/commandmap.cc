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
#include	<april/abstracta/aatokenizer.h>
#include	"aaoutput.h"

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
CommandMap::CommandMap	( void )
	: MemTrack(),
	  b_exit_(false)
{
	APRDBG_CDTOR;
	/* stub */
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
CommandMap::~CommandMap	( void )
{
	APRDBG_CDTOR;
	/* stub */
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
	AaTkString aas = AaTokenizer::basicTk( s_input );
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
			AaOutput::showError( s_err );
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
				AaOutput::showError( s_err );
			}
			else if ( kb( s_cmd, aas, s_err ) == false )
			{
				AaOutput::showError( s_err );
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

/*  CLASS    =============================================================== */
//
//
//
//
/* ------------------------------------------------------------------------- */
/* ========================================================================= */



