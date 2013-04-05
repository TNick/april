#include	<gtest/gtest.h>
#include	<april/aprillibrary.h>
#include	<april/logic/world.h>
#include	<april/logic/actor.h>
#include	<april/logic/actorfactory.h>
#include	<april/logic/brain.h>
#include	<april/logic/brainfactory.h>

using namespace april;

/* ----------------------------------------------------- */
namespace	brain_cc		{

enum Ids {
	IdKind = 1,
	IdBrain = 2
};

class FBrn : public BrainFactory {
public:
	FBrn( World * w ): BrainFactory( w ) {
		w->insertId( IdBrain, "brains.test" );
		addMyself( IdBrain );
	}
	virtual Brain * create ( Actor * a, ID id ) {
		Q_UNUSED( id );
		Brain * ret = new Brain( a );
		return ret;
	}
};

class FAgent : public ActorFactory {
public:
	FAgent( World * w ) : ActorFactory( w ) {
		w->insertId( IdKind, "kinds.test" );
		addMyself( IdKind );
		initDNA( IdKind );
		EXPECT_TRUE( defaultDNA().addBrain( IdBrain ) );
	}
	virtual Actor * create ( ID id ) {
		Q_UNUSED( id );
		Q_ASSERT( id == IdKind );
		Actor * ret = new Actor( world() );
		setDNA( ret );
		return ret;
	}
	virtual void copyDefaultDNA ( DNA & destination ) { 
		destination = defaultDNA();
	}
};

}	/* namespace brain_cc */
/* ----------------------------------------------------- */

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

TEST(Brain, factory) {
	initAprilLibrary();

	World * w = new World( __FUNCTION__, 1000 );
	DEC_REF( w, w );

	brain_cc::FBrn * brain_fact = new brain_cc::FBrn( w );
	DEC_REF( brain_fact, brain_fact );
	
	brain_cc::FAgent * actor_fact = new brain_cc::FAgent( w );
	DEC_REF( actor_fact, actor_fact );
	
	Actor * a = w->createActor( brain_cc::IdKind );
	DEC_REF( a, a );
	EXPECT_TRUE( a != NULL );
	EXPECT_TRUE( a->firstSensor() == NULL );
	EXPECT_TRUE( a->firstActuator() == NULL );
	EXPECT_TRUE( a->firstReflex() == NULL );
	EXPECT_TRUE( a->firstBrain() != NULL );
	EXPECT_EQ( a->kind(), brain_cc::IdKind );
	EXPECT_EQ( a->kindName(), "kinds.test" );

	Brain * b = a->firstBrain();
	EXPECT_TRUE( b->next() == NULL );
	EXPECT_TRUE( b->prev() == NULL );
	EXPECT_TRUE( b->actor() == a );
	
	endAprilLibrary();
}
