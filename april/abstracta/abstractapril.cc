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
#include	"modules/aaworld.h"
#include	"modules/aaplugins.h"

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
	/* stub */	
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
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void			AbstractApril::init					( void )
{
	/* load build-in modules */
	
	AaWorld * module_w = new AaWorld();
	addModule( module_w );
	REMOVE_CONSTRUCTOR_REF(module_w);

	AaPlugIns * module_p = new AaPlugIns();
	addModule( module_p );
	REMOVE_CONSTRUCTOR_REF(module_p);

}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
int				AbstractApril::runMainLoop			( void )
{
	/* create the one and only instance */
	uniq_ = new AbstractApril();
	uniq_->init();
	
	std::string prompt_string;
	std::string buffer;
	prompt_string = ">";
	
	for ( ;; )
	{
		cout << prompt_string;
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

/*  CLASS    =============================================================== */
//
//
//
//
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
