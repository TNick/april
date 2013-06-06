/* ========================================================================= */
/* ------------------------------------------------------------------------- */
/*!
  \file			apriltokenizer.cc
  \date			Apr 2013
  \author		TNick
  
  \brief		Contains the implementation of AprilTokenizer class
  
  
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

#include	"apriltokenizer.h"


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
AaTkString				AprilTokenizer::basicTk			( const QString & s )
{
	QString::ConstIterator itr = s.constBegin();
	QString::ConstIterator itr_end = s.constEnd();
	AaTkString	ret;
	AaToken		tkn;
	ushort		c;
	QChar		ch;
	ushort		quote = 0;
	bool		in_token = false;
	int			i_current = 0;
	
	ret.tk_.reserve( qMin( 1000, s.length() ) );
	ret.s_ = s;
	
	/* skip leading white spaces */
	while ( itr != itr_end )
	{
		ch = *itr;
		c = (*itr).unicode();
		if ( ch.isSpace() == false )
		{
			in_token = true;
			break;
		}
		itr++; i_current++;
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
				if ( ch.isSpace() == false )
				{
					in_token = true;
					break;
				}
				
				itr++; i_current++;
				if ( itr == itr_end )
					break;
				ch = *itr; c = ch.unicode();
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
			itr++; i_current++;
			if ( itr == itr_end )
			{ /* a string consisting of only a quote */
				tkn.flags = 0;
				tkn.i_start = i_current-1;
				tkn.i_end = i_current;
				ret.tk_.append( tkn );
				break;
			}
			ch = *itr; c = ch.unicode();
		}
		tkn.i_start = i_current;
		bool end_of_token = false;
		bool all_whites = true;
		bool all_hex = true;
		bool this_is_white;
		bool prev_was_white = false;
		bool leading_whites = false;
		bool prev_all_whites;
		for ( ;; ) {
			this_is_white = false;
			prev_all_whites = all_whites;
			switch ( c ) {
			case ' ':	{
				if ( tkn.wasQuoted() == false ) {
					end_of_token = true;
				}
				else {
					tkn.flags |= AaToken::HasSpaces;
					all_hex = false;
					this_is_white = true;
				}
				break; }
			case '\t':	{
				if ( tkn.wasQuoted() == false ) {
					end_of_token = true;
				}
				else {
					tkn.flags |= AaToken::HasTabs;
					all_hex = false;
					this_is_white = true;
				}
				break; }
			case '\n':	{
				if ( tkn.wasQuoted() == false ) {
					end_of_token = true;
				}
				else {
					tkn.flags |= AaToken::HasNewLine;
					all_hex = false;
					this_is_white = true;
				}
				break; }
			case '\r':	{
				if ( tkn.wasQuoted() == false ) {
					end_of_token = true;
				}
				else {
					tkn.flags |= AaToken::HasCR;
					all_hex = false;
					this_is_white = true;
				}
				break; }
			case '0':
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
				tkn.flags |= AaToken::HasDigits;
				all_whites = false;
				break;
			case ',': {
				tkn.flags |= AaToken::HasComma;
				all_whites = false;
				all_hex = false;
				break; }
			case '.': {
				tkn.flags |= AaToken::HasDot;
				all_whites = false;
				all_hex = false;
				break; }
			case '\'': 
			case '"': 
				if ( tkn.wasQuoted() && ( quote == c ) ) {
					end_of_token = true;
				}
				else {
					all_whites = false;
					all_hex = false;
				}
				break;
			default:	{
				all_whites = false;
				if ( c < ' ' )
				{
					tkn.flags |= AaToken::HasLowCodes;
					all_hex = false;
				}
				else if ( c >= 'a' && c <= 'f' )
				{
					tkn.flags |= AaToken::HasLetters;
				}
				else if ( c > 'f' && c <= 'z' )
				{
					tkn.flags |= AaToken::HasLetters;
					all_hex = false;
				}
				else if ( c >= 'A' && c <= 'F' )
				{
					tkn.flags |= AaToken::HasLetters;
				}
				else if ( c > 'F' && c <= 'Z' )
				{
					tkn.flags |= AaToken::HasLetters;
					all_hex = false;
				}
				else if ( c > 127 )
				{
					tkn.flags |= AaToken::HasLetters;
					all_hex = false;
				}
				else
				{
					all_hex = false;
				}
			} /* default */
			} /* switch */
			if ( end_of_token )
				break;
			
			if ( this_is_white == false )
			{
				if ( leading_whites == false )
				{ /* on first non-white we look for leading */
					if ( ( prev_all_whites == true ) && 
						 ( i_current > tkn.i_start ) )
					{
						tkn.flags |= AaToken::HasLeadingWhites;
					}
					leading_whites = true;
				}
				else if ( prev_was_white )
				{ /* next we look for middle */
					tkn.flags |= AaToken::HasMiddleWhites;
				}
			}
			prev_was_white = this_is_white;
			
			/* step to next character */
			itr++; i_current++;
			if ( itr == itr_end )
				break;
			ch = *itr; c = ch.unicode();
			
		}
		tkn.i_end = i_current;
		if ( tkn.i_end == tkn.i_start )
		{ /* this can only happen in quoted strings */
			tkn.flags = AaToken::WasQuoted;
		}
		else
		{
			if ( prev_was_white )
			{
				tkn.flags |= AaToken::HasTrailingWhites;
			}
			if ( all_whites )
			{
				tkn.flags |= AaToken::IsAllWhites;
			}
			if ( all_hex && ( ( tkn.flags & AaToken::HasMiddleWhites ) == 0 ) )
			{
				tkn.flags |= AaToken::OnlyHex;
			}
		}
		ret.tk_.append( tkn );
		
		/* end of string? */
		in_token = false;
		if ( itr == itr_end )
			break;
		
		/* no, only end of token */
		itr++; i_current++;
		if ( itr == itr_end )
			break;
		ch = *itr; c = ch.unicode();
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
/*  CLASS    --------------------------------------------------------------- */

