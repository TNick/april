#include	<gtest/gtest.h>
#include	<april/aprillibrary.h>

using namespace april;

TEST(AprilLibrary, initialisation) {
	bool b = initAprilLibrary();
	EXPECT_TRUE( b);
	EXPECT_TRUE( AprilLibrary::unique() != NULL );
	endAprilLibrary();
}
