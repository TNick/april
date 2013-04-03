#include	<gtest/gtest.h>
#include	<april/aprillibrary.h>
#include	<april/logic/world.h>
#include	<april/logic/actuator.h>
#include	<april/logic/event.h>
#include	<april/logic/eventfactory.h>

using namespace april;

TEST(Event, init) {

	initAprilLibrary();
	World * w = new World( "test-world", 1000 );
	DEC_REF( w, w );
	
	Event * act = new Event( w );
	DEC_REF(act,act);
	
	endAprilLibrary();
}

