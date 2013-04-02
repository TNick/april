#include	<gtest/gtest.h>
#include	<april/aprillibrary.h>
#include	<april/logic/dna.h>
#include	<april/logic/dnaview.h>

using namespace april;

TEST(DNA, basic) {
	initAprilLibrary();

	DNA		dna; // default invalid instance
	EXPECT_EQ( dna.isValid(), false );
	EXPECT_EQ( dna.kind(), InvalidId );
	EXPECT_EQ( dna.brains().length(), 0 );
	EXPECT_EQ( dna.actuators().length(), 0 );
	EXPECT_EQ( dna.sensors().length(), 0 );
	EXPECT_EQ( dna.reflexes().length(), 0 );
	
	EXPECT_EQ( dna.getView( InvalidId ).isValid(), false );
	EXPECT_EQ( dna.getView( 0 ).isValid(), false );
	EXPECT_EQ( dna.getView( 1 ).isValid(), false );
	EXPECT_EQ( dna.getView( 2 ).isValid(), false );



	endAprilLibrary();
}
