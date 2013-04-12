
#include	<gtest/gtest.h>
#include	<april/aprillibrary.h>
#include	<april/abstracta/aatokenizer.h>

using namespace april;

TEST(AaTokenizer, empty_string) {
	
	initAprilLibrary();
	
	QString	s;
	AaTkString aas = AaTokenizer::basicTk( s );
	EXPECT_TRUE( aas.s_.isEmpty() );
	EXPECT_EQ( aas.tk_.count(), 0 );
	
	endAprilLibrary();
}

TEST(AaTokenizer, one_letter) {
	
	initAprilLibrary();
	
	QString	s("a");
	AaTkString aas = AaTokenizer::basicTk( s );
	EXPECT_FALSE( aas.s_.isEmpty() );
	EXPECT_EQ( aas.s_, s );
	EXPECT_EQ( aas.tk_.count(), 1 );
	const AaToken & tk1 = aas.tk_.at( 0 );
	EXPECT_EQ( tk1.i_start, 0 );
	EXPECT_EQ( tk1.i_end, 1 );
	EXPECT_FALSE( tk1.isAllWhite() );
	EXPECT_FALSE( tk1.leadingWhite() );
	EXPECT_FALSE( tk1.trailingWhite() );
	EXPECT_FALSE( tk1.middleWhite() );
	EXPECT_FALSE( tk1.hasWhiteSpaces() );
	EXPECT_FALSE( tk1.hasDigits() );
	EXPECT_TRUE( tk1.hasLetters() );
	EXPECT_FALSE( tk1.hasComma() );
	EXPECT_FALSE( tk1.hasDot() );
	EXPECT_FALSE( tk1.isInteger() );
	EXPECT_TRUE( tk1.isHexInteger() );
	EXPECT_FALSE( tk1.wasQuoted() );
	
	endAprilLibrary();
}

TEST(AaTokenizer, one_letter_leading) {
	
	initAprilLibrary();
	{
		QString	s(" a");
		AaTkString aas = AaTokenizer::basicTk( s );
		EXPECT_FALSE( aas.s_.isEmpty() );
		EXPECT_EQ( aas.s_, s );
		EXPECT_EQ( aas.tk_.count(), 1 );
		const AaToken & tk1 = aas.tk_.at( 0 );
		EXPECT_EQ( tk1.i_start, 1 );
		EXPECT_EQ( tk1.i_end, 2 );
		EXPECT_FALSE( tk1.isAllWhite() );
		EXPECT_FALSE( tk1.leadingWhite() );
		EXPECT_FALSE( tk1.trailingWhite() );
		EXPECT_FALSE( tk1.middleWhite() );
		EXPECT_FALSE( tk1.hasWhiteSpaces() );
		EXPECT_FALSE( tk1.hasDigits() );
		EXPECT_TRUE( tk1.hasLetters() );
		EXPECT_FALSE( tk1.hasComma() );
		EXPECT_FALSE( tk1.hasDot() );
		EXPECT_FALSE( tk1.isInteger() );
		EXPECT_TRUE( tk1.isHexInteger() );
		EXPECT_FALSE( tk1.wasQuoted() );
	}
	{
		QString	s( " 'a'" );
		AaTkString aas = AaTokenizer::basicTk( s );
		EXPECT_FALSE( aas.s_.isEmpty() );
		EXPECT_EQ( aas.s_, s );
		EXPECT_EQ( aas.tk_.count(), 1 );
		const AaToken & tk1 = aas.tk_.at( 0 );
		EXPECT_EQ( tk1.i_start, 2 );
		EXPECT_EQ( tk1.i_end, 3 );
		EXPECT_FALSE( tk1.isAllWhite() );
		EXPECT_FALSE( tk1.leadingWhite() );
		EXPECT_FALSE( tk1.trailingWhite() );
		EXPECT_FALSE( tk1.middleWhite() );
		EXPECT_FALSE( tk1.hasWhiteSpaces() );
		EXPECT_FALSE( tk1.hasDigits() );
		EXPECT_TRUE( tk1.hasLetters() );
		EXPECT_FALSE( tk1.hasComma() );
		EXPECT_FALSE( tk1.hasDot() );
		EXPECT_FALSE( tk1.isInteger() );
		EXPECT_TRUE( tk1.isHexInteger() );
		EXPECT_TRUE( tk1.wasQuoted() );
	}
	{
		QString	s( " ''" );
		AaTkString aas = AaTokenizer::basicTk( s );
		EXPECT_FALSE( aas.s_.isEmpty() );
		EXPECT_EQ( aas.s_, s );
		EXPECT_EQ( aas.tk_.count(), 1 );
		const AaToken & tk1 = aas.tk_.at( 0 );
		EXPECT_EQ( tk1.i_start, 2 );
		EXPECT_EQ( tk1.i_end, 2 );
		EXPECT_FALSE( tk1.isAllWhite() );
		EXPECT_FALSE( tk1.leadingWhite() );
		EXPECT_FALSE( tk1.trailingWhite() );
		EXPECT_FALSE( tk1.middleWhite() );
		EXPECT_FALSE( tk1.hasWhiteSpaces() );
		EXPECT_FALSE( tk1.hasDigits() );
		EXPECT_FALSE( tk1.hasLetters() );
		EXPECT_FALSE( tk1.hasComma() );
		EXPECT_FALSE( tk1.hasDot() );
		EXPECT_FALSE( tk1.isInteger() );
		EXPECT_FALSE( tk1.isHexInteger() );
		EXPECT_TRUE( tk1.wasQuoted() );
	}
	endAprilLibrary();
}

