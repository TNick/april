#include	<gtest/gtest.h>
#include	<april/aprillibrary.h>
#include	<april/logic/world.h>
#include	<april/logic/worldfactory.h>
#include	<april/logic/actor.h>
#include	<april/logic/actorfactory.h>
#include	<april/logic/eventsource.h>
#include	<april/logic/eventfactory.h>
#include	<april/logic/brain.h>
#include	<april/logic/brainfactory.h>
#include	<april/logic/actuator.h>
#include	<april/logic/actuatorfactory.h>
#include	<april/logic/reflex.h>
#include	<april/logic/reflexfactory.h>
#include	<april/logic/sensor.h>
#include	<april/logic/sensorfactory.h>

#include	<QMap>
#include	<QTemporaryFile>

using namespace april;

/* ----------------------------------------------------- */
namespace	saveload2_cc		{

enum Ids {
	IdKind = 1,
	IdBrain,
	IdReflex,
	IdActuator,
	IdSensor,
	IdEvent
};

static const char * f_world_name = "World.Factory.Test";
static const char * world_name = "World.Test";
static const char * f_actor_name = "Actor.Factory.Test";
static const char * f_event_name = "Event.Factory.Test";
static const char * f_sensor_name = "Sensor.Factory.Test";
static const char * f_actuator_name = "Actuator.Factory.Test";
static const char * f_reflex_name = "Reflex.Factory.Test";
static const char * f_brain_name = "Brain.Factory.Test";

class TstWorld : public World {
	friend class TstFact;
public:
	int test_int_;
protected:
	TstWorld(const QString & s, quint64 tot_energ) : World(s,tot_energ) {
		test_int_ = rand() % 12345;
	}
	virtual QString		factoryName			( void ) const
	{ return f_world_name; }
	virtual bool	save				( QSettings & stg ) const
	{
		bool b = true;
		b = b & World::save( stg );
		stg.beginGroup( "TstWorld" );
		stg.setValue( "test_int_", test_int_ );
		stg.endGroup();
		return b;
	}
	virtual bool	load				( QSettings & stg )
	{
		bool b = true;
		
		b = World::load( stg );
		if ( !b ) return false;
		
		stg.beginGroup( "TstWorld" );
		for(;;) {
			
			test_int_ = stg.value( "test_int_", 0 ).toInt( &b );
			if ( !b ) break;
			
			break;
		}
		stg.endGroup();
		
		return b;
	}
}; /* .............................................................. */
class TstFact : public WorldFactory	{
public:
	TstFact() : WorldFactory( f_world_name ) {
	}
	virtual QString			factoryName			( void )
	{ return f_world_name; }
	virtual World * create ( const QString & s, quint64 tot_energ ) {
		return new TstWorld( s, tot_energ );
	}
	virtual World * create ( QSettings & stg ) {
		World * w = new TstWorld( world_name, 0 );
		if ( w->load( stg ) == false )
		{
			DEC_REF(w,w);
			AprilLibrary::remWorld( w );
			return NULL;
		}
		return w;
	}
}; /* .............................................................. */
class TstActor : public Actor {
	friend class TstFactActor;
public:
	int test_int_;
protected:
	TstActor( World * w ) : Actor( w ) {
		test_int_ = rand() % 22345;
	}
	virtual QString		factoryName		( void ) const
	{ return f_actor_name; }
	bool			save				( QSettings & stg ) const {
		bool b = true;
		b = b & Actor::save( stg );
		stg.beginGroup( "TstActor" );
		stg.setValue( "test_int_", test_int_ );
		stg.endGroup();
		return b;
	}
	bool			load				( QSettings & stg ) {
		bool b = true;
		
		b = Actor::load( stg );
		if ( !b ) return false;
		
		stg.beginGroup( "TstActor" );
		for(;;) {
			
			test_int_ = stg.value( "test_int_", 0 ).toInt( &b );
			if ( !b ) break;
			
			break;
		}
		stg.endGroup();
		
		return b;
	}
	virtual ID			identificator			( void ) const
	{ return IdKind; }
	virtual Factory *	factory					( void ) const
	{ return world()->actorFactories().value( IdKind ); }
	
}; /* .............................................................. */
class TstFactActor : public ActorFactory	{
public:
	int test_int_;
	TstFactActor( World * w ) : ActorFactory( w ) {
		w->insertId( IdKind, f_actor_name );
		addMyself( IdKind );
		test_int_ = rand() % 32345;
		DNA::InitData	idata;
		idata.kind_ = IdKind;
		idata.cost_ = 1;
		idata.age_= 100;
		idata.energy_= 10;
		initDNA( idata );
//		EXPECT_TRUE( defaultDNA().addBrain( IdBrain) );
//		EXPECT_TRUE( defaultDNA().addActuator( IdActuator ) );
//		EXPECT_TRUE( defaultDNA().addReflex( IdReflex ) );
//		EXPECT_TRUE( defaultDNA().addSensor( IdSensor ) );
	}
	virtual QString			factoryName			( void )
	{ return f_actor_name; }
	Actor *			create				( ID id ) {
		Q_UNUSED( id );
		return new TstActor( world() );
	}
	bool			save				( QSettings & stg ) const {
		bool b = true;
		b = b & ActorFactory::save( stg );
		stg.beginGroup( "TstFactActor" );
		stg.setValue( "test_int_", test_int_ );
		stg.endGroup();
		return b;
	}
	bool			load				( QSettings & stg ) {
		bool b = true;
		
		b = ActorFactory::load( stg );
		if ( !b ) return false;
		
		stg.beginGroup( "TstFactActor" );
		for(;;) {
			
			test_int_ = stg.value( "test_int_", 0 ).toInt( &b );
			if ( !b ) break;
			
			break;
		}
		stg.endGroup();
		
		return b;
	}
}; /* .............................................................. */
class TstEventSource : public EventSource {
	friend class TstFactEventSource;
public:
	int test_int_;
protected:
	TstEventSource( World * w ) : EventSource( w ) {
		test_int_ = rand() % 22345;
	}
	virtual QString		factoryName		( void ) const
	{ return f_event_name; }
	bool			save				( QSettings & stg ) const {
		bool b = true;
		b = b & EventSource::save( stg );
		stg.beginGroup( "TstEventSource" );
		stg.setValue( "test_int_", test_int_ );
		stg.endGroup();
		return b;
	}
	bool			load				( QSettings & stg ) {
		bool b = true;
		
		b = EventSource::load( stg );
		if ( !b ) return false;
		
		stg.beginGroup( "TstEventSource" );
		for(;;) {
			test_int_ = stg.value( "test_int_", 0 ).toInt( &b );
			if ( !b ) break;
			
			break;
		}
		stg.endGroup();
		
		return b;
	}
}; /* .............................................................. */
class TstFactEventSource : public EventFactory	{
public:
	int test_int_;
	TstFactEventSource( World * w ) : EventFactory( w ) {
		w->insertId( IdEvent, f_event_name );
		addMyself( IdEvent );
		test_int_ = rand() % 42345;
	}
	virtual QString			factoryName			( void )
	{ return f_event_name; }
	EventSource *			create				( ID id ) {
		Q_UNUSED( id );
		return new TstEventSource( world() );
	}
	bool			save				( QSettings & stg ) const {
		bool b = true;
		b = b & EventFactory::save( stg );
		stg.beginGroup( "TstFactEventSource" );
		stg.setValue( "test_int_", test_int_ );
		stg.endGroup();
		return b;
	}
	bool			load				( QSettings & stg ) {
		bool b = true;
		
		b = EventFactory::load( stg );
		if ( !b ) return false;
		
		stg.beginGroup( "TstFactEventSource" );
		for(;;) {
			test_int_ = stg.value( "test_int_", 0 ).toInt( &b );
			if ( !b ) break;
			
			break;
		}
		stg.endGroup();
		
		return b;
	}
}; /* .............................................................. */
class TstSensor : public Sensor {
	friend class TstFactSensor;
public:
	int test_int_;
protected:
	TstSensor( Actor * actor ) : Sensor( actor ) {
		test_int_ = rand() % 22345;
	}
	virtual QString		factoryName		( void ) const
	{ return f_actor_name; }
	bool			save				( QSettings & stg ) const {
		bool b = true;
		b = b & Sensor::save( stg );
		stg.beginGroup( "TstSensor" );
		stg.setValue( "test_int_", test_int_ );
		stg.endGroup();
		return b;
	}
	bool			load				( QSettings & stg ) {
		bool b = true;
		
		b = Sensor::load( stg );
		if ( !b ) return false;
		
		stg.beginGroup( "TstSensor" );
		for(;;) {
			
			test_int_ = stg.value( "test_int_", 0 ).toInt( &b );
			if ( !b ) break;
			
			break;
		}
		stg.endGroup();
		
		return b;
	}
}; /* .............................................................. */
class TstFactSensor : public SensorFactory	{
public:
	int test_int_;
	TstFactSensor( World * w ) : SensorFactory( w ) {
		w->insertId( IdSensor, f_sensor_name );
		addMyself( IdSensor );
		test_int_ = rand() % 32345;
	}
	virtual QString			factoryName			( void )
	{ return f_sensor_name; }
	Sensor * create ( Actor * ag, ID id ) {
		Q_UNUSED( id );
		return new TstSensor( ag );
	}
	bool			save				( QSettings & stg ) const {
		bool b = true;
		b = b & SensorFactory::save( stg );
		stg.beginGroup( "TstFactSensor" );
		stg.setValue( "test_int_", test_int_ );
		stg.endGroup();
		return b;
	}
	bool			load				( QSettings & stg ) {
		bool b = true;
		
		b = SensorFactory::load( stg );
		if ( !b ) return false;
		
		stg.beginGroup( "TstFactSensor" );
		for(;;) {
			
			test_int_ = stg.value( "test_int_", 0 ).toInt( &b );
			if ( !b ) break;
			
			break;
		}
		stg.endGroup();
		
		return b;
	}
}; /* .............................................................. */
class TstActuator : public Actuator {
	friend class TstFactActuator;
public:
	int test_int_;
protected:
	TstActuator( Actor * actor ) : Actuator( actor ) {
		test_int_ = rand() % 22345;
	}
	virtual QString		factoryName		( void ) const
	{ return f_actor_name; }
	bool			save				( QSettings & stg ) const {
		bool b = true;
		b = b & Actuator::save( stg );
		stg.beginGroup( "TstActuator" );
		stg.setValue( "test_int_", test_int_ );
		stg.endGroup();
		return b;
	}
	bool			load				( QSettings & stg ) {
		bool b = true;
		
		b = Actuator::load( stg );
		if ( !b ) return false;
		
		stg.beginGroup( "TstActuator" );
		for(;;) {
			
			test_int_ = stg.value( "test_int_", 0 ).toInt( &b );
			if ( !b ) break;
			
			break;
		}
		stg.endGroup();
		
		return b;
	}
}; /* .............................................................. */
class TstFactActuator : public ActuatorFactory	{
public:
	int test_int_;
	TstFactActuator( World * w ) : ActuatorFactory( w ) {
		w->insertId( IdActuator, f_actuator_name );
		addMyself( IdActuator );
		test_int_ = rand() % 32345;
	}
	virtual QString			factoryName			( void )
	{ return f_actuator_name; }
	Actuator * create ( Actor * ag, ID id ) {
		Q_UNUSED( id );
		return new TstActuator( ag );
	}
	bool			save				( QSettings & stg ) const {
		bool b = true;
		b = b & ActuatorFactory::save( stg );
		stg.beginGroup( "TstFactActuator" );
		stg.setValue( "test_int_", test_int_ );
		stg.endGroup();
		return b;
	}
	bool			load				( QSettings & stg ) {
		bool b = true;
		
		b = ActuatorFactory::load( stg );
		if ( !b ) return false;
		
		stg.beginGroup( "TstFactActuator" );
		for(;;) {
			
			test_int_ = stg.value( "test_int_", 0 ).toInt( &b );
			if ( !b ) break;
			
			break;
		}
		stg.endGroup();
		
		return b;
	}
}; /* .............................................................. */
class TstReflex : public Reflex {
	friend class TstFactReflex;
public:
	int test_int_;
protected:
	TstReflex( Actor * actor ) : Reflex( actor ) {
		test_int_ = rand() % 22345;
	}
	virtual QString		factoryName		( void ) const
	{ return f_actor_name; }
	bool			save				( QSettings & stg ) const {
		bool b = true;
		b = b & Reflex::save( stg );
		stg.beginGroup( "TstReflex" );
		stg.setValue( "test_int_", test_int_ );
		stg.endGroup();
		return b;
	}
	bool			load				( QSettings & stg ) {
		bool b = true;
		
		b = Reflex::load( stg );
		if ( !b ) return false;
		
		stg.beginGroup( "TstReflex" );
		for(;;) {
			
			test_int_ = stg.value( "test_int_", 0 ).toInt( &b );
			if ( !b ) break;
			
			break;
		}
		stg.endGroup();
		
		return b;
	}
}; /* .............................................................. */
class TstFactReflex : public ReflexFactory	{
public:
	int test_int_;
	TstFactReflex( World * w ) : ReflexFactory( w ) {
		w->insertId( IdReflex, f_reflex_name );
		addMyself( IdReflex );
		test_int_ = rand() % 32345;
	}
	virtual QString			factoryName			( void )
	{ return f_reflex_name; }
	Reflex * create ( Actor * ag, ID id ) {
		Q_UNUSED( id );
		return new TstReflex( ag );
	}
	bool			save				( QSettings & stg ) const {
		bool b = true;
		b = b & ReflexFactory::save( stg );
		stg.beginGroup( "TstFactReflex" );
		stg.setValue( "test_int_", test_int_ );
		stg.endGroup();
		return b;
	}
	bool			load				( QSettings & stg ) {
		bool b = true;
		
		b = ReflexFactory::load( stg );
		if ( !b ) return false;
		
		stg.beginGroup( "TstFactReflex" );
		for(;;) {
			
			test_int_ = stg.value( "test_int_", 0 ).toInt( &b );
			if ( !b ) break;
			
			break;
		}
		stg.endGroup();
		
		return b;
	}
}; /* .............................................................. */
class TstBrain : public Brain {
	friend class TstFactBrain;
public:
	int test_int_;
protected:
	TstBrain( Actor * actor ) : Brain( actor ) {
		test_int_ = rand() % 22345;
	}
	virtual QString		factoryName		( void ) const
	{ return f_actor_name; }
	bool			save				( QSettings & stg ) const {
		bool b = true;
		b = b & Brain::save( stg );
		stg.beginGroup( "TstBrain" );
		stg.setValue( "test_int_", test_int_ );
		stg.endGroup();
		return b;
	}
	bool			load				( QSettings & stg ) {
		bool b = true;
		
		b = Brain::load( stg );
		if ( !b ) return false;
		
		stg.beginGroup( "TstBrain" );
		for(;;) {
			
			test_int_ = stg.value( "test_int_", 0 ).toInt( &b );
			if ( !b ) break;
			
			break;
		}
		stg.endGroup();
		
		return b;
	}
}; /* .............................................................. */
class TstFactBrain : public BrainFactory	{
public:
	int test_int_;
	TstFactBrain( World * w ) : BrainFactory( w ) {
		w->insertId( IdBrain, f_brain_name );
		addMyself( IdBrain );
		test_int_ = rand() % 32345;
	}
	virtual QString			factoryName			( void )
	{ return f_brain_name; }
	Brain * create ( Actor * ag, ID id ) {
		Q_UNUSED( id );
		return new TstBrain( ag );
	}
	bool			save				( QSettings & stg ) const {
		bool b = true;
		b = b & BrainFactory::save( stg );
		stg.beginGroup( "TstFactBrain" );
		stg.setValue( "test_int_", test_int_ );
		stg.endGroup();
		return b;
	}
	bool			load				( QSettings & stg ) {
		bool b = true;
		
		b = BrainFactory::load( stg );
		if ( !b ) return false;
		
		stg.beginGroup( "TstFactBrain" );
		for(;;) {
			
			test_int_ = stg.value( "test_int_", 0 ).toInt( &b );
			if ( !b ) break;
			
			break;
		}
		stg.endGroup();
		
		return b;
	}
}; /* .............................................................. */


Factory * factoryCreatorWorlds ( World * w, const QString & s_name )
{
	Q_UNUSED( s_name );
	Q_UNUSED( w );
	Factory * f = AprilLibrary::findWorldFactory( f_world_name );
	if ( f == NULL )
	{
		f = new TstFact();
	}
	else
	{
		INC_REF(f,f);
	}
	return f;
}
Factory * factoryCreatorActor ( World * w, const QString & s_name )
{
	Q_UNUSED( s_name );
	return new TstFactActor(w);
}
Factory * factoryCreatorEventSource ( World * w, const QString & s_name )
{
	Q_UNUSED( s_name );
	return new TstFactEventSource(w);
}
Factory * factoryCreatorSensor ( World * w, const QString & s_name )
{
	Q_UNUSED( s_name );
	return new TstFactSensor(w);
}
Factory * factoryCreatorActuator ( World * w, const QString & s_name )
{
	Q_UNUSED( s_name );
	return new TstFactActuator(w);
}
Factory * factoryCreatorReflex ( World * w, const QString & s_name )
{
	Q_UNUSED( s_name );
	return new TstFactReflex(w);
}
Factory * factoryCreatorBrain ( World * w, const QString & s_name )
{
	Q_UNUSED( s_name );
	return new TstFactBrain(w);
}


void saveWorld ( World * w, const QString & s_file )
{
	QSettings s_out( s_file, QSettings::IniFormat );
	EXPECT_TRUE( w->save( s_out ) );
	s_out.sync();
}
World * loadWorld ( const QString & s_file )
{
	QSettings s_out( s_file, QSettings::IniFormat );
	World * ret = World::fromStg( s_out );
	EXPECT_TRUE( ret != NULL );
	return ret;
}

}	/* namespace saveload2_cc */
/* ----------------------------------------------------- */