/* ------------------------------------------------------------------------- */
bool			AaTkString::isString		( const QString & s_match, int i ) const
{
	Q_ASSERT( i >= 0 );
	Q_ASSERT( i < tk_.count() );
	const AaToken & tk = tk_.at( i );
	if ( isString(tk) == false )
		return false;
	QString s_tk = getToken( tk );
	return ( s_tk == s_match );
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool			AaTkString::isString		( int i ) const
{
	Q_ASSERT( i >= 0 );
	Q_ASSERT( i < tk_.count() );
	const AaToken & tk = tk_.at( i );
	return isString( tk );
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool			AaTkString::isString		( const AaToken & tk ) const
{
	return ( tk.hasWhiteSpaces() || 
		 tk.hasDigits() || 
		 tk.hasComma() || 
		 tk.hasDot() || 
		 tk.hasLowCodes() ||
		 tk.hasUpperCaseLetters() ) == false;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool			AaTkString::isInteger		( int i ) const
{
	Q_ASSERT( i >= 0 );
	Q_ASSERT( i < tk_.count() );
	const AaToken & tk = tk_.at( i );
	return isInteger( tk );
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool			AaTkString::isInteger		( const AaToken & tk ) const
{
	return tk.isInteger();
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool			AaTkString::isHexInteger	( int i ) const
{
	Q_ASSERT( i >= 0 );
	Q_ASSERT( i < tk_.count() );
	const AaToken & tk = tk_.at( i );
	return isHexInteger( tk );
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool			AaTkString::isHexInteger	( const AaToken & tk ) const
{
	return tk.isHexInteger();
}
/* ========================================================================= */



/*  CLASS    =============================================================== */
//
//
//
//
/* ------------------------------------------------------------------------- */
/* ========================================================================= */



