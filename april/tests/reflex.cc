#include	<gtest/gtest.h>
#include	<april/aprillibrary.h>
#include	<april/logic/world.h>
#include	<april/logic/actor.h>
#include	<april/logic/actorfactory.h>
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

enum TestIds {
	TestIdKind = 1,
	TestIdReflex = 2
};

class ReflexTstFact : public ReflexFactory {
public:
	ReflexTstFact( World * w ): ReflexFactory( w ) {
		w->insertId( TestIdReflex, "reflexes.test" );
		addMyself( TestIdReflex );
	}
	virtual Reflex * create ( Actor * a, ID id ) {
		Q_UNUSED( id );
		Reflex * ret = new Reflex( a );
		return ret;
	}
};

class ActorReflexTstFact : public ActorFactory {
public:
	ActorReflexTstFact( World * w ) : ActorFactory( w ) {
		w->insertId( TestIdKind, "kinds.test" );
		addMyself( TestIdKind );
		initDNA( TestIdKind );
		EXPECT_TRUE( defaultDNA().addReflex( TestIdReflex ) );
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

TEST(Reflex, factory) {
	initAprilLibrary();

	World * w = new World( __FUNCTION__, 1000 );
	DEC_REF( w, w );

	ReflexTstFact * reflex_fact = new ReflexTstFact( w );
	DEC_REF( reflex_fact, reflex_fact );
	
	ActorReflexTstFact * actor_fact = new ActorReflexTstFact( w );
	DEC_REF( actor_fact, actor_fact );
	
	Actor * a = w->createActor( TestIdKind );
	DEC_REF( a, a );
	EXPECT_TRUE( a != NULL );
	EXPECT_TRUE( a->firstSensor() == NULL );
	EXPECT_TRUE( a->firstActuator() == NULL );
	EXPECT_TRUE( a->firstBrain() == NULL );
	EXPECT_TRUE( a->firstReflex() != NULL );
	EXPECT_EQ( a->kind(), TestIdKind );
	EXPECT_EQ( a->kindName(), "kinds.test" );

	Reflex * r = a->firstReflex();
	EXPECT_TRUE( r->next() == NULL );
	EXPECT_TRUE( r->prev() == NULL );
	EXPECT_TRUE( r->actor() == a );
	
	endAprilLibrary();
}
