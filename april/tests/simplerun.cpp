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

/* ----------------------------------------------------- */
namespace	simplerun_cc		{



enum Ids {
	IdKind = 1,
	IdBrain,
	IdReflex,
	IdActuator,
	IdSensor
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
		EXPECT_TRUE( setEnergy( ret, 100, 5 ) );
		return ret;
	}
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
		EXPECT_TRUE( setEnergy( ret, 10, 1 ) );
		return ret;
	}
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
		EXPECT_TRUE( setEnergy( ret, 10, 1 ) );
		return ret;
	}
};

class FSens : public SensorFactory {
public:
	FSens( World * w ): SensorFactory( w ) {
		w->insertId( IdSensor, "sensors.test" );
		addMyself( IdSensor );
	}
	virtual Sensor * create ( Actor * a, ID id ) {
		Q_UNUSED( id );
		Sensor * ret = new Sensor( a );
		EXPECT_TRUE( setEnergy( ret, 10, 1 ) );
		return ret;
	}
};

class FAgent : public ActorFactory	{
public:
	
	FAgent( World * w ) : ActorFactory( w ) {
		w->insertId( IdKind, "kinds.test" );
		addMyself( IdKind );
		initDNA( IdKind );
		
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
		
		EXPECT_TRUE( defaultDNA().addBrain( IdBrain) );
		EXPECT_TRUE( defaultDNA().addActuator( IdActuator ) );
		EXPECT_TRUE( defaultDNA().addReflex( IdReflex ) );
		EXPECT_TRUE( defaultDNA().addSensor( IdSensor ) );
	}
	virtual Actor * create ( ID id ) {
		Q_UNUSED( id );
		Q_ASSERT( id == IdKind );
		/* create new instance that gets inserted in the world */
		Actor * ret = new Actor( world() ); 
		/* set a default dan */
		setDNA( ret );
		return ret;
	}
};

}	/* namespace simplerun_cc */
/* ----------------------------------------------------- */


TEST(SimpleRun, init) {
	
	initAprilLibrary();
	World * w = new World( __FUNCTION__, 1000 );
	DEC_REF( w, w );
	
	simplerun_cc::FBrn * bf = new simplerun_cc::FBrn( w );
	DEC_REF( bf, bf );
	simplerun_cc::FActu * af = new simplerun_cc::FActu( w );
	DEC_REF( af, af );
	simplerun_cc::FRefx * rf = new simplerun_cc::FRefx( w );
	DEC_REF( rf, rf );
	simplerun_cc::FSens * sf = new simplerun_cc::FSens( w );
	DEC_REF( sf, sf );
	
	simplerun_cc::FAgent * fact = new simplerun_cc::FAgent( w );
	DEC_REF( fact, fact );
	
	Actor * a = w->createActor( simplerun_cc::IdKind );
	Q_UNUSED( a );
	
	w->start();
	
	int i = 0;
	while ( a->isAlive() )
	{
		w->advance();
		i++;
	}
	EXPECT_GE( i, 0 );
	EXPECT_LE( i, 20 );

	w->stop();
	DEC_REF( a, a );
	
	endAprilLibrary();
}