void registerFactoryCreators()
{
	/* register factory creators so that they may be later retrieved */
	AprilLibrary::registerFactory( 
				saveload2_cc::f_world_name, 
				saveload2_cc::factoryCreatorWorlds );
	AprilLibrary::registerFactory( 
				saveload2_cc::f_actor_name, 
				saveload2_cc::factoryCreatorActor );
	AprilLibrary::registerFactory( 
				saveload2_cc::f_event_name, 
				saveload2_cc::factoryCreatorEventSource );
	AprilLibrary::registerFactory( 
				saveload2_cc::f_sensor_name, 
				saveload2_cc::factoryCreatorSensor );
	AprilLibrary::registerFactory( 
				saveload2_cc::f_actuator_name, 
				saveload2_cc::factoryCreatorActuator );
	AprilLibrary::registerFactory( 
				saveload2_cc::f_reflex_name, 
				saveload2_cc::factoryCreatorReflex );
	AprilLibrary::registerFactory( 
				saveload2_cc::f_brain_name, 
				saveload2_cc::factoryCreatorBrain );
}

void addFactories ( World * test_world )
{
	/* Actor factory */
	saveload2_cc::TstFactActor * tstactorf = 
			new saveload2_cc::TstFactActor( test_world );
	DEC_REF(tstactorf,tstactorf);
	/* Event factory */
	saveload2_cc::TstFactEventSource * tsteventf = 
			new saveload2_cc::TstFactEventSource( test_world );
	DEC_REF(tsteventf,tsteventf);
	/* Sensor factory */
	saveload2_cc::TstFactSensor * tstsensorf = 
			new saveload2_cc::TstFactSensor( test_world );
	DEC_REF(tstsensorf,tstsensorf);
	/* Actuator factory */
	saveload2_cc::TstFactActuator * tstactuatorf = 
			new saveload2_cc::TstFactActuator( test_world );
	DEC_REF(tstactuatorf,tstactuatorf);
	/* Reflex factory */
	saveload2_cc::TstFactReflex * tstreflexf = 
			new saveload2_cc::TstFactReflex( test_world );
	DEC_REF(tstreflexf,tstreflexf);
	/* Brain factory */
	saveload2_cc::TstFactBrain * tstbrainf = 
			new saveload2_cc::TstFactBrain( test_world );
	DEC_REF(tstbrainf,tstbrainf);	
}

