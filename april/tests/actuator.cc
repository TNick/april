#include	<gtest/gtest.h>
#include	<april/aprillibrary.h>
#include	<april/logic/world.h>
#include	<april/logic/actuator.h>
#include	<april/logic/actor.h>
#include	<april/logic/actuatorfactory.h>

using namespace april;

TEST(Actuator, init) {

	initAprilLibrary();
	World * w = new World( "test-world", 1000 );
	DEC_REF( w, w );
	
	Actor * ag = new Actor( w );
	DEC_REF(ag,ag);
	Actuator * act = new Actuator( ag );
	DEC_REF(act,act);
	
	
	endAprilLibrary();
}

