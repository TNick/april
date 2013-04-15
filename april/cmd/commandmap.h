/* ========================================================================= */
/* ------------------------------------------------------------------------- */
/*!
  \file			commandmap.h
  \date			Apr 2013
  \author		TNick

  \brief		Contains the definition for CommandMap class


*//*


 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Please read COPYING and README files in root folder
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
#ifndef __COMMANDMAP_INC__
#define __COMMANDMAP_INC__
//
//
//
//
/*  INCLUDES    ------------------------------------------------------------ */

#include    <april/april.h>
#include	<QMap>

/*  INCLUDES    ============================================================ */
//
//
//
//
/*  DEFINITIONS    --------------------------------------------------------- */

namespace   april    {

class	AaTkString;
class	AaModule;

//! the definition for a callback used with commands
typedef	bool	(*cmdCallBack)	(
		const QString &			s_cmd,
		const AaTkString &		atks,
		QString &				s_err
		);

/*  DEFINITIONS    ========================================================= */
//
//
//
//
/*  CLASS    --------------------------------------------------------------- */

/**
*	@brief	Class capable  of storing a list of commands and associated callbacks
*/
class
	APRILSHARED_EXPORT
	CommandMap		: public MemTrack		{
	BBM_TRACK( CommandMap );

	//
	//
	//
	//
	/*  DEFINITIONS    ----------------------------------------------------- */

	typedef QMap<QString,cmdCallBack>						CmdList;
	typedef QMap<QString,cmdCallBack>::Iterator				CmdIter;
	
	/*  DEFINITIONS    ===================================================== */
	//
	//
	//
	//
	/*  DATA    ------------------------------------------------------------ */

private:

	//! the list of commands
	CmdList						cmd_list_;

	//! should exit?
	bool						b_exit_;
	
	//! the list of modules
	QList<AaModule*>			modules_;
	
	//! default instance	
	static CommandMap *			def_inst_;
	
	/*  DATA    ============================================================ */
	//
	//
	//
	//
	/*  FUNCTIONS    ------------------------------------------------------- */

public:

	//! constructor
	CommandMap			( void );

	//! destructor;
	virtual				~CommandMap		( void );


	//! add a command to the list; returns false if the string is in use
	bool				addCommand		( const QString & s_cmd, cmdCallBack kb );

	//! remove a command to from list; returns false if not found or don't match
	bool				remCommand		( const QString & s_cmd, cmdCallBack kb );
	
	//! the list of registered commands
	QStringList			commands		( void ) const;

	//! add an module; appends module's list of commands and appends the module
	bool				addModule		( AaModule * m );

	//! add an module; removes module's list of commands and removes the module
	bool				remModule		( AaModule * m );
	
	//! the list of registered modules
	QStringList			modules			( void ) const;

	
	//! execute the command associated with the given string
	void				execute			( const QString & s_input );
	
	//! should exit?
	bool				shouldExit		( void ) const
	{ return b_exit_; }
	
	//! should not exit?
	bool				shouldContinue	( void ) const
	{ return b_exit_ == false; }

	//! default instance
	static const CommandMap *	defaultInstance	( void );

	/*  FUNCTIONS    ======================================================= */
	//
	//
	//
	//
	
};	/*	class CommandMap	*/

/*  CLASS    =============================================================== */
//
//
//
//

}   //  namespace   april

#endif // __COMMANDMAP_INC__
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
