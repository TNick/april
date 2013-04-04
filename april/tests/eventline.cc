#include	<gtest/gtest.h>
#include	<april/aprillibrary.h>
#include	<april/logic/world.h>
#include	<april/logic/actuator.h>
#include	<april/logic/event.h>
#include	<april/logic/eventfactory.h>
#include	<april/logic/eventline.h>
#include	<april/logic/eventdata.h>

using namespace april;

enum TestIds {
	TestIdKind = 1,
	TestIdBrain,
	TestIdReflex,
	TestIdActuator,
	TestIdSensor,
	TestIdSound
};

TEST(EventLine, factory) {

	initAprilLibrary();
	World * w = new World( "test-world", 1000 );
	DEC_REF( w, w );
	w->insertId( TestIdSound, "eventline.sound" );
	EventLine * el = new EventLine( w, TestIdSound );
	DEC_REF( el, el );
	EventData * ed = new EventData( w, 4 );
	
	w->start();
	
	EXPECT_EQ( el->dataCount(), 0 );
	EXPECT_TRUE( el->firstEventData() == NULL );
	EXPECT_TRUE( el->lastEventData() == NULL );

	el->postActivity( ed );
	
	EXPECT_TRUE( el->world() == w );
	EXPECT_TRUE( el->identificator() == TestIdSound );
	EXPECT_EQ( el->dataCount(), 1 );
	EXPECT_TRUE( el->firstEventData() == ed );
	EXPECT_TRUE( el->lastEventData() == ed );
	
	for ( int i = 0; i < 3; i++ )
	{
		w->advance();
		EXPECT_EQ( el->dataCount(), 1 );
		EXPECT_TRUE( el->firstEventData() == ed );
		EXPECT_TRUE( el->lastEventData() == ed );
	}
	w->advance();
	EXPECT_EQ( el->dataCount(), 0 );
	EXPECT_TRUE( el->firstEventData() == NULL );
	EXPECT_TRUE( el->lastEventData() == NULL );
	
	w->stop();
	
	DEC_REF( ed, ed );
	
	endAprilLibrary();
}