TEST(AaTokenizer, one_letter_trailing) {
	
	initAprilLibrary();
	{
		QString	s("a ");
		AaTkString aas = AaTokenizer::basicTk( s );
		EXPECT_FALSE( aas.s_.isEmpty() );
		EXPECT_EQ( aas.s_, s );
		EXPECT_EQ( aas.tk_.count(), 1 );
		const AaToken & tk1 = aas.tk_.at( 0 );
		EXPECT_EQ( tk1.i_start, 0 );
		EXPECT_EQ( tk1.i_end, 1 );
		EXPECT_FALSE( tk1.isAllWhite() );
		EXPECT_FALSE( tk1.leadingWhite() );
		EXPECT_FALSE( tk1.trailingWhite() );
		EXPECT_FALSE( tk1.middleWhite() );
		EXPECT_FALSE( tk1.hasWhiteSpaces() );
		EXPECT_FALSE( tk1.hasDigits() );
		EXPECT_TRUE( tk1.hasLetters() );
		EXPECT_FALSE( tk1.hasComma() );
		EXPECT_FALSE( tk1.hasDot() );
		EXPECT_FALSE( tk1.isInteger() );
		EXPECT_TRUE( tk1.isHexInteger() );
		EXPECT_FALSE( tk1.wasQuoted() );
	}
	{
		QString	s( "'a' " );
		AaTkString aas = AaTokenizer::basicTk( s );
		EXPECT_FALSE( aas.s_.isEmpty() );
		EXPECT_EQ( aas.s_, s );
		EXPECT_EQ( aas.tk_.count(), 1 );
		const AaToken & tk1 = aas.tk_.at( 0 );
		EXPECT_EQ( tk1.i_start, 1 );
		EXPECT_EQ( tk1.i_end, 2 );
		EXPECT_FALSE( tk1.isAllWhite() );
		EXPECT_FALSE( tk1.leadingWhite() );
		EXPECT_FALSE( tk1.trailingWhite() );
		EXPECT_FALSE( tk1.middleWhite() );
		EXPECT_FALSE( tk1.hasWhiteSpaces() );
		EXPECT_FALSE( tk1.hasDigits() );
		EXPECT_TRUE( tk1.hasLetters() );
		EXPECT_FALSE( tk1.hasComma() );
		EXPECT_FALSE( tk1.hasDot() );
		EXPECT_FALSE( tk1.isInteger() );
		EXPECT_TRUE( tk1.isHexInteger() );
		EXPECT_TRUE( tk1.wasQuoted() );
	}
	{
		QString	s( "'' " );
		AaTkString aas = AaTokenizer::basicTk( s );
		EXPECT_FALSE( aas.s_.isEmpty() );
		EXPECT_EQ( aas.s_, s );
		EXPECT_EQ( aas.tk_.count(), 1 );
		const AaToken & tk1 = aas.tk_.at( 0 );
		EXPECT_EQ( tk1.i_start, 1 );
		EXPECT_EQ( tk1.i_end, 1 );
		EXPECT_FALSE( tk1.isAllWhite() );
		EXPECT_FALSE( tk1.leadingWhite() );
		EXPECT_FALSE( tk1.trailingWhite() );
		EXPECT_FALSE( tk1.middleWhite() );
		EXPECT_FALSE( tk1.hasWhiteSpaces() );
		EXPECT_FALSE( tk1.hasDigits() );
		EXPECT_FALSE( tk1.hasLetters() );
		EXPECT_FALSE( tk1.hasComma() );
		EXPECT_FALSE( tk1.hasDot() );
		EXPECT_FALSE( tk1.isInteger() );
		EXPECT_FALSE( tk1.isHexInteger() );
		EXPECT_TRUE( tk1.wasQuoted() );
	}
	endAprilLibrary();
}