void compareTwoWorldsFactories( 
		saveload2_cc::TstWorld * loaded_world, 
		saveload2_cc::TstWorld * test_world)
{
	QMap<ID,ActorFactory*> afl1 = loaded_world->actorFactories();
	QMap<ID,ActorFactory*> afl2 = test_world->actorFactories();
	EXPECT_EQ( afl1.count(), 1 );
	EXPECT_EQ( afl2.count(), 1 );
	EXPECT_EQ( afl1.constBegin().key(), afl2.constBegin().key() );
	EXPECT_TRUE( afl1.constBegin().value() != NULL );
	EXPECT_TRUE( afl2.constBegin().value() != NULL );
	EXPECT_EQ( 
				static_cast<saveload2_cc::TstFactActor*>(
					afl1.constBegin().value())->test_int_,
				static_cast<saveload2_cc::TstFactActor*>(
					afl2.constBegin().value())->test_int_
				);
	
	QMap<ID,EventFactory*> efl1 = loaded_world->eventFactories();
	QMap<ID,EventFactory*> efl2 = test_world->eventFactories();
	EXPECT_EQ( efl1.count(), 1 );
	EXPECT_EQ( efl2.count(), 1 );
	EXPECT_EQ( efl1.constBegin().key(), efl2.constBegin().key() );
	EXPECT_TRUE( efl1.constBegin().value() != NULL );
	EXPECT_TRUE( efl2.constBegin().value() != NULL );
	EXPECT_EQ( 
				static_cast<saveload2_cc::TstFactEventSource*>(
					efl1.constBegin().value())->test_int_,
				static_cast<saveload2_cc::TstFactEventSource*>(
					efl2.constBegin().value())->test_int_
				);
	
	QMap<ID,SensorFactory*> sfl1 = loaded_world->sensorFactories();
	QMap<ID,SensorFactory*> sfl2 = test_world->sensorFactories();
	EXPECT_EQ( sfl1.count(), 1 );
	EXPECT_EQ( sfl2.count(), 1 );
	EXPECT_EQ( sfl1.constBegin().key(), sfl2.constBegin().key() );
	EXPECT_TRUE( sfl1.constBegin().value() != NULL );
	EXPECT_TRUE( sfl2.constBegin().value() != NULL );
	EXPECT_EQ( 
				static_cast<saveload2_cc::TstFactSensor*>(
					sfl1.constBegin().value())->test_int_,
				static_cast<saveload2_cc::TstFactSensor*>(
					sfl2.constBegin().value())->test_int_
				);
	
	QMap<ID,ActuatorFactory*> attfl1 = loaded_world->actuatorFactories();
	QMap<ID,ActuatorFactory*> attfl2 = test_world->actuatorFactories();
	EXPECT_EQ( attfl1.count(), 1 );
	EXPECT_EQ( attfl2.count(), 1 );
	EXPECT_EQ( attfl1.constBegin().key(), attfl2.constBegin().key() );
	EXPECT_TRUE( attfl1.constBegin().value() != NULL );
	EXPECT_TRUE( attfl2.constBegin().value() != NULL );
	EXPECT_EQ( 
				static_cast<saveload2_cc::TstFactActuator*>(
					attfl1.constBegin().value())->test_int_,
				static_cast<saveload2_cc::TstFactActuator*>(
					attfl2.constBegin().value())->test_int_
				);
	
	QMap<ID,ReflexFactory*> rfl1 = loaded_world->reflexFactories();
	QMap<ID,ReflexFactory*> rfl2 = test_world->reflexFactories();
	EXPECT_EQ( rfl1.count(), 1 );
	EXPECT_EQ( rfl2.count(), 1 );
	EXPECT_EQ( rfl1.constBegin().key(), rfl2.constBegin().key() );
	EXPECT_TRUE( rfl1.constBegin().value() != NULL );
	EXPECT_TRUE( rfl2.constBegin().value() != NULL );
	EXPECT_EQ( 
				static_cast<saveload2_cc::TstFactReflex*>(
					rfl1.constBegin().value())->test_int_,
				static_cast<saveload2_cc::TstFactReflex*>(
					rfl2.constBegin().value())->test_int_
				);
	
	QMap<ID,BrainFactory*> bfl1 = loaded_world->brainFactories();
	QMap<ID,BrainFactory*> bfl2 = test_world->brainFactories();
	EXPECT_EQ( bfl1.count(), 1 );
	EXPECT_EQ( bfl2.count(), 1 );
	EXPECT_EQ( bfl1.constBegin().key(), bfl2.constBegin().key() );
	EXPECT_TRUE( bfl1.constBegin().value() != NULL );
	EXPECT_TRUE( bfl2.constBegin().value() != NULL );
	EXPECT_EQ( 
				static_cast<saveload2_cc::TstFactBrain*>(
					bfl1.constBegin().value())->test_int_,
				static_cast<saveload2_cc::TstFactBrain*>(
					bfl2.constBegin().value())->test_int_
				);
}


