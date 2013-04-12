
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



