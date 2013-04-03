#include	<gtest/gtest.h>
#include	<april/aprillibrary.h>
#include	<april/logic/world.h>
#include	<april/logic/actor.h>
#include	<april/logic/brain.h>
#include	<april/logic/brainfactory.h>
#include	<april/logic/actor.h>
#include	<april/logic/actorfactory.h>

using namespace april;

TEST(Brain, init) {

	initAprilLibrary();
	World * w = new World( __FUNCTION__, 1000 );
	DEC_REF( w, w );
	
	Actor * a = new Actor( w );
	DEC_REF(a,a);
	Brain * act = new Brain( a );
	DEC_REF(act,act);
	
	
	endAprilLibrary();
}

enum TestIds {
	TestIdKind = 1,
	TestIdBrain = 2
};

class BrainTstFact : public BrainFactory {
public:
	BrainTstFact( World * w ): BrainFactory( w ) {
		w->insertId( TestIdBrain, "brains.test" );
		addMyself( TestIdBrain );
	}
	virtual Brain * create ( Actor * a, ID id ) {
		Q_UNUSED( id );
		Brain * ret = new Brain( a );
		
		return ret;
	}
};

class ActorTstFact : public ActorFactory {
public:
	ActorTstFact( World * w ) : ActorFactory( w ) {
		w->insertId( TestIdKind, "kinds.test" );
		addMyself( TestIdKind );
		initDNA( TestIdKind );
		EXPECT_TRUE( defaultDNA().addBrain( TestIdBrain ) );
	}
	virtual Actor * create ( ID id ) {
		Q_UNUSED( id );
		Q_ASSERT( id == TestIdKind );
		Actor * ret = new Actor( world() );
		setDNA( ret );
		return ret;
	}
	virtual void copyDefaultDNA ( DNA & destination ) { 
		destination = defaultDNA();
	}
};

TEST(Brain, factory) {
	initAprilLibrary();

	World * w = new World( __FUNCTION__, 1000 );
	DEC_REF( w, w );

	BrainTstFact * brain_fact = new BrainTstFact( w );
	DEC_REF( brain_fact, brain_fact );
	
	ActorTstFact * actor_fact = new ActorTstFact( w );
	DEC_REF( actor_fact, actor_fact );
	
	Actor * a = w->createActor( TestIdKind );
	DEC_REF( a, a );
	EXPECT_TRUE( a != NULL );
	EXPECT_TRUE( a->firstSensor() == NULL );
	EXPECT_TRUE( a->firstActuator() == NULL );
	EXPECT_TRUE( a->firstReflex() == NULL );
	EXPECT_TRUE( a->firstBrain() != NULL );
	EXPECT_EQ( a->kind(), TestIdKind );
	EXPECT_EQ( a->kindName(), "kinds.test" );

	Brain * b = a->firstBrain();
	EXPECT_TRUE( b->next() == NULL );
	EXPECT_TRUE( b->prev() == NULL );
	EXPECT_TRUE( b->actor() == a );
	
	endAprilLibrary();
}