TEST(AaTokenizer, three_letters) {
	
	initAprilLibrary();
	{
		QString	s(" a b c ");
		AaTkString aas = AaTokenizer::basicTk( s );
		EXPECT_FALSE( aas.s_.isEmpty() );
		EXPECT_EQ( aas.s_, s );
		EXPECT_EQ( aas.tk_.count(), 3 );
		const AaToken & tk1 = aas.tk_.at( 0 );
		const AaToken & tk2 = aas.tk_.at( 1 );
		const AaToken & tk3 = aas.tk_.at( 2 );
		
		EXPECT_EQ( tk1.i_start, 1 );
		EXPECT_EQ( tk1.i_end, 2 );
		EXPECT_FALSE( tk1.isAllWhite() );
		EXPECT_FALSE( tk1.leadingWhite() );
		EXPECT_FALSE( tk1.trailingWhite() );
		EXPECT_FALSE( tk1.middleWhite() );
		EXPECT_FALSE( tk1.hasWhiteSpaces() );
		EXPECT_FALSE( tk1.hasDigits() );
		EXPECT_TRUE( tk1.hasLetters() );
		EXPECT_FALSE( tk1.hasComma() );
		EXPECT_FALSE( tk1.hasDot() );
		EXPECT_FALSE( tk1.isInteger() );
		EXPECT_TRUE( tk1.isHexInteger() );
		EXPECT_FALSE( tk1.wasQuoted() );
		
		EXPECT_EQ( tk2.i_start, 3 );
		EXPECT_EQ( tk2.i_end, 4 );
		EXPECT_FALSE( tk2.isAllWhite() );
		EXPECT_FALSE( tk2.leadingWhite() );
		EXPECT_FALSE( tk2.trailingWhite() );
		EXPECT_FALSE( tk2.middleWhite() );
		EXPECT_FALSE( tk2.hasWhiteSpaces() );
		EXPECT_FALSE( tk2.hasDigits() );
		EXPECT_TRUE( tk2.hasLetters() );
		EXPECT_FALSE( tk2.hasComma() );
		EXPECT_FALSE( tk2.hasDot() );
		EXPECT_FALSE( tk2.isInteger() );
		EXPECT_TRUE( tk2.isHexInteger() );
		EXPECT_FALSE( tk2.wasQuoted() );
		
		EXPECT_EQ( tk3.i_start, 5 );
		EXPECT_EQ( tk3.i_end, 6 );
		EXPECT_FALSE( tk3.isAllWhite() );
		EXPECT_FALSE( tk3.leadingWhite() );
		EXPECT_FALSE( tk3.trailingWhite() );
		EXPECT_FALSE( tk3.middleWhite() );
		EXPECT_FALSE( tk3.hasWhiteSpaces() );
		EXPECT_FALSE( tk3.hasDigits() );
		EXPECT_TRUE( tk3.hasLetters() );
		EXPECT_FALSE( tk3.hasComma() );
		EXPECT_FALSE( tk3.hasDot() );
		EXPECT_FALSE( tk3.isInteger() );
		EXPECT_TRUE( tk3.isHexInteger() );
		EXPECT_FALSE( tk3.wasQuoted() );
	}
	{
		QString	s(" \t\t\n  \"a\" 'b' \"c\" \t\t\n ");
		AaTkString aas = AaTokenizer::basicTk( s );
		EXPECT_FALSE( aas.s_.isEmpty() );
		EXPECT_EQ( aas.s_, s );
		EXPECT_EQ( aas.tk_.count(), 3 );
		const AaToken & tk1 = aas.tk_.at( 0 );
		const AaToken & tk2 = aas.tk_.at( 1 );
		const AaToken & tk3 = aas.tk_.at( 2 );
		
		EXPECT_EQ( tk1.i_start, 7 );
		EXPECT_EQ( tk1.i_end, 8 );
		EXPECT_FALSE( tk1.isAllWhite() );
		EXPECT_FALSE( tk1.leadingWhite() );
		EXPECT_FALSE( tk1.trailingWhite() );
		EXPECT_FALSE( tk1.middleWhite() );
		EXPECT_FALSE( tk1.hasWhiteSpaces() );
		EXPECT_FALSE( tk1.hasDigits() );
		EXPECT_TRUE( tk1.hasLetters() );
		EXPECT_FALSE( tk1.hasComma() );
		EXPECT_FALSE( tk1.hasDot() );
		EXPECT_FALSE( tk1.isInteger() );
		EXPECT_TRUE( tk1.isHexInteger() );
		EXPECT_TRUE( tk1.wasQuoted() );
		
		EXPECT_EQ( tk2.i_start, 11 );
		EXPECT_EQ( tk2.i_end, 12 );
		EXPECT_FALSE( tk2.isAllWhite() );
		EXPECT_FALSE( tk2.leadingWhite() );
		EXPECT_FALSE( tk2.trailingWhite() );
		EXPECT_FALSE( tk2.middleWhite() );
		EXPECT_FALSE( tk2.hasWhiteSpaces() );
		EXPECT_FALSE( tk2.hasDigits() );
		EXPECT_TRUE( tk2.hasLetters() );
		EXPECT_FALSE( tk2.hasComma() );
		EXPECT_FALSE( tk2.hasDot() );
		EXPECT_FALSE( tk2.isInteger() );
		EXPECT_TRUE( tk2.isHexInteger() );
		EXPECT_TRUE( tk2.wasQuoted() );
		
		EXPECT_EQ( tk3.i_start, 15 );
		EXPECT_EQ( tk3.i_end, 16 );
		EXPECT_FALSE( tk3.isAllWhite() );
		EXPECT_FALSE( tk3.leadingWhite() );
		EXPECT_FALSE( tk3.trailingWhite() );
		EXPECT_FALSE( tk3.middleWhite() );
		EXPECT_FALSE( tk3.hasWhiteSpaces() );
		EXPECT_FALSE( tk3.hasDigits() );
		EXPECT_TRUE( tk3.hasLetters() );
		EXPECT_FALSE( tk3.hasComma() );
		EXPECT_FALSE( tk3.hasDot() );
		EXPECT_FALSE( tk3.isInteger() );
		EXPECT_TRUE( tk3.isHexInteger() );
		EXPECT_TRUE( tk3.wasQuoted() );
	}
	endAprilLibrary();
}

