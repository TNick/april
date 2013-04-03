#include	<gtest/gtest.h>
#include	<april/aprillibrary.h>
#include	<april/logic/world.h>
#include	<april/logic/actor.h>
#include	<april/logic/actorfactory.h>
#include	<april/logic/brain.h>
#include	<april/logic/brainfactory.h>
#include	<april/logic/actuator.h>
#include	<april/logic/actuatorfactory.h>
#include	<april/logic/reflex.h>
#include	<april/logic/reflexfactory.h>
#include	<april/logic/sensor.h>
#include	<april/logic/sensorfactory.h>


using namespace april;

TEST(Actor, init) {

	initAprilLibrary();
	World * w = new World( "test-world", 1000 );
	DEC_REF( w, w );

	Actor * ag = new Actor( w );
	DEC_REF(ag,ag);
	EXPECT_TRUE( ag->firstSensor() == NULL );
	EXPECT_TRUE( ag->firstActuator() == NULL );
	EXPECT_TRUE( ag->firstReflex() == NULL );
	EXPECT_TRUE( ag->firstBrain() == NULL );
	EXPECT_EQ( ag->kind(), InvalidId );
	EXPECT_EQ( ag->kindName(), QString() );
	EXPECT_EQ( ag->birth(), (quint64)0 );
	EXPECT_EQ( ag->death(), (quint64)0 );
	EXPECT_EQ( ag->age(), (quint64)0 );
	EXPECT_EQ( ag->toLive(), (quint64)0 );
	EXPECT_EQ( ag->energy(), (quint64)0 );
	EXPECT_EQ( ag->cost(), (quint64)0 );
	EXPECT_EQ( ag->isAlive(), false );
	EXPECT_EQ( ag->dies(), true );
	EXPECT_TRUE( ag->payload().p_ == NULL );
	
	endAprilLibrary();
}

enum TestIds {
	TestIdKind = 1,
	TestIdBrain,
	TestIdReflex,
	TestIdActuator,
	TestIdSensor
};

class BrainTstFactA : public BrainFactory {
public:
	BrainTstFactA( World * w ): BrainFactory( w ) {
		w->insertId( TestIdBrain, "brains.test" );
		addMyself( TestIdBrain );
	}
	virtual Brain * create ( Actor * a, ID id ) {
		Q_UNUSED( id );
		Brain * ret = new Brain( a );
		return ret;
	}
};

class ActuatorTstFactA : public ActuatorFactory {
public:
	ActuatorTstFactA( World * w ): ActuatorFactory( w ) {
		w->insertId( TestIdActuator, "actuators.test" );
		addMyself( TestIdActuator );
	}
	virtual Actuator * create ( Actor * a, ID id ) {
		Q_UNUSED( id );
		Actuator * ret = new Actuator( a );
		return ret;
	}
};

class ReflexTstFactA : public ReflexFactory {
public:
	ReflexTstFactA( World * w ): ReflexFactory( w ) {
		w->insertId( TestIdReflex, "reflexes.test" );
		addMyself( TestIdReflex );
	}
	virtual Reflex * create ( Actor * a, ID id ) {
		Q_UNUSED( id );
		Reflex * ret = new Reflex( a );
		return ret;
	}
};

class SensorTstFactA : public SensorFactory {
public:
	SensorTstFactA( World * w ): SensorFactory( w ) {
		w->insertId( TestIdSensor, "sensors.test" );
		addMyself( TestIdSensor );
	}
	virtual Sensor * create ( Actor * a, ID id ) {
		Q_UNUSED( id );
		Sensor * ret = new Sensor( a );
		return ret;
	}
};


class TstFactA : public ActorFactory	{
public:
	
	TstFactA( World * w ) : ActorFactory( w ) {
		w->insertId( TestIdKind, "kinds.test" );
		addMyself( TestIdKind );
		initDNA( TestIdKind );
		EXPECT_TRUE( defaultDNA().addBrain( TestIdBrain) );
		EXPECT_TRUE( defaultDNA().addActuator( TestIdActuator ) );
		EXPECT_TRUE( defaultDNA().addReflex( TestIdReflex ) );
		EXPECT_TRUE( defaultDNA().addSensor( TestIdSensor ) );
	}
	virtual Actor * create ( ID id ) {
		Q_UNUSED( id );
		Q_ASSERT( id == TestIdKind );
		/* create new instance that gets inserted in the world */
		Actor * ret = new Actor( world() ); 
		/* set a default dan */
		setDNA( ret );
		return ret;
	}
	virtual void copyDefaultDNA ( DNA & destination ) { 
		destination = defaultDNA();
	}

};

TEST(Actor, factory) {
	
	initAprilLibrary();
	World * w = new World( __FUNCTION__, 1000 );
	DEC_REF( w, w );
	
	BrainTstFactA * bf = new BrainTstFactA( w );
	DEC_REF( bf, bf );
	ActuatorTstFactA * af = new ActuatorTstFactA( w );
	DEC_REF( af, af );
	ReflexTstFactA * rf = new ReflexTstFactA( w );
	DEC_REF( rf, rf );
	SensorTstFactA * sf = new SensorTstFactA( w );
	DEC_REF( sf, sf );
	
	TstFactA * fact = new TstFactA( w );
	DEC_REF( fact, fact );
	
	Actor * a = w->createActor( TestIdKind );
	EXPECT_TRUE( a != NULL );
	EXPECT_EQ( a->kind(), TestIdKind );
	EXPECT_EQ( a->kindName(), "kinds.test" );
	EXPECT_TRUE( a->firstSensor() != NULL );
	EXPECT_TRUE( a->firstActuator() != NULL );
	EXPECT_TRUE( a->firstReflex() != NULL );
	EXPECT_TRUE( a->firstBrain() != NULL );
	
	Brain * b = a->firstBrain();
	EXPECT_TRUE( b->next() == NULL );
	EXPECT_TRUE( b->prev() == NULL );
	EXPECT_TRUE( b->actor() == a );
	
	Actuator * ct = a->firstActuator();
	EXPECT_TRUE( ct->next() == NULL );
	EXPECT_TRUE( ct->prev() == NULL );
	EXPECT_TRUE( ct->actor() == a );

	Reflex * r = a->firstReflex();
	EXPECT_TRUE( r->next() == NULL );
	EXPECT_TRUE( r->prev() == NULL );
	EXPECT_TRUE( r->actor() == a );

	Sensor * s = a->firstSensor();
	EXPECT_TRUE( s->next() == NULL );
	EXPECT_TRUE( s->prev() == NULL );
	EXPECT_TRUE( s->actor() == a );
	
	endAprilLibrary();
}





