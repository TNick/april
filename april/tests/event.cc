#include	<gtest/gtest.h>
#include	<april/aprillibrary.h>
#include	<april/logic/world.h>
#include	<april/logic/actuator.h>
#include	<april/logic/eventsource.h>
#include	<april/logic/eventfactory.h>

using namespace april;

/* ----------------------------------------------------- */
namespace	event_cc		{

enum Ids {
	IdKind = 1,
	IdBrain,
	IdReflex,
	IdActuator,
	IdSensor,
	IdEvent
};

class	Ev : public EventSource	{
public:
	Ev( World * w ) : EventSource( w )	{
		hit_times_ = 0;
	}
	void		doSteps		( int steps )
	{
		Q_UNUSED( steps );
		hit_times_ += steps;
	}
	int hit_times_;
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

}	/* namespace event_cc */
/* ----------------------------------------------------- */

TEST(EventSource, init) {

	initAprilLibrary();
	World * w = new World( "test-world", 1000 );
	DEC_REF( w, w );
	
	event_cc::Ev * act = new event_cc::Ev( w );
	DEC_REF(act,act);
	
	endAprilLibrary();
}

TEST(EventSource, factory) {

	initAprilLibrary();
	World * w = new World( __FUNCTION__, 1000 );
	DEC_REF( w, w );
	event_cc::FEv * ef = new event_cc::FEv( w );
	DEC_REF( ef, ef );
	
	event_cc::Ev * event = static_cast<event_cc::Ev*>( ef->create( event_cc::IdEvent ) );
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


