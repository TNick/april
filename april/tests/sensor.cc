#include	<gtest/gtest.h>
#include	<april/aprillibrary.h>
#include	<april/logic/world.h>
#include	<april/logic/actor.h>
#include	<april/logic/actorfactory.h>
#include	<april/logic/sensor.h>
#include	<april/logic/sensorfactory.h>

using namespace april;

TEST(Sensor, init) {

	initAprilLibrary();
	World * w = new World( "test-world", 1000 );
	DEC_REF( w, w );
	
	Actor * ag = new Actor( w );
	DEC_REF(ag,ag);
	Sensor * act = new Sensor( ag );
	DEC_REF(act,act);
	
	
	endAprilLibrary();
}


enum TestIds {
	TestIdKind = 1,
	TestIdSensor = 2
};

class SensorTstFact : public SensorFactory {
public:
	SensorTstFact( World * w ): SensorFactory( w ) {
		w->insertId( TestIdSensor, "sensors.test" );
		addMyself( TestIdSensor );
	}
	virtual Sensor * create ( Actor * a, ID id ) {
		Q_UNUSED( id );
		Sensor * ret = new Sensor( a );
		return ret;
	}
};

class ActorSensorTstFact : public ActorFactory {
public:
	ActorSensorTstFact( World * w ) : ActorFactory( w ) {
		w->insertId( TestIdKind, "kinds.test" );
		addMyself( TestIdKind );
		initDNA( TestIdKind );
		EXPECT_TRUE( defaultDNA().addSensor( TestIdSensor ) );
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

TEST(Sensor, factory) {
	initAprilLibrary();

	World * w = new World( __FUNCTION__, 1000 );
	DEC_REF( w, w );

	SensorTstFact * sensor_fact = new SensorTstFact( w );
	DEC_REF( sensor_fact, sensor_fact );
	
	ActorSensorTstFact * actor_fact = new ActorSensorTstFact( w );
	DEC_REF( actor_fact, actor_fact );
	
	Actor * a = w->createActor( TestIdKind );
	DEC_REF( a, a );
	EXPECT_TRUE( a != NULL );
	EXPECT_TRUE( a->firstReflex() == NULL );
	EXPECT_TRUE( a->firstActuator() == NULL );
	EXPECT_TRUE( a->firstBrain() == NULL );
	EXPECT_TRUE( a->firstSensor() != NULL );
	EXPECT_EQ( a->kind(), TestIdKind );
	EXPECT_EQ( a->kindName(), "kinds.test" );

	Sensor * r = a->firstSensor();
	EXPECT_TRUE( r->next() == NULL );
	EXPECT_TRUE( r->prev() == NULL );
	EXPECT_TRUE( r->actor() == a );
	
	endAprilLibrary();
}
