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
namespace	actor_cc		{

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
		return ret;
	}
};

class FAgent : public ActorFactory	{
public:
	
	FAgent( World * w ) : ActorFactory( w ) {
		w->insertId( IdKind, "kinds.test" );
		addMyself( IdKind );
		initDNA( IdKind );
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
	virtual void copyDefaultDNA ( DNA & destination ) { 
		destination = defaultDNA();
	}

};
}	/* namespace actor_cc */
/* ----------------------------------------------------- */


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

TEST(Actor, factory) {
	
	initAprilLibrary();
	World * w = new World( __FUNCTION__, 1000 );
	DEC_REF( w, w );
	
	actor_cc::FBrn * bf = new actor_cc::FBrn( w );
	DEC_REF( bf, bf );
	actor_cc::FActu * af = new actor_cc::FActu( w );
	DEC_REF( af, af );
	actor_cc::FRefx * rf = new actor_cc::FRefx( w );
	DEC_REF( rf, rf );
	actor_cc::FSens * sf = new actor_cc::FSens( w );
	DEC_REF( sf, sf );
	
	actor_cc::FAgent * fact = new actor_cc::FAgent( w );
	DEC_REF( fact, fact );
	
	Actor * a = w->createActor( actor_cc::IdKind );
	EXPECT_TRUE( a != NULL );
	EXPECT_EQ( a->kind(), actor_cc::IdKind );
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

