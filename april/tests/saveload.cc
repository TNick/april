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

void saveTest		( World * w, const QString & s )
{
	QSettings s_out( s, QSettings::IniFormat );
	EXPECT_TRUE( w->save( s_out ) );
	s_out.sync();
}

void loadTest		( World * w, const QString & s )
{
	QSettings s_out( s, QSettings::IniFormat );
	EXPECT_TRUE( w->load( s_out ) );
}

}	/* namespace saveload_cc */
/* ----------------------------------------------------- */



TEST(SaveLoad, basic) {
	
	QTemporaryFile	tf;
	tf.open();

	initAprilLibrary();
	World * w = new World( __FUNCTION__, 1000 );
	DEC_REF( w, w );
	
	saveload_cc::FBrn * bf = new saveload_cc::FBrn( w );
	DEC_REF( bf, bf );
	saveload_cc::FActu * af = new saveload_cc::FActu( w );
	DEC_REF( af, af );
	saveload_cc::FRefx * rf = new saveload_cc::FRefx( w );
	DEC_REF( rf, rf );
	saveload_cc::FSens * sf = new saveload_cc::FSens( w );
	DEC_REF( sf, sf );
	
	saveload_cc::FAgent * fact = new saveload_cc::FAgent( w );
	DEC_REF( fact, fact );
	
	Actor * a = w->createActor( saveload_cc::IdKind );
	Q_UNUSED( a );
	
	w->start();
	w->advance();
	w->stop();
	
	saveload_cc::saveTest( w, tf.fileName() );
	saveload_cc::loadTest( w, tf.fileName() );
//	saveload_cc::saveTest( w, "D:\\qt\\april-build-Desktop_Qt_5_0_1_MinGW_32bit-Debug\\build\\t.ini");
//	saveload_cc::loadTest( w, "D:\\qt\\april-build-Desktop_Qt_5_0_1_MinGW_32bit-Debug\\build\\t.ini" );
	
	DEC_REF( a, a );
	
	endAprilLibrary();
}
