#include	<gtest/gtest.h>
#include	<april/aprillibrary.h>
#include	<april/logic/world.h>
#include	<april/logic/actor.h>
#include	<april/logic/reflex.h>
#include	<april/logic/reflexfactory.h>

using namespace april;

TEST(Reflex, init) {

	initAprilLibrary();
	World * w = new World( "test-world", 1000 );
	DEC_REF( w, w );
	
	Actor * ag = new Actor( w );
	DEC_REF(ag,ag);
	Reflex * act = new Reflex( ag );
	DEC_REF(act,act);
	
	
	endAprilLibrary();
}

