#include	<gtest/gtest.h>
#include	<april/aprillibrary.h>
#include	<april/logic/world.h>
#include	<april/logic/actor.h>
#include	<april/logic/actorfactory.h>
#include	<april/logic/actuator.h>
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


enum TestIds {
	TestIdKind = 1,
	TestIdActuator = 2
};

class ActuatorTstFact : public ActuatorFactory {
public:
	ActuatorTstFact( World * w ): ActuatorFactory( w ) {
		w->insertId( TestIdActuator, "actuators.test" );
		addMyself( TestIdActuator );
	}
	virtual Actuator * create ( Actor * a, ID id ) {
		Q_UNUSED( id );
		Actuator * ret = new Actuator( a );
		return ret;
	}
};

class ActorActuatorTstFact : public ActorFactory {
public:
	ActorActuatorTstFact( World * w ) : ActorFactory( w ) {
		w->insertId( TestIdKind, "kinds.test" );
		addMyself( TestIdKind );
		initDNA( TestIdKind );
		EXPECT_TRUE( defaultDNA().addActuator( TestIdActuator ) );
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

TEST(Actuator, factory) {
	initAprilLibrary();

	World * w = new World( __FUNCTION__, 1000 );
	DEC_REF( w, w );

	ActuatorTstFact * actuator_fact = new ActuatorTstFact( w );
	DEC_REF( actuator_fact, actuator_fact );
	
	ActorActuatorTstFact * actor_fact = new ActorActuatorTstFact( w );
	DEC_REF( actor_fact, actor_fact );
	
	Actor * a = w->createActor( TestIdKind );
	DEC_REF( a, a );
	EXPECT_TRUE( a != NULL );
	EXPECT_TRUE( a->firstSensor() == NULL );
	EXPECT_TRUE( a->firstReflex() == NULL );
	EXPECT_TRUE( a->firstBrain() == NULL );
	EXPECT_TRUE( a->firstActuator() != NULL );
	EXPECT_EQ( a->kind(), TestIdKind );
	EXPECT_EQ( a->kindName(), "kinds.test" );

	Actuator * r = a->firstActuator();
	EXPECT_TRUE( r->next() == NULL );
	EXPECT_TRUE( r->prev() == NULL );
	EXPECT_TRUE( r->actor() == a );
	
	endAprilLibrary();
}
