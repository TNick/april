/* ========================================================================= */
/* ------------------------------------------------------------------------- */
/*!
  \file			cmdtest.h
  \date			Jun 2013
  \author		TNick
  
  \brief		Contains the definition for CmdTest class
  
  
*//*


 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Please read COPYING and README files in root folder
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
#ifndef __CMDTEST_INC__
#define __CMDTEST_INC__
//
//
//
//
/*  INCLUDES    ------------------------------------------------------------ */

#include    <QString>
#include    <QStringList>
#include    <QList>
#include    <QVector>
#include    <QRegExp>

/*  INCLUDES    ============================================================ */
//
//
//
//
/*  DEFINITIONS    --------------------------------------------------------- */

namespace   cmd_test    {

class	Target;

/* ------------------------------------------------------------------------- */
#ifdef QT_NO_DEBUG
#define SHOW_DEBUG 0
#else
#define SHOW_DEBUG 1
#endif

#if SHOW_DEBUG
#define dbgtext(txt) qDebug() << txt;
#define dbgtextl(txt) qDebug() << txt;// << "\n";
#define dbgtext2l(txt1,txt2) qDebug() << txt1 << txt2;// << "\n";
#define dbgtext3l(txt1,txt2,txt3) qDebug() << txt1 << txt2 << txt3;// << "\n";
#else
#define dbgtext(txt)
#define dbgtextl(txt)
#define dbgtext2l(txt1,txt2)
#define dbgtext3l(txt1,txt2,txt3)
#endif
/* ========================================================================= */

/*  DEFINITIONS    ========================================================= */
//
//
//
//
/*  CLASS    --------------------------------------------------------------- */

/**
*	@brief
*/
class CmdTest				{
	
	//
	//
	//
	//
	/*  DEFINITIONS    ----------------------------------------------------- */
	
public:
	
	enum LogTypes		{
		LOG_FILES = 0x00001,
		LOG_TARGETS = 0x00002,
		LOG_COMMANDS = 0x00004,
		LOG_EXPECTS = 0x00008,
		LOG_SUCCESS = 0x00010,
		LOG_FAILURE = 0x00020,
		
		
		LOG_ALL = 
		LOG_FILES | LOG_TARGETS | 
		LOG_COMMANDS | LOG_EXPECTS |
		LOG_SUCCESS | LOG_FAILURE
	};
	
#define fileError(txt)	CmdTest::error( s_file, i_line+1, s_line, txt )
	
	class CmdEntry;
	
	typedef bool (*cmdRoutine) ( const CmdEntry & cmd );
	
	struct CmdEntry {
		QRegExp	rex_;
		cmdRoutine call_;
	};
	
	/*  DEFINITIONS    ===================================================== */
	//
	//
	//
	//
	/*  DATA    ------------------------------------------------------------ */
	
private:
	
	//! list of targets
	QList<Target*>				targets_;
	
	//! list of source files
	QStringList					files_;
	
	//! current target
	Target *					t_crt_;
	
	//! current file
	int							file_crt_;
	
	//! what should be visible to the user
	LogTypes					log_types_;
	
	//! list of commands and associated callbacks
	QVector<CmdEntry>			commands_;
	
	//! the one and only instance
	static CmdTest *			uniq_;
	
	
	
	/*  DATA    ============================================================ */
	//
	//
	//
	//
	/*  FUNCTIONS    ------------------------------------------------------- */
	
private:
	
	//! constructor
	CmdTest				( void );
	
	//! destructor;
	virtual				~CmdTest		( void );
	
public:
	
	//! initialisation method
	static bool			init			( void );
	
	//! finish method
	static void			end				( void );
	
	//! the one and only instance
	static CmdTest *	unique			( void )
	{ return uniq_; }
	
	//! process a source file
	static QString	 	crtFile		( void );
	
	//! process a source file
	static bool			processFile		( const QString & the_file );
	
	//! find a target given its name
	static int			findTargetId	( const QString & s_name );
	
	//! find a target given its name
	static int			findTargetId	( const Target * trg );
	
	//! find a target given its name
	static Target *		findTarget		( const QString & s_name );
	
	//! get existing target or start a new one
	static Target *		getTarget		( const QString & s_name );
	
	//! sends a command to current target
	static bool			sendCommand		( const QString & s_cmd );
	
	//! compares existing output to provided pattern
	static bool			expectOutput	( const QString & s_out );
	
	//! prints an error
	static void			error			( const QString & s_text );
	
	//! prints an error continuation
	static void			errorContin		( const QString & s_text );
	
	//! prints an error for given file, line number and content
	static void			error			( 
			const QString & s_file, 
			int i_line, 
			const QString & s_line, 
			const QString & s_text
			);
	
	//! prints an informative message
	static void			log				( 
			LogTypes				ty,
			const QString &			s_text
			);
	
	//! a succesfull test
	static void			successTest		(
			Target *				target,
			const QString &			s_text
			);
	
	//! a failed test
	static void			failedTest		(
			Target *				target,
			const QString &			s_text
			);
	
	
private:
	
	
	//! read the content of a file in memory
	static bool			get_file_contents	(
			const QString &			filename,
			QStringList &			contents
			);
	
	
	static bool commandWhites		( const CmdEntry & cmd );
	static bool commandComments		( const CmdEntry & cmd );
	static bool commandTarget		( const CmdEntry & cmd );
	static bool commandTargetArgs	( const CmdEntry & cmd );
	static bool commandEndTarget	( const CmdEntry & cmd );
	static bool commandExit			( const CmdEntry & cmd );
	static bool commandExitNot		( const CmdEntry & cmd );
	static bool commandCommand		( const CmdEntry & cmd );
	static bool commandExpect		( const CmdEntry & cmd );
	static bool commandExpectE		( const CmdEntry & cmd );
	static bool commandExpectO		( const CmdEntry & cmd );
	static bool commandInclude		( const CmdEntry & cmd );
	static bool commandSwitch		( const CmdEntry & cmd );
	
	
	/*  FUNCTIONS    ======================================================= */
	//
	//
	//
	//
	
};	/*	class CmdTest	*/

/*  CLASS    =============================================================== */
//
//
//
//

}   //  namespace   cmd_test

#endif // __CMDTEST_INC__
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
