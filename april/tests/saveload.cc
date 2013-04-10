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
#include	<april/logic/eventsource.h>
#include	<april/logic/eventfactory.h>

#include	<QTemporaryFile>

using namespace april;

/* ----------------------------------------------------- */
namespace	saveload_cc		{



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
		DNA::InitData	idata;
		idata.kind_ = IdKind;
		idata.cost_ = 1;
		idata.age_= 100;
		idata.energy_= 10;
		initDNA( idata );
		
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



/* ----------------------------------------------------- */


void registerFactoryCreators()
{
	/* register factory creators so that they may be later retrieved */
}


bool				saveTest		( World * w, const QString & s )
{
	QSettings s_out( s, QSettings::IniFormat );
	bool b = w->save( s_out );
	s_out.sync();
	return b;
}

World *				loadTest		( const QString & s )
{
	QSettings s_out( s, QSettings::IniFormat );
	World * w = World::fromStg( s_out );
	return w;
}

}	/* namespace saveload_cc */
/* ----------------------------------------------------- */



TEST(SaveLoad, basic) {
	/* save and load an empty world */
	
	QTemporaryFile	tf;
	tf.open();
	
	initAprilLibrary();
	World * w = new World( __FUNCTION__, 1000 );
	DEC_REF( w, w );
	
	EXPECT_TRUE( saveload_cc::saveTest( w, tf.fileName() ) );
	World * loaded_world = saveload_cc::loadTest( tf.fileName() );
	EXPECT_TRUE( loaded_world != NULL );
	
	DEC_REF( loaded_world, loaded_world );
	endAprilLibrary();
}
	
TEST(SaveLoad, actor) {
	/* save a world with actor and no factory */
	
	QTemporaryFile	tf;
	tf.open();
	
	initAprilLibrary();
	World * w = new World( __FUNCTION__, 1000 );
	DEC_REF( w, w );
	
	Actor * a = new Actor( w );
	DEC_REF( a, a );
	
	EXPECT_FALSE( saveload_cc::saveTest( w, tf.fileName() ) );
		
	endAprilLibrary();
}	

TEST(SaveLoad, actor_factory) {
	/* save a world with actor and actor factory */
	
	QTemporaryFile	tf;
	tf.open();
	
	initAprilLibrary();
	World * test_world = new World( __FUNCTION__, 1000 );
	DEC_REF( test_world, test_world );
	test_world->payload().i_ = 11;
	
	ActorFactory * af = new ActorFactory( test_world );
	test_world->addActorFactory( af, 1 );
	Actor * test_actor = test_world->createActor( 1 );
	DEC_REF( test_actor, test_actor );
	test_actor->payload().i_ = 11;
	
	EXPECT_TRUE( saveload_cc::saveTest( test_world, tf.fileName() ) );
	World * loaded_world = saveload_cc::loadTest( tf.fileName() );
	EXPECT_TRUE( loaded_world != NULL );
	EXPECT_EQ( loaded_world->payload().i_, test_world->payload().i_ );
	EXPECT_EQ( loaded_world->name(), test_world->name() );
	EXPECT_EQ( loaded_world->currentTime(), test_world->currentTime() );
	EXPECT_EQ( loaded_world->energy(), test_world->energy() );
	EXPECT_EQ( loaded_world->energyBounded(), test_world->energyBounded() );
	EXPECT_EQ( loaded_world->energyFree(), test_world->energyFree() );
	EXPECT_TRUE( loaded_world->sameUId( test_world ) );
	
	Actor * loaded_actor = loaded_world->firstActor();
	
	EXPECT_TRUE( loaded_actor != NULL );
	EXPECT_EQ( loaded_actor->payload().i_, test_actor->payload().i_ );
	
	endAprilLibrary();
}	
