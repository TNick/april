/* ========================================================================= */
/* ------------------------------------------------------------------------- */
/*!
  \file			aatokenizer.cc
  \date			Apr 2013
  \author		TNick
  
  \brief		Contains the implementation of AaTokenizer class
  
  
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

#include	"aatokenizer.h"


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
AaTkString				AaTokenizer::basicTk			( const QString & s )
{
	QString::ConstIterator itr = s.constBegin();
	QString::ConstIterator itr_end = s.constEnd();
	AaTkString	ret;
	AaToken		tkn;
	QChar		c;
	QChar		quote;
	bool		in_token = false;
	
	ret.tk_.reserve( qMax( 1000, s.length() ) );
	ret.s_ = s;
	
	/* skip leading white spaces */
	while ( itr != itr_end )
	{
		c = *itr;
		if ( c.isSpace() == false )
		{
			in_token = true;
			break;
		}
		itr++;
	}
	
	/* string of all-whites or empty? */
	if ( in_token == false )
	{
		return ret;
	}
	
	/* we're at the beginning of a string, with first letter in c */
	for ( ;; )
	{
		/* c has the character */
		if ( in_token == false )
		{
			/* find next token start */
			for ( ;; )
			{
				if ( c.isSpace() == false )
				{
					in_token = true;
					break;
				}
				
				itr++;
				if ( itr == itr_end )
					break;
				c = *itr;
			}
			/* end of the string? */
			if ( in_token == false )
			{
				break;
			}
		}
		
		/* in_token is true at this point */
		Q_ASSERT( in_token );
		tkn.init();

		/* do we start a quoted string or a regular one? */
		if ( ( c == '"' ) || ( c == '\'' ) )
		{
			tkn.flags |= AaToken::WasQuoted;
			quote = c;
		}
		else
		{
			
		}
		
		
		
		/* step to next character */
		itr++;
		if ( itr == itr_end )
			break;
		c = *itr;
		
		
	}
	
	ret.tk_.squeeze();
	return ret;
}
/* ========================================================================= */


/*  CLASS    =============================================================== */
//
//
//
//
/* ------------------------------------------------------------------------- */
/* ========================================================================= */


