
#include <iostream>

#include <april/aprillibrary.h>
#include <april/logic/world.h>
//! [incdirfactory]
#include <april/logic/factory.h>
#include <april/logic/sensorfactory.h>
#include <april/logic/eventfactory.h>
#include <april/logic/actuatorfactory.h>
#include <april/logic/actorfactory.h>
#include <april/logic/brainfactory.h>
#include <april/logic/reflexfactory.h>
//! [incdirfactory]

#include <april/logic/sensor.h>
#include <april/logic/eventsource.h>
#include <april/logic/actuator.h>
#include <april/logic/actor.h>
#include <april/logic/brain.h>
#include <april/logic/reflex.h>

using namespace std;
using namespace april;

enum	Constants		{
	WORLD_ENERGY = 10000,
	IdKind = 1,
	IdBrain,
	IdSensor,
	IdReflex,
	IdActuator,
	IdEvent
};


//! [evproxy]
class	Ev : public EventSource	{
public:
	Ev( World * w ) : EventSource( w ) { }
	void		doSteps		( int ) { }
};
//! [evproxy]

//! [fproxy]
class FActor : public ActorFactory {
public:
	FActor( World * w ) : ActorFactory( w ) {
		w->insertId( IdKind, "kinds.test" );
		addMyself( IdKind );
	}
	virtual Actor * create ( ID ) {
		Actor * ret = new Actor( world() ); 
		setDNA( ret );
		return ret;
	}
	virtual void copyDefaultDNA ( DNA & destination ) { 
		destination = defaultDNA();
	}
	
};
class FSensor : public SensorFactory {
public:
	FSensor( World * w ): SensorFactory( w ) {
		w->insertId( IdSensor, "sensors.test" );
		addMyself( IdSensor );
	}
	virtual Sensor * create ( Actor * a, ID ) {
		Sensor * ret = new Sensor( a );
		return ret;
	}
};
class FEvent : public EventFactory {
public:
	FEvent( World * w ): EventFactory( w ) {
		w->insertId( IdEvent, "events.test" );
		addMyself( IdEvent );
	}
	virtual EventSource * create ( ID ) {
		Ev * ret = new Ev( world() );
		return ret;
	}
};
class FActuator : public ActuatorFactory {
public:
	FActuator( World * w ): ActuatorFactory( w ) {
		w->insertId( IdActuator, "actuators.test" );
		addMyself( IdActuator );
	}
	virtual Actuator * create ( Actor * a, ID ) {
		Actuator * ret = new Actuator( a );
		return ret;
	}
};
class FBrain : public BrainFactory {
public:
	FBrain( World * w ): BrainFactory( w ) {
		w->insertId( IdBrain, "brains.test" );
		addMyself( IdBrain );
	}
	virtual Brain * create ( Actor * a, ID ) {
		Brain * ret = new Brain( a );
		return ret;
	}
};
class FReflex : public ReflexFactory {
public:
	FReflex( World * w ): ReflexFactory( w ) {
		w->insertId( IdReflex, "reflexes.test" );
		addMyself( IdReflex );
	}
	virtual Reflex * create ( Actor * a, ID ) {
		Reflex * ret = new Reflex( a );
		return ret;
	}
};
//! [fproxy]

int main ()
{
	if ( initAprilLibrary() == false )
	{
		cerr << "Error! Failed to initialise april library!\n";
		return 1;
	}
	
	World * w = new World( "world-name", WORLD_ENERGY );
	cout << "World has been created!\n";
	
	
	//! [new]
	FActor * f_actor = new FActor( w );
	DEC_REF(f_actor,f_actor);
	FSensor * f_sensor = new FSensor( w );
	DEC_REF(f_sensor,f_sensor);
	FEvent * f_event = new FEvent( w );
	DEC_REF(f_event,f_event);
	FActuator * f_actuator = new FActuator( w );
	DEC_REF(f_actuator,f_actuator);
	FBrain * f_brain = new FBrain( w );
	DEC_REF(f_brain,f_brain);
	FReflex * f_reflex = new FReflex( w );
	DEC_REF(f_reflex,f_reflex);
	//! [new]
	
	
	
	DEC_REF(w,w);
	AprilLibrary::remWorld( w );
	cout << "World has been destroyed!\n";
	
	endAprilLibrary();
	
	return 0;
}

