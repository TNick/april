/* ========================================================================= */
/* ------------------------------------------------------------------------- */
/*!
  \file			aatokenizer.h
  \date			Apr 2013
  \author		TNick
  
  \brief		Contains the definition for AaTokenizer class
  
  
*//*


 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Please read COPYING and README files in root folder
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
#ifndef __AATOKENIZER_INC__
#define __AATOKENIZER_INC__
//
//
//
//
/*  INCLUDES    ------------------------------------------------------------ */

#include    <april/april.h>

/*  INCLUDES    ============================================================ */
//
//
//
//
/*  DEFINITIONS    --------------------------------------------------------- */

namespace   april    {

//! a token descriptor (string is not contained inside)
struct	AaToken		{
	
	//! properties of a token
	enum	Flags	{
		HasSpaces			= 0x0001,
		HasTabs				= 0x0002,
		HasNewLine			= 0x0004,
		HasLineFeed			= HasNewLine,
		HasCR				= 0x0008,
		HasWhites			= HasSpaces | HasTabs | HasNewLine | HasCR,
		
		HasDigits			= 0x0010,
		HasLetters			= 0x0020,
		OnlyHex				= 0x0040,	/**< set for [A-Fa-f] letters and [0-9] digits */
		HasComma			= 0x0080,
		HasDot				= 0x0100,
		WasQuoted			= 0x0200,
		
		HasLeadingWhites	= 0x0400,
		HasTrailingWhites	= 0x0800,
		HasMiddleWhites		= 0x1000,
		IsAllWhites			= HasLeadingWhites | HasMiddleWhites | HasTrailingWhites
		
	};
	
	//! initialise the structure to ground values
	void	init			( void )
	{ i_stat = -1; i_end = -1; flags = 0; }
	
	//!@{
	//! querry the flags
	bool	isAllWhite		( void ) const
	{ return ( flags & IsAllWhites ) == IsAllWhites; }
	
	bool	leadingWhite	( void ) const
	{ return ( flags & HasLeadingWhites ) == HasLeadingWhites; }
	
	bool	trailingWhite	( void ) const
	{ return ( flags & HasTrailingWhites ) == HasTrailingWhites; }
	
	bool	middleWhite		( void ) const
	{ return ( flags & HasMiddleWhites ) == HasMiddleWhites; }
	
	bool	hasWhiteSpaces	( void ) const
	{ return ( flags & HasWhites ) != 0; }
	
	bool	hasDigits		( void ) const
	{ return ( flags & HasDigits ) != 0; }
	
	bool	hasLetters		( void ) const
	{ return ( flags & HasLetters ) != 0; }
	
	bool	hasComma		( void ) const
	{ return ( flags & HasComma ) != 0; }
	
	bool	hasDot			( void ) const
	{ return ( flags & HasDot ) != 0; }
	
	bool	isInteger		( void ) const
	{ 
		return ( isAllWhite() == false ) && 
				( middleWhite() == false ) && 
				hasDigits() && 
				( hasLetters() == false ); 
	}
	
	bool	isHexInteger	( void ) const
	{ 
		return ( isAllWhite() == false ) && 
				( middleWhite() == false ) && 
				( ( flags & OnlyHex ) == OnlyHex ); 
	}
	//!@}


	//! the offset from the start of the string to the start of the token
	int		i_stat;
	
	//! the offset from the start of the string to the end of the token
	int		i_end;
	
	//! a combination of flags from Flags enum
	int		flags;
	
}; /* struct AaToken */


//! a tokenised string; contains the string itself and the list of tokens
struct	AaTkString		{
	
	//! the string
	QString				s_;
	
	//! the list of token descriptors
	QVector<AaToken>	tk_;
	
}; /* struct AaTkString */

/*  DEFINITIONS    ========================================================= */
//
//
//
//
/*  CLASS    --------------------------------------------------------------- */

/**
*	@brief	A class capable of splitting strings into tokens
*/
class AaTokenizer		: public MemTrack		{
	BBM_TRACK( AaTokenizer );
	
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
	
	
	
	/*  DATA    ============================================================ */
	//
	//
	//
	//
	/*  FUNCTIONS    ------------------------------------------------------- */
	
public:
	
	//! tokenise a string; use white spaces as separators; use quotes
	static AaTkString		basicTk			( const QString & s );
	
	/*  FUNCTIONS    ======================================================= */
	//
	//
	//
	//
	
};	/*	class AaTokenizer	*/

/*  CLASS    =============================================================== */
//
//
//
//

}   //  namespace   april

#endif // __AATOKENIZER_INC__
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