TEST(SaveLoad2, basic) {
	
	QTemporaryFile	tf;
	tf.open();
	
	initAprilLibrary();
	registerFactoryCreators();
	
	/* World factory */
	saveload2_cc::TstFact * tstf = 
			new saveload2_cc::TstFact();
	DEC_REF(tstf,tstf);
	
	/* World */
	saveload2_cc::TstWorld * test_world = 
			static_cast<saveload2_cc::TstWorld *>(
				tstf->create( "sample-world", 10000 ));
	
	addFactories( test_world );
	saveload2_cc::TstActor * test_actor = static_cast<saveload2_cc::TstActor*>(
				test_world->createActor( saveload2_cc::IdKind ) );
	Q_UNUSED( test_actor );
	
	/* save our world */
	saveload2_cc::saveWorld( test_world, tf.fileName() );
	
	/* and load it in a different one */
	saveload2_cc::TstWorld * loaded_world = 
			static_cast<saveload2_cc::TstWorld *>( 
				saveload2_cc::loadWorld( tf.fileName() ) );
	
	
	EXPECT_TRUE( loaded_world != NULL );
	EXPECT_EQ( loaded_world->test_int_, test_world->test_int_ );
	EXPECT_EQ( loaded_world->payload().i_, test_world->payload().i_ );
	EXPECT_EQ( loaded_world->name(), test_world->name() );
	EXPECT_EQ( loaded_world->currentTime(), test_world->currentTime() );
	EXPECT_EQ( loaded_world->energy(), test_world->energy() );
	EXPECT_EQ( loaded_world->energyBounded(), test_world->energyBounded() );
	EXPECT_EQ( loaded_world->energyFree(), test_world->energyFree() );
	EXPECT_TRUE( loaded_world->sameUId( test_world ) );
	
	
	compareTwoWorldsFactories( loaded_world, test_world );
	saveload2_cc::TstActor * loaded_actor = 
			static_cast<saveload2_cc::TstActor *>( 
				loaded_world->firstActor() );
	
	EXPECT_TRUE( loaded_actor != NULL );
	EXPECT_EQ( loaded_actor->test_int_, test_actor->test_int_ );
	
	
	DEC_REF(loaded_world,loaded_world);
	DEC_REF(test_world,test_world);
	AprilLibrary::unregisterFactory( 
				saveload2_cc::f_world_name, 
				saveload2_cc::factoryCreatorWorlds );
	endAprilLibrary();
	
}
