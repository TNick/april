#include	<gtest/gtest.h>
#include	<april/aprillibrary.h>
#include	<april/logic/world.h>
#include	<april/logic/actor.h>
#include	<april/logic/brain.h>
#include	<april/logic/brainfactory.h>

using namespace april;

TEST(Brain, init) {

	initAprilLibrary();
	World * w = new World( "test-world", 1000 );
	DEC_REF( w, w );
	
	Actor * ag = new Actor( w );
	DEC_REF(ag,ag);
	Brain * act = new Brain( ag );
	DEC_REF(act,act);
	
	
	endAprilLibrary();
}