TEST(AaTokenizer, whites_and_letters) {
	
	initAprilLibrary();
	{
		QString	s("' a b '");
		AaTkString aas = AaTokenizer::basicTk( s );
		EXPECT_FALSE( aas.s_.isEmpty() );
		EXPECT_EQ( aas.s_, s );
		EXPECT_EQ( aas.tk_.count(), 1 );
		const AaToken & tk1 = aas.tk_.at( 0 );
		EXPECT_EQ( tk1.i_start, 1 );
		EXPECT_EQ( tk1.i_end, 6 );
		EXPECT_FALSE( tk1.isAllWhite() );
		EXPECT_TRUE( tk1.leadingWhite() );
		EXPECT_TRUE( tk1.trailingWhite() );
		EXPECT_TRUE( tk1.middleWhite() );
		EXPECT_TRUE( tk1.hasWhiteSpaces() );
		EXPECT_FALSE( tk1.hasDigits() );
		EXPECT_TRUE( tk1.hasLetters() );
		EXPECT_FALSE( tk1.hasComma() );
		EXPECT_FALSE( tk1.hasDot() );
		EXPECT_FALSE( tk1.isInteger() );
		EXPECT_FALSE( tk1.isHexInteger() );
		EXPECT_TRUE( tk1.wasQuoted() );
	}
	{
		QString	s("'a b '");
		AaTkString aas = AaTokenizer::basicTk( s );
		EXPECT_FALSE( aas.s_.isEmpty() );
		EXPECT_EQ( aas.s_, s );
		EXPECT_EQ( aas.tk_.count(), 1 );
		const AaToken & tk1 = aas.tk_.at( 0 );
		EXPECT_EQ( tk1.i_start, 1 );
		EXPECT_EQ( tk1.i_end, 5 );
		EXPECT_FALSE( tk1.isAllWhite() );
		EXPECT_FALSE( tk1.leadingWhite() );
		EXPECT_TRUE( tk1.trailingWhite() );
		EXPECT_TRUE( tk1.middleWhite() );
		EXPECT_TRUE( tk1.hasWhiteSpaces() );
		EXPECT_FALSE( tk1.hasDigits() );
		EXPECT_TRUE( tk1.hasLetters() );
		EXPECT_FALSE( tk1.hasComma() );
		EXPECT_FALSE( tk1.hasDot() );
		EXPECT_FALSE( tk1.isInteger() );
		EXPECT_FALSE( tk1.isHexInteger() );
		EXPECT_TRUE( tk1.wasQuoted() );
	}
	{
		QString	s("' a b'");
		AaTkString aas = AaTokenizer::basicTk( s );
		EXPECT_FALSE( aas.s_.isEmpty() );
		EXPECT_EQ( aas.s_, s );
		EXPECT_EQ( aas.tk_.count(), 1 );
		const AaToken & tk1 = aas.tk_.at( 0 );
		EXPECT_EQ( tk1.i_start, 1 );
		EXPECT_EQ( tk1.i_end, 5 );
		EXPECT_FALSE( tk1.isAllWhite() );
		EXPECT_TRUE( tk1.leadingWhite() );
		EXPECT_FALSE( tk1.trailingWhite() );
		EXPECT_TRUE( tk1.middleWhite() );
		EXPECT_TRUE( tk1.hasWhiteSpaces() );
		EXPECT_FALSE( tk1.hasDigits() );
		EXPECT_TRUE( tk1.hasLetters() );
		EXPECT_FALSE( tk1.hasComma() );
		EXPECT_FALSE( tk1.hasDot() );
		EXPECT_FALSE( tk1.isInteger() );
		EXPECT_FALSE( tk1.isHexInteger() );
		EXPECT_TRUE( tk1.wasQuoted() );
	}
	{
		QString	s("' ab '");
		AaTkString aas = AaTokenizer::basicTk( s );
		EXPECT_FALSE( aas.s_.isEmpty() );
		EXPECT_EQ( aas.s_, s );
		EXPECT_EQ( aas.tk_.count(), 1 );
		const AaToken & tk1 = aas.tk_.at( 0 );
		EXPECT_EQ( tk1.i_start, 1 );
		EXPECT_EQ( tk1.i_end, 5 );
		EXPECT_FALSE( tk1.isAllWhite() );
		EXPECT_TRUE( tk1.leadingWhite() );
		EXPECT_TRUE( tk1.trailingWhite() );
		EXPECT_FALSE( tk1.middleWhite() );
		EXPECT_TRUE( tk1.hasWhiteSpaces() );
		EXPECT_FALSE( tk1.hasDigits() );
		EXPECT_TRUE( tk1.hasLetters() );
		EXPECT_FALSE( tk1.hasComma() );
		EXPECT_FALSE( tk1.hasDot() );
		EXPECT_FALSE( tk1.isInteger() );
		EXPECT_FALSE( tk1.isHexInteger() );
		EXPECT_TRUE( tk1.wasQuoted() );
	}
	
	endAprilLibrary();
}

