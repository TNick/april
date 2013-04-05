#include	<gtest/gtest.h>
#include	<april/aprillibrary.h>
#include	<april/logic/world.h>
#include	<april/logic/actor.h>
#include	<april/logic/actorfactory.h>
#include	<april/logic/reflex.h>
#include	<april/logic/reflexfactory.h>

using namespace april;

/* ----------------------------------------------------- */
namespace	reflex_cc		{


enum Ids {
	IdKind = 1,
	IdReflex = 2
};

class FRefx : public ReflexFactory {
public:
	FRefx( World * w ): ReflexFactory( w ) {
		w->insertId( IdReflex, "reflexes.test" );
		addMyself( IdReflex );
	}
	virtual Reflex * create ( Actor * a, ID id ) {
		Q_UNUSED( id );
		Reflex * ret = new Reflex( a );
		return ret;
	}
};

class FAgent : public ActorFactory {
public:
	FAgent( World * w ) : ActorFactory( w ) {
		w->insertId( IdKind, "kinds.test" );
		addMyself( IdKind );
		initDNA( IdKind );
		EXPECT_TRUE( defaultDNA().addReflex( IdReflex ) );
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

}	/* namespace reflex_cc */
/* ----------------------------------------------------- */

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

TEST(Reflex, factory) {
	initAprilLibrary();

	World * w = new World( __FUNCTION__, 1000 );
	DEC_REF( w, w );

	reflex_cc::FRefx * reflex_fact = new reflex_cc::FRefx( w );
	DEC_REF( reflex_fact, reflex_fact );
	
	reflex_cc::FAgent * actor_fact = new reflex_cc::FAgent( w );
	DEC_REF( actor_fact, actor_fact );
	
	Actor * a = w->createActor( reflex_cc::IdKind );
	DEC_REF( a, a );
	EXPECT_TRUE( a != NULL );
	EXPECT_TRUE( a->firstSensor() == NULL );
	EXPECT_TRUE( a->firstActuator() == NULL );
	EXPECT_TRUE( a->firstBrain() == NULL );
	EXPECT_TRUE( a->firstReflex() != NULL );
	EXPECT_EQ( a->kind(), reflex_cc::IdKind );
	EXPECT_EQ( a->kindName(), "kinds.test" );

	Reflex * r = a->firstReflex();
	EXPECT_TRUE( r->next() == NULL );
	EXPECT_TRUE( r->prev() == NULL );
	EXPECT_TRUE( r->actor() == a );
	
	endAprilLibrary();
}
