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


enum TestIds {
	TestIdKind = 1,
	TestIdBrain,
	TestIdReflex,
	TestIdActuator,
	TestIdSensor
};

class BrainTstFactSR : public BrainFactory {
public:
	BrainTstFactSR( World * w ): BrainFactory( w ) {
		w->insertId( TestIdBrain, "brains.test" );
		addMyself( TestIdBrain );
	}
	virtual Brain * create ( Actor * a, ID id ) {
		Q_UNUSED( id );
		Brain * ret = new Brain( a );
		EXPECT_TRUE( setEnergy( ret, 100, 5 ) );
		return ret;
	}
};

class ActuatorTstFactSR : public ActuatorFactory {
public:
	ActuatorTstFactSR( World * w ): ActuatorFactory( w ) {
		w->insertId( TestIdActuator, "actuators.test" );
		addMyself( TestIdActuator );
	}
	virtual Actuator * create ( Actor * a, ID id ) {
		Q_UNUSED( id );
		Actuator * ret = new Actuator( a );
		EXPECT_TRUE( setEnergy( ret, 10, 1 ) );
		return ret;
	}
};

class ReflexTstFactSR : public ReflexFactory {
public:
	ReflexTstFactSR( World * w ): ReflexFactory( w ) {
		w->insertId( TestIdReflex, "reflexes.test" );
		addMyself( TestIdReflex );
	}
	virtual Reflex * create ( Actor * a, ID id ) {
		Q_UNUSED( id );
		Reflex * ret = new Reflex( a );
		EXPECT_TRUE( setEnergy( ret, 10, 1 ) );
		return ret;
	}
};

class SensorTstFactSR : public SensorFactory {
public:
	SensorTstFactSR( World * w ): SensorFactory( w ) {
		w->insertId( TestIdSensor, "sensors.test" );
		addMyself( TestIdSensor );
	}
	virtual Sensor * create ( Actor * a, ID id ) {
		Q_UNUSED( id );
		Sensor * ret = new Sensor( a );
		EXPECT_TRUE( setEnergy( ret, 10, 1 ) );
		return ret;
	}
};

class TstFactSR : public ActorFactory	{
public:
	
	TstFactSR( World * w ) : ActorFactory( w ) {
		w->insertId( TestIdKind, "kinds.test" );
		addMyself( TestIdKind );
		initDNA( TestIdKind );
		
		QList<quint64>	l1;
		l1.reserve( DNA::OffMax );
		l1.append( 1 );
		l1.append( 0 );
		l1.append( 0 );
		l1.append( 0 );
		l1.append( 0 );
		l1.append( 4 ); // cost
		l1.append( 80 ); // age
		l1.append( 150 ); // birth energy
		defaultDNA().setValuesI( l1 );
		
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
};

TEST(SimpleRun, init) {
	
	initAprilLibrary();
	World * w = new World( __FUNCTION__, 1000 );
	DEC_REF( w, w );
	
	BrainTstFactSR * bf = new BrainTstFactSR( w );
	DEC_REF( bf, bf );
	ActuatorTstFactSR * af = new ActuatorTstFactSR( w );
	DEC_REF( af, af );
	ReflexTstFactSR * rf = new ReflexTstFactSR( w );
	DEC_REF( rf, rf );
	SensorTstFactSR * sf = new SensorTstFactSR( w );
	DEC_REF( sf, sf );
	
	TstFactSR * fact = new TstFactSR( w );
	DEC_REF( fact, fact );
	
	Actor * a = w->createActor( TestIdKind );
	Q_UNUSED( a );
	
	w->start();
	
	for ( int i = 0; i < 10; i++ )
	{
		w->advance();
	}
	
	w->stop();
	
	endAprilLibrary();
	
}
