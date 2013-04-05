#include	<gtest/gtest.h>
#include	<april/aprillibrary.h>
#include	<april/logic/world.h>
#include	<april/logic/actor.h>
#include	<april/logic/actorfactory.h>
#include	<april/logic/actuator.h>
#include	<april/logic/actuatorfactory.h>

using namespace april;

/* ----------------------------------------------------- */
namespace	actuator_cc		{

enum Ids {
	IdKind = 1,
	IdActuator = 2
};

class FActu : public ActuatorFactory {
public:
	FActu( World * w ): ActuatorFactory( w ) {
		w->insertId( IdActuator, "actuators.test" );
		addMyself( IdActuator );
	}
	virtual Actuator * create ( Actor * a, ID id ) {
		Q_UNUSED( id );
		Actuator * ret = new Actuator( a );
		return ret;
	}
};

class FAgent : public ActorFactory {
public:
	FAgent( World * w ) : ActorFactory( w ) {
		w->insertId( IdKind, "kinds.test" );
		addMyself( IdKind );
		initDNA( IdKind );
		EXPECT_TRUE( defaultDNA().addActuator( IdActuator ) );
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

}	/* namespace actuator_cc */
/* ----------------------------------------------------- */

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

TEST(Actuator, factory) {
	initAprilLibrary();
	
	World * w = new World( __FUNCTION__, 1000 );
	DEC_REF( w, w );
	
	actuator_cc::FActu * actuator_fact = new actuator_cc::FActu( w );
	DEC_REF( actuator_fact, actuator_fact );
	
	actuator_cc::FAgent * actor_fact = new actuator_cc::FAgent( w );
	DEC_REF( actor_fact, actor_fact );
	
	Actor * a = w->createActor( actuator_cc::IdKind );
	DEC_REF( a, a );
	EXPECT_TRUE( a != NULL );
	EXPECT_TRUE( a->firstSensor() == NULL );
	EXPECT_TRUE( a->firstReflex() == NULL );
	EXPECT_TRUE( a->firstBrain() == NULL );
	EXPECT_TRUE( a->firstActuator() != NULL );
	EXPECT_EQ( a->kind(), actuator_cc::IdKind );
	EXPECT_EQ( a->kindName(), "kinds.test" );
	
	Actuator * r = a->firstActuator();
	EXPECT_TRUE( r->next() == NULL );
	EXPECT_TRUE( r->prev() == NULL );
	EXPECT_TRUE( r->actor() == a );
	
	endAprilLibrary();
}
