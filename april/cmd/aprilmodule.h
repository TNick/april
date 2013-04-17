/* ========================================================================= */
/* ------------------------------------------------------------------------- */
/*!
  \file			aprilmodule.h
  \date			Apr 2013
  \author		TNick
  
  \brief		Contains the definition for AprilModule class
  
  
*//*


 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Please read COPYING and README files in root folder
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
#ifndef __APRILMODULE_INC__
#define __APRILMODULE_INC__
//
//
//
//
/*  INCLUDES    ------------------------------------------------------------ */

#include    <april/april.h>
#include	<libbbb/1/refcnt.h>
#include	<april/logic/uniqueid.h>

/*  INCLUDES    ============================================================ */
//
//
//
//
/*  DEFINITIONS    --------------------------------------------------------- */

namespace   april    {

class	World;
class	AaTkString;
class	AaToken;
class	CommandMap;
class	Actor;

/*  DEFINITIONS    ========================================================= */
//
//
//
//
/*  CLASS    --------------------------------------------------------------- */

/**
*	@brief	Base class for all modules
*/
class
		APRILSHARED_EXPORT
		AprilModule		: public libbbb::RefCnt, public MemTrack		{
	BBM_TRACK( AprilModule );
	
	//
	//
	//
	//
	/*  DEFINITIONS    ----------------------------------------------------- */
	
	/*  DEFINITIONS    ===================================================== */
	//
	//
	//
	//
	/*  DATA    ------------------------------------------------------------ */
	
private:
	
	//! the CommandMap where we belong
	CommandMap *			cmd_map_;
	
	/*  DATA    ============================================================ */
	//
	//
	//
	//
	/*  FUNCTIONS    ------------------------------------------------------- */
	
public:
	
	//! constructor
	AprilModule			( CommandMap * cmd_map );
	
protected:
	
	//! destructor;
	virtual				~AprilModule		( void );
	
public:
	
	//! insert all commands
	virtual void		insertCommands	( CommandMap * cm ) = 0;
	
	//! remove all commands
	virtual void		removeCommands	( CommandMap * cm ) = 0;
	
	//! tell your name
	virtual QString		name			( void ) = 0;
	
	//! the CommandMap where we belong
	inline CommandMap *	cmdMap			( void ) const 
	{ return cmd_map_; }
	
	
public:
	//!@{
	//! common types of errors
	static void errorNumberOfArguments(QString &s_err);
	static void errorOneArgumentExpected(QString &s_err);
	static void errorNoAssocFile(World *w, QString &s_err);
	static void errorEnergyInteger(QString &s_err);
	static void errorUnknownOption(QString &s_err, const QString &s_tk);
	static void errorIntegerExpected(QString &s_err, const QString &s_tk);
	static void errorIdExpected(QString &s_err, const QString &s_tk);
	static void errorNoCurrentWorld(QString &s_err);
	//!@}
	
public:
	
	//! get the string representing command line info for a command
	static QString		getCLUsage		( const QString & s_name );
	
	//! save the usage for a command
	static bool			setUsage		(
			const QString &					s_name,
			const QStringList &				usage,
			const QStringList &				usage_descr,
			const QStringList &				opts,
			const QList<QStringList> &		opts_descr,
			const QStringList &				obs
			);
	
	
	//! callback for functions with no arguments
	typedef QString ( * arg0Func)	( void );
	
	//! callback for functions with one argument
	typedef QString ( * arg1Func)	( const QString & s_arg_1, const AaToken & tk1 );
	
	//! callback for functions with no arguments and world expectations
	typedef QString ( * arg0WFunc)	( World * w );
	
	//! callback for functions with one argument and world expectations
	typedef QString ( * arg1WFunc)	( 
			World *					w, 
			const QString &			s_arg_1, 
			const AaToken &			tk1
			);
	
	//! callback for functions that require a default world with 2 args
	typedef QString ( * argW2Func)	( 
			World * w, const QString & s_arg_1, const AaToken & tk1,
			const QString & s_arg_2, const AaToken & tk2 );
	
	//! callback for functions with an actor as single argument
	typedef QString ( * argA0Func)	( Actor * a );
	
	//! callback for functions with an actor and an ID as argument
	typedef QString ( * argAIdFunc)	( Actor * a, ID id );
	
	
	
	//! parse argument i and get an unsigned integer
	static bool			getUIntArg		(
			const AaTkString &		atks,
			int						i,
			QString &				s_err,
			quint64 *				val
			);
	
protected:
	
	//! helper for functions with no arguments
	static bool			funcArg0		(
			const QString &			s_cmd,
			const AaTkString &		atks,
			QString &				s_err,
			arg0Func				kb
			);
	
	//! helper for functions with one argument
	static bool			funcArg1		(
			const QString &			s_cmd,
			const AaTkString &		atks,
			QString &				s_err,
			arg1Func				kb
			);
	
	//! helper for functions with no arguments and world expectations
	static bool			funcArg0W		(
			const QString &			s_cmd,
			const AaTkString &		atks,
			QString &				s_err,
			arg0WFunc				kb
			);
	
	//! helper for functions with one argument and world expectations
	static bool			funcArg1W		(
			const QString &			s_cmd,
			const AaTkString &		atks,
			QString &				s_err,
			arg1WFunc				kb
			);
	
	
	//! helper for functions with two arguments and world expectations
	static bool			funcArg_W2		(
			const QString &			s_cmd,
			const AaTkString &		atks,
			QString &				s_err,
			argW2Func				kb
			);
	
	
	//! helper for functions with an argument that is an actor index
	static bool			funcArg_A0		(
			const QString &			s_cmd,
			const AaTkString &		atks,
			QString &				s_err,
			argA0Func				kb
			);
	
	//! helper for functions with irst argument an actor index and second an ID
	static bool			funcArg_AID		(
			const QString &			s_cmd,
			const AaTkString &		atks,
			QString &				s_err,
			argAIdFunc				kb
			);
	
	/*  FUNCTIONS    ======================================================= */
	//
	//
	//
	//
	
};	/*	class AprilModule	*/

/*  CLASS    =============================================================== */
//
//
//
//

}   //  namespace   april

#endif // __APRILMODULE_INC__
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
