#include	<gtest/gtest.h>
#include	<april/aprillibrary.h>
#include	<april/logic/world.h>
#include	<april/logic/actor.h>
#include	<april/logic/actorfactory.h>
#include	<april/logic/sensor.h>
#include	<april/logic/sensorfactory.h>
#include	<april/logic/eventsource.h>
#include	<april/logic/eventfactory.h>
#include	<april/logic/eventdata.h>
#include	<april/logic/eventline.h>

using namespace april;

/* ----------------------------------------------------- */
namespace	sensor_cc		{

enum Ids {
	IdKind = 1,
	IdBrain,
	IdReflex,
	IdActuator,
	IdSensor,
	IdEvent,
	IdScanLine
};


class Sens : public Sensor	{
	int i_counter;
public:	
	
	Sens( Actor * actor ) : Sensor( actor, 1, 1 )
	{
		i_counter = 0;
	}
	
	virtual void		doSteps		( int steps )
	{
		Q_UNUSED( steps );
		EventLine * el = actor()->world()->eventLine( IdScanLine );
		if ( el != NULL )
		{
			EventData * ed = el->firstEventData();
			INC_REF(ed,this);
			
			EXPECT_EQ( ed->payload().i_, (quint64)i_counter );
			i_counter++;
			
			DEC_REF(ed,this);
		}
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
		Sens * ret = new Sens( a );
		
		return ret;
	}
	
};

class FAgent : public ActorFactory {
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
		EXPECT_TRUE( defaultDNA().addSensor( IdSensor ) );
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

class	Ev : public EventSource	{
	int i_counter;
public:
	Ev( World * w ) : EventSource( w )	{
		i_counter = 0;
	}
	void		doSteps		( int steps )
	{
		Q_UNUSED( steps );
		EventLine * el = world()->eventLine( IdScanLine );
		if ( el != NULL )
		{
			INC_REF(el,this);
			EventData * ed = new EventData( world(), 1 );
			ed->payload().i_ = i_counter;
			el->postActivity( ed );
			i_counter++;
			DEC_REF(ed,ed);
			DEC_REF(el,this);
		}
	}
};

class	FEv : public EventFactory	{
public:
	FEv(World * w) : EventFactory(w) {
		w->insertId( IdEvent, "events.test" );
		addMyself( IdEvent );
	}
	virtual EventSource *			create				( ID id ) {
		Q_UNUSED( id );
		Ev * ret = new Ev( world() );
		return ret;
	}
};

}	/* namespace sensor_cc */
/* ----------------------------------------------------- */

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

TEST(Sensor, factory) {
	initAprilLibrary();
	
	World * w = new World( __FUNCTION__, 1000 );
	DEC_REF( w, w );
	
	sensor_cc::FSens * sensor_fact = new sensor_cc::FSens( w );
	DEC_REF( sensor_fact, sensor_fact );
	
	sensor_cc::FAgent * actor_fact = new sensor_cc::FAgent( w );
	DEC_REF( actor_fact, actor_fact );
	
	Actor * a = w->createActor( sensor_cc::IdKind );
	DEC_REF( a, a );
	EXPECT_TRUE( a != NULL );
	EXPECT_TRUE( a->firstReflex() == NULL );
	EXPECT_TRUE( a->firstActuator() == NULL );
	EXPECT_TRUE( a->firstBrain() == NULL );
	EXPECT_TRUE( a->firstSensor() != NULL );
	EXPECT_EQ( a->kind(), sensor_cc::IdKind );
	EXPECT_EQ( a->kindName(), "kinds.test" );
	
	Sensor * r = a->firstSensor();
	EXPECT_TRUE( r->next() == NULL );
	EXPECT_TRUE( r->prev() == NULL );
	EXPECT_TRUE( r->actor() == a );
	
	endAprilLibrary();
}

TEST(Sensor, fromEvent) {
	initAprilLibrary();
	
	World * w = new World( __FUNCTION__, 1000 );
	DEC_REF( w, w );
	sensor_cc::FSens * sensor_fact = new sensor_cc::FSens( w );
	DEC_REF( sensor_fact, sensor_fact );
	sensor_cc::FAgent * actor_fact = new sensor_cc::FAgent( w );
	DEC_REF( actor_fact, actor_fact );
	Actor * a = w->createActor( sensor_cc::IdKind );
	DEC_REF( a, a );
	sensor_cc::FEv * ef = new sensor_cc::FEv( w );
	DEC_REF( ef, ef );
	sensor_cc::Ev * event = static_cast<sensor_cc::Ev*>( ef->create( sensor_cc::IdEvent ) );
	w->insertId( sensor_cc::IdScanLine, "eventline.test-1" );
	EventLine * el = new EventLine( w, sensor_cc::IdScanLine );
	DEC_REF( el, el );
	
	w->start();
	for ( int i = 0; i < 10; i++ )
	{
		/** SIGSEGV @todo w->advance(); */
	}
	w->stop();
	
	
	DEC_REF(event,event);
	endAprilLibrary();
}
