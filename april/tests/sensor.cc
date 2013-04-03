#include	<gtest/gtest.h>
#include	<april/aprillibrary.h>
#include	<april/logic/world.h>
#include	<april/logic/actor.h>
#include	<april/logic/sensor.h>
#include	<april/logic/sensorfactory.h>

using namespace april;

TEST(Sensor, init) {

	initAprilLibrary();
	World * w = new World( "test-world", 1000 );
	DEC_REF( w, w );
	
	Actor * ag = new Actor( w );
	DEC_REF(ag,ag);
	Sensor * act = new Sensor( ag );
	DEC_REF(act,act);
	
	
	endAprilLibrary();
}

