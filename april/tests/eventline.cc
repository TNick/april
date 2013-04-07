#include	<gtest/gtest.h>
#include	<april/aprillibrary.h>
#include	<april/logic/world.h>
#include	<april/logic/actuator.h>
#include	<april/logic/eventsource.h>
#include	<april/logic/eventfactory.h>
#include	<april/logic/eventline.h>
#include	<april/logic/eventdata.h>

using namespace april;

/* ----------------------------------------------------- */
namespace	eventline_cc		{

enum Ids {
	IdKind = 1,
	IdBrain,
	IdReflex,
	IdActuator,
	IdSensor,
	IdSound
};

}	/* namespace eventline_cc */
/* ----------------------------------------------------- */

TEST(EventLine, factory) {

	initAprilLibrary();
	World * w = new World( "test-world", 1000 );
	DEC_REF( w, w );
	w->insertId( eventline_cc::IdSound, "eventline.sound" );
	EventLine * el = new EventLine( w, eventline_cc::IdSound );
	DEC_REF( el, el );
	EventData * ed = new EventData( w, 4 );
	
	w->start();
	
	EXPECT_EQ( el->dataCount(), (unsigned int)0 );
	EXPECT_TRUE( el->firstEventData() == NULL );
	EXPECT_TRUE( el->lastEventData() == NULL );

	el->postActivity( ed );
	
	EXPECT_TRUE( el->world() == w );
	EXPECT_TRUE( el->identificator() == eventline_cc::IdSound );
	EXPECT_EQ( el->dataCount(), (unsigned int)1 );
	EXPECT_TRUE( el->firstEventData() == ed );
	EXPECT_TRUE( el->lastEventData() == ed );
	
	for ( int i = 0; i < 3; i++ )
	{
		w->advance();
		EXPECT_EQ( el->dataCount(), (unsigned int)1 );
		EXPECT_TRUE( el->firstEventData() == ed );
		EXPECT_TRUE( el->lastEventData() == ed );
	}
	w->advance();
	EXPECT_EQ( el->dataCount(), (unsigned int)0 );
	EXPECT_TRUE( el->firstEventData() == NULL );
	EXPECT_TRUE( el->lastEventData() == NULL );
	
	w->stop();
	
	DEC_REF( ed, ed );
	
	endAprilLibrary();
}




