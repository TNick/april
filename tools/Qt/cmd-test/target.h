/* ========================================================================= */
/* ------------------------------------------------------------------------- */
/*!
  \file			target.h
  \date			Jun 2013
  \author		TNick
  
  \brief		Contains the definition for Target class
  
  
*//*


 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Please read COPYING and README files in root folder
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
#ifndef __TARGET_INC__
#define __TARGET_INC__
//
//
//
//
/*  INCLUDES    ------------------------------------------------------------ */

#include    <QString>
#include    <QProcess>

/*  INCLUDES    ============================================================ */
//
//
//
//
/*  DEFINITIONS    --------------------------------------------------------- */

namespace   cmd_test    {
class	CmdTest;

/*  DEFINITIONS    ========================================================= */
//
//
//
//
/*  CLASS    --------------------------------------------------------------- */

/**
*	@brief A target application
*/
class Target		: public QProcess		{
	
	//
	//
	//
	//
	/*  DEFINITIONS    ----------------------------------------------------- */
	
	friend class cmd_test::CmdTest;
	
	/*  DEFINITIONS    ===================================================== */
	//
	//
	//
	//
	/*  DATA    ------------------------------------------------------------ */
	
private:
	
	//! the name of the target
	QString					s_name_;
	
	//! number of failed tests
	int						i_failed_;
	
	//! number of succesfull tests
	int						i_success_;
	
	
	/*  DATA    ============================================================ */
	//
	//
	//
	//
	/*  FUNCTIONS    ------------------------------------------------------- */
	
protected:
	
	//! constructor
	Target				( 
			const QString & s_name );
	
	//! destructor;
	virtual				~Target			( void );
	
	//! start this target
	bool				start			( const QStringList & args = QStringList() );
	
	//! the name
	const QString &		name			( void ) const
	{ return s_name_; }
	
	//! sends a command to this target
	bool				sendCommand		( const QString & s_cmd );
	
	//! compares existing output to provided pattern
	bool				expectOutput	( const QString & s_out );
	
	//! the target is being activated
	void				activate		( void );
	
	//! a success
	void				incSuccessTest	( void )
	{ i_success_++; }
	
	//! a failure
	void				incFailedTest	( void )
	{ i_failed_++; }
	
	//! tell the number of successes
	int					successTests	( void )
	{ return i_success_; }
	
	//! tell the number of failed tests
	int					failedTests		( void )
	{ return i_failed_; }	
	
	//! tell the total numebr of tests
	int					allTests		( void )
	{ return i_failed_ + i_success_; }	
	
	//! checks if the target is running; emits error if is not
	bool				testRunning		( void );
	
	//! discards any text in the process buffer
	void				discardContent	( void );
	
	
public:

private:

	//! prints the content of the target
	void				debugPrint		( void );

	/*  FUNCTIONS    ======================================================= */
	//
	//
	//
	//
	
	
};	/*	class Target	*/

/*  CLASS    =============================================================== */
//
//
//
//

}   //  namespace   cmd_test

#endif // __TARGET_INC__
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
