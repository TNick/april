
#include <iostream>

#include <april/aprillibrary.h>
#include <april/logic/world.h>
#include <april/logic/factory.h>
#include <april/logic/sensorfactory.h>
#include <april/logic/actuatorfactory.h>
#include <april/logic/actorfactory.h>
#include <april/logic/brainfactory.h>
#include <april/logic/reflexfactory.h>
#include <april/logic/sensor.h>
#include <april/logic/actuator.h>
#include <april/logic/actor.h>
#include <april/logic/brain.h>
#include <april/logic/reflex.h>

#include <april/logic/eventdata.h>
#include <april/logic/eventsource.h>
#include <april/logic/eventfactory.h>
#include <april/logic/eventline.h>


using namespace std;
using namespace april;

enum	Constants		{
	WORLD_ENERGY = 10000,
	IdKind = 1,
	IdBrain,
	IdSensor,
	IdReflex,
	IdActuator,
	IdEvent,
	IdEventLine
};

class FActor : public ActorFactory {
public:
	FActor( World * w ) : ActorFactory( w ) {
		w->insertId( IdKind, "kinds.test" );
		addMyself( IdKind );
		
		DNA::InitData	idata;
		idata.kind_ = IdKind;
		idata.cost_ = 1;
		idata.age_= 100;
		idata.energy_= 50;
		initDNA( idata );
		
		defaultDNA().addBrain( IdBrain);
		defaultDNA().addActuator( IdActuator );
		defaultDNA().addReflex( IdReflex );
		defaultDNA().addSensor( IdSensor );
	}
	virtual Actor * create ( ID id ) {
		Actor * ret = new Actor( world() ); 
		setDNA( ret );
		return ret;
	}
	virtual void copyDefaultDNA ( DNA & destination ) { 
		destination = defaultDNA();
	}
	
};
class FActuator : public ActuatorFactory {
public:
	FActuator( World * w ): ActuatorFactory( w ) {
		w->insertId( IdActuator, "actuators.test" );
		addMyself( IdActuator );
	}
	virtual Actuator * create ( Actor * a, ID id ) {
		Actuator * ret = new Actuator( a, 1, 10 );
		return ret;
	}
};
class FBrain : public BrainFactory {
public:
	FBrain( World * w ): BrainFactory( w ) {
		w->insertId( IdBrain, "brains.test" );
		addMyself( IdBrain );
	}
	virtual Brain * create ( Actor * a, ID id ) {
		Brain * ret = new Brain( a, 1, 10 );
		return ret;
	}
};
class FReflex : public ReflexFactory {
public:
	FReflex( World * w ): ReflexFactory( w ) {
		w->insertId( IdReflex, "reflexes.test" );
		addMyself( IdReflex );
	}
	virtual Reflex * create ( Actor * a, ID id ) {
		Reflex * ret = new Reflex( a, 1, 10 );
		return ret;
	}
};

//! [evsrc]
class	Ev : public EventSource	{
	int i;
public:
	Ev( World * w ) : EventSource( w ) { 
		i = 0;
	}
	void		doSteps		( int steps ) { 
		EventLine * eline = world()->eventLine( IdEventLine );
		if ( eline != NULL )
		{
			EventData * ed1 = new EventData( world(), 1 );
			ed1->payload().i_ = i*steps;
			eline->postActivity( ed1 );
			cout << "Posted event with payload " << i*steps << "\n";
			DEC_REF(ed1,ed1);
			i++;
		}
	}
};
//! [evsrc]

class FEvent : public EventFactory {
public:
	FEvent( World * w ): EventFactory( w ) {
		w->insertId( IdEvent, "events.test" );
		addMyself( IdEvent );
	}
	virtual EventSource * create ( ID id ) {
		Ev * ret = new Ev( world() );
		return ret;
	}
};

//! [sens]
class Sens : public Sensor	{
	EventData * ed_prev;
public:
	Sens( Actor * a ) : Sensor( a, 1, 10 )
	{
		cout << "Created custom sensor;\n";
		ed_prev = NULL;
	}
	void doSteps(int steps)
	{
		EventLine * eline = actor()->world()->eventLine( IdEventLine );
		if ( eline != NULL )
		{
			EventData * ed = eline->firstEventData();
			EventData * ed_first = ed;
			while ( ed != NULL )
			{
				if ( ed == ed_prev )
					break;
				cout << "Sensed payload " << ed->payload().i_ << ";\n";
				ed = nextEventData_(ed);
			}
			ed_prev = ed_first;
		}
	}
};
//! [sens]

class FSensor : public SensorFactory {
public:
	FSensor( World * w ): SensorFactory( w ) {
		w->insertId( IdSensor, "sensors.test" );
		addMyself( IdSensor );
	}
	virtual Sensor * create ( Actor * a, ID id ) {
		Sens * ret = new Sens( a );
		return ret;
	}
};


int main ()
{
	if ( initAprilLibrary() == false )
	{
		cerr << "Error! Failed to initialise april library!\n";
		return 1;
	}
	
	World * w = new World( "world-name", WORLD_ENERGY );
	cout << "World has been created!\n";
	
	FActor * f_actor = new FActor( w );
	DEC_REF(f_actor,f_actor);
	FSensor * f_sensor = new FSensor( w );
	DEC_REF(f_sensor,f_sensor);
	FActuator * f_actuator = new FActuator( w );
	DEC_REF(f_actuator,f_actuator);
	FBrain * f_brain = new FBrain( w );
	DEC_REF(f_brain,f_brain);
	FReflex * f_reflex = new FReflex( w );
	DEC_REF(f_reflex,f_reflex);
	FEvent * f_event = new FEvent( w );
	DEC_REF(f_event,f_event);
	
	
	//! [mainloop]
	EventLine * evline = new EventLine( w, IdEventLine );
	w->start();
	Actor *	actor = w->createActor( IdKind );
	if ( actor )
	{
		Ev * evsrc = static_cast<Ev *>( w->createEvent( IdEvent ) );
		if ( evsrc != NULL )
		{
			
			for ( int i = 0; i < 20; i++ )
			{
				w->advance();
			}
			
			DEC_REF(evsrc,evsrc);
		}
		DEC_REF(actor,actor);
	}
	w->stop();
	DEC_REF(evline,evline);
	//! [mainloop]
	
	DEC_REF(w,w);
	AprilLibrary::remWorld( w );
	cout << "World has been destroyed!\n";
	
	endAprilLibrary();
	
	return 0;
}

