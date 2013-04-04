
#include	<gtest/gtest.h>
#include	<april/aprillibrary.h>
#include	<april/logic/world.h>

using namespace april;

TEST(World, running) {

	// not initialised
	EXPECT_TRUE( AprilLibrary::unique() == NULL );

	bool b = initAprilLibrary();
	EXPECT_TRUE( b);
	
	// create an world
	World * w = new World( "test-world", 1000 );
	DEC_REF( w, w );
	EXPECT_TRUE( AprilLibrary::hasWorld( w ) );

	EXPECT_FALSE( w->isRunning() );

	// start the world
	EXPECT_TRUE( w->start() );

	EXPECT_TRUE( w->isRunning() );

	// stop the world
	w->stop();

	EXPECT_FALSE( w->isRunning() );

	// destroy the world
	AprilLibrary::remWorld( w );

	endAprilLibrary();
}

TEST(World, energy) {

	initAprilLibrary();
	World * w = new World( "test-world", 1000 );
	DEC_REF( w, w );
	
	EXPECT_EQ( w->energy(), (quint64)1000 );
	EXPECT_EQ( w->energyFree(), (quint64)1000 );
	EXPECT_EQ( w->energyBounded(), (quint64)0 );
	
	
	endAprilLibrary();
}

TEST(World, time) {


	initAprilLibrary();
	World * w = new World( "test-world", 1000 );
	DEC_REF( w, w );

	EXPECT_EQ( w->currentTime(), (quint64)0 );
	w->advance();
	EXPECT_EQ( w->currentTime(), (quint64)0 );
	w->advance();	
	EXPECT_EQ( w->currentTime(), (quint64)0 );
	EXPECT_TRUE( w->start() );
	EXPECT_EQ( w->currentTime(), (quint64)0 );
	w->advance();
	EXPECT_EQ( w->currentTime(), (quint64)1 );
	w->advance();
	EXPECT_EQ( w->currentTime(), (quint64)2 );
	w->advance();
	EXPECT_EQ( w->currentTime(), (quint64)3 );
	w->stop();
	EXPECT_EQ( w->currentTime(), (quint64)3 );
	w->advance();
	EXPECT_EQ( w->currentTime(), (quint64)3 );
	EXPECT_TRUE( w->start() );
	EXPECT_EQ( w->currentTime(), (quint64)3 );
	w->advance();
	EXPECT_EQ( w->currentTime(), (quint64)4 );
	w->advance();
	EXPECT_EQ( w->currentTime(), (quint64)5 );
	w->stop();
	EXPECT_EQ( w->currentTime(), (quint64)5 );
	
	endAprilLibrary();
}


TEST(World, factories) {
	
	initAprilLibrary();
	World * w = new World( "test-world", 1000 );
	DEC_REF( w, w );

	EXPECT_EQ( w->actorFactories().count(), 0 );
	EXPECT_EQ( w->actuatorFactories().count(), 0 );
	EXPECT_EQ( w->brainFactories().count(), 0 );
	EXPECT_EQ( w->sensorFactories().count(), 0 );
	EXPECT_EQ( w->eventFactories().count(), 0 );

	endAprilLibrary();
	
}

TEST(World, unique_id) {

initAprilLibrary();
	World * w = new World( "test-world", 1000 );
	DEC_REF( w, w );

	EXPECT_EQ( w->idValue( QString() ), InvalidId );
	EXPECT_EQ( w->idValue( "1"), InvalidId );
	EXPECT_EQ( w->idValue( "abcd" ), InvalidId );
	
	EXPECT_EQ( w->nameForId( InvalidId ), QString() );
	EXPECT_EQ( w->nameForId( 0 ), QString() );
	EXPECT_EQ( w->nameForId( 1005 ), QString() );
	
	w->insertId( 1, "test-string" );
	EXPECT_EQ( w->idValue( "test-string" ), (quint64)1 );
	EXPECT_EQ( w->idValue( "TEST-STRING" ), InvalidId );
	EXPECT_EQ( w->nameForId( 1 ), QString("test-string") );
	EXPECT_EQ( w->checkAddId( "test-string" ), (quint64)1 );
	w->insertId( 1, "test-string-2" );
	EXPECT_EQ( w->idValue( "test-string" ), InvalidId );
	EXPECT_EQ( w->idValue( "test-string-2" ), (quint64)1 );
	EXPECT_EQ( w->nameForId( 1 ), QString("test-string-2") );
	EXPECT_EQ( w->checkAddId( "test-string-2" ), (quint64)1 );
	
	endAprilLibrary();
}

/* Actors in dedicated test file */

/* Events in dedicated test file */
