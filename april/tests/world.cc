
#include	<gtest/gtest.h>
#include	<april/aprillibrary.h>
#include	<april/logic/world.h>

using namespace april;

TEST(World, add_remove) {

	// not initialised
	EXPECT_TRUE( AprilLibrary::unique() == NULL );

	bool b = initAprilLibrary();
	EXPECT_TRUE( b);
	
	// create an world
	World * ag = new World();
	ag->decRef();
	EXPECT_TRUE( AprilLibrary::hasWorld( ag ) );

	EXPECT_FALSE( ag->isRunning() );

	// start the world
	ag->start();

	EXPECT_TRUE( ag->isRunning() );

	// stop the world
	ag->stop();

	EXPECT_FALSE( ag->isRunning() );

	// destroy the world
	AprilLibrary::remWorld( ag );

	endAprilLibrary();
}

