#include	<gtest/gtest.h>
#include	<april/aprillibrary.h>
#include	<april/logic/world.h>
#include	<april/logic/actuator.h>
#include	<april/logic/event.h>
#include	<april/logic/eventfactory.h>

using namespace april;

class	TstE : public Event	{
public:
	TstE( World * w ) : Event( w )	{
		hit_times_ = 0;
	}
	void		doSteps		( int steps )
	{
		Q_UNUSED( steps );
		hit_times_ += steps;
	}
	int hit_times_;
};

TEST(Event, init) {

	initAprilLibrary();
	World * w = new World( "test-world", 1000 );
	DEC_REF( w, w );
	
	TstE * act = new TstE( w );
	DEC_REF(act,act);
	
	endAprilLibrary();
}

enum TestIds {
	TestIdKind = 1,
	TestIdBrain,
	TestIdReflex,
	TestIdActuator,
	TestIdSensor,
	TestIdEvent
};



class	TstFactoryE : public EventFactory	{
public:
	TstFactoryE(World * w) : EventFactory(w) {
		w->insertId( TestIdEvent, "events.test" );
		addMyself( TestIdEvent );
	}
	virtual Event *			create				( ID id ) {
		Q_UNUSED( id );
		TstE * ret = new TstE( world() );
		return ret;
	}
};

TEST(Event, factory) {

	initAprilLibrary();
	World * w = new World( "test-world", 1000 );
	DEC_REF( w, w );
	TstFactoryE * ef = new TstFactoryE( w );
	DEC_REF( ef, ef );
	
	TstE * event = static_cast<TstE*>( ef->create( TestIdEvent ) );
	w->start();
	for ( int i = 0; i < 10; i++ )
	{
		w->advance();
	}
	w->stop();
	
	EXPECT_EQ( event->hit_times_, 10 );
	DEC_REF(event,event);
	endAprilLibrary();
}