TEST(AaTokenizer, whites) {
	
	initAprilLibrary();
	{
		QString	s("'  '");
		AaTkString aas = AaTokenizer::basicTk( s );
		EXPECT_FALSE( aas.s_.isEmpty() );
		EXPECT_EQ( aas.s_, s );
		EXPECT_EQ( aas.tk_.count(), 1 );
		const AaToken & tk1 = aas.tk_.at( 0 );
		EXPECT_EQ( tk1.i_start, 1 );
		EXPECT_EQ( tk1.i_end, 3 );
		EXPECT_TRUE( tk1.isAllWhite() );
		EXPECT_TRUE( tk1.leadingWhite() );
		EXPECT_TRUE( tk1.trailingWhite() );
		EXPECT_TRUE( tk1.middleWhite() );
		EXPECT_TRUE( tk1.hasWhiteSpaces() );
		EXPECT_FALSE( tk1.hasDigits() );
		EXPECT_FALSE( tk1.hasLetters() );
		EXPECT_FALSE( tk1.hasComma() );
		EXPECT_FALSE( tk1.hasDot() );
		EXPECT_FALSE( tk1.isInteger() );
		EXPECT_FALSE( tk1.isHexInteger() );
		EXPECT_TRUE( tk1.wasQuoted() );
	}
	{
		QString	s("' \n\t\r '");
		AaTkString aas = AaTokenizer::basicTk( s );
		EXPECT_FALSE( aas.s_.isEmpty() );
		EXPECT_EQ( aas.s_, s );
		EXPECT_EQ( aas.tk_.count(), 1 );
		const AaToken & tk1 = aas.tk_.at( 0 );
		EXPECT_EQ( tk1.i_start, 1 );
		EXPECT_EQ( tk1.i_end, 6 );
		EXPECT_TRUE( tk1.isAllWhite() );
		EXPECT_TRUE( tk1.leadingWhite() );
		EXPECT_TRUE( tk1.trailingWhite() );
		EXPECT_TRUE( tk1.middleWhite() );
		EXPECT_TRUE( tk1.hasWhiteSpaces() );
		EXPECT_FALSE( tk1.hasDigits() );
		EXPECT_FALSE( tk1.hasLetters() );
		EXPECT_FALSE( tk1.hasComma() );
		EXPECT_FALSE( tk1.hasDot() );
		EXPECT_FALSE( tk1.isInteger() );
		EXPECT_FALSE( tk1.isHexInteger() );
		EXPECT_TRUE( tk1.wasQuoted() );
	}
	
	endAprilLibrary();
}



