/* ========================================================================= */
/* ------------------------------------------------------------------------- */
/*!
  \file			world.h
  \date			Apr 2013
  \author		TNick

  \brief		Contains the definition for World class


*//*


 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Please read COPYING and README files in root folder
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
#ifndef __WORLD_INC__
#define __WORLD_INC__
//
//
//
//
/*  INCLUDES    ------------------------------------------------------------ */

#include    <april/april.h>
#include    <april/logic/uniqueid.h>
#include    <april/logic/component.h>

/*  INCLUDES    ============================================================ */
//
//
//
//
/*  DEFINITIONS    --------------------------------------------------------- */

namespace   april    {

class ActorComp;
class Actor;
class World;
class Event;
class Actuator;
class Brain;
class Sensor;
class Reflex;

class ActorFactory;
class ActuatorFactory;
class BrainFactory;
class SensorFactory;
class EventFactory;
class ReflexFactory;

/*  DEFINITIONS    ========================================================= */
//
//
//
//
/*  CLASS    --------------------------------------------------------------- */

/**
*	@brief	A world hosts agents, events, environment
*/
class
	APRILSHARED_EXPORT
	World		: public Component		{
	BBM_TRACK( World );

	//
	//
	//
	//
	/*  DEFINITIONS    ----------------------------------------------------- */

	friend class Actor;
	friend class Event;
	friend class Factory;
	friend class ActorFactory;
	friend class ActuatorFactory;
	friend class BrainFactory;
	friend class SensorFactory;
	friend class EventFactory;
	friend class ReflexFactory;

	/*  DEFINITIONS    ===================================================== */
	//
	//
	//
	//
	/*  DATA    ------------------------------------------------------------ */

private:

	//! running status
	bool						b_running_:1;

	//! the name of this world
	QString						s_name_;
		
	//! current time in this world
	quint64						time_;
	
	//! ammount of energy in this world
	quint64						energy_all_;
	
	//! ammount of free energy in this world
	quint64						energy_free_;

	//! the list of actors (alive or recently dead)
	List2Dh						actors_;
	
	//! the list of events (alive or recently dead)
	List2Dh						events_;
	
	//! unique ID provider
	UniqueId					uid_;
	
	//! the list of actor factories
	QMap<ID,ActorFactory*>		actor_factories_;
	
	//! the list of actuator factories
	QMap<ID,ActuatorFactory*>	actuator_factories_;
		
	//! the list of brain factories
	QMap<ID,BrainFactory*>		brain_factories_;
		
	//! the list of sensor factories
	QMap<ID,SensorFactory*>		sensor_factories_;
		
	//! the list of event factories
	QMap<ID,EventFactory*>		event_factories_;
		
	//! the list of reflex factories
	QMap<ID,ReflexFactory*>		reflex_factories_;

	/*  DATA    ============================================================ */
	//
	//
	//
	//
	/*  FUNCTIONS    ------------------------------------------------------- */

public:


	/**
	*	@brief	constructor;
	*/
	World				( const QString & name, quint64 tot_energ );

protected:

	/**
	*	@brief	destructor;
	*/
	virtual				~World				( void );


public:

	//! current time in this world
	quint64				currentTime			( void ) const
	{ return time_; }
	
	//! one unit of time passed
	void				advance				( void );
	


	/* OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO */
	/** @name Running
	 */
	///@{

public:

	/**
	*	@brief	starts this world
	*/
	bool				start				( void )
	{ b_running_ = true; return true; }

	/**
	*	@brief	stops this world
	*/
	void				stop				( void )
	{ b_running_ = false; }

	/**
	*	@brief	tell if this world is running
	*/
	bool				isRunning			( void )
	{ return b_running_; }


	///@}
	/* ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo */


	/* OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO */
	/** @name Energy
	 */
	///@{

public:

	
	//! ammount of energy in this world
	quint64				energy				( void ) const
	{ return energy_all_; }
	
	//! ammount of free energy in this world
	quint64				energyFree			( void ) const
	{ return energy_free_; }	
	
	//! ammount of bounded energy in this world
	quint64				energyBounded		( void ) const
	{ return energy_all_ - energy_free_; }	
	
	//! sets the total ammout of energy in this world
	bool				setTotEnergy		( quint64 new_val );
	
protected:
	
	//! set the packed energy and the ammount of energy consumed on each time unit
	/**
	 * If the world does not have that much energy the opperation is dropped.
	 *
	 * @param comp the component where this is to be set
	 * @param energy packed energy (will be substracted from world's free energy)
	 * @param cost energy consumed on each step by this component
	 * @return true if the opperation succeded
	 */
	bool				setEnergy			(
			ActorComp *				comp, 
			quint64					energy, 
			quint64					cost 
			);

	///@}
	/* ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo */


	/* OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO */
	/** @name Factories
	 */
	///@{

public:

	//! the list of actor factories
	const QMap<ID,ActorFactory*> &		actorFactories		( void ) const
	{ return actor_factories_; }
	
	//! the list of actuator factories
	const QMap<ID,ActuatorFactory*> &	actuatorFactories	( void ) const
	{ return actuator_factories_; }
		
	//! the list of brain factories
	const QMap<ID,BrainFactory*> &		brainFactories		( void ) const
	{ return brain_factories_; }
		
	//! the list of sensor factories
	const QMap<ID,SensorFactory*> &		sensorFactories		( void ) const
	{ return sensor_factories_; }
		
	//! the list of event factories
	const QMap<ID,EventFactory*> &		eventFactories		( void ) const
	{ return event_factories_; }
		
	//! the list of reflex factories
	const QMap<ID,ReflexFactory*> &		reflexFactories		( void ) const
	{ return reflex_factories_; }


	//! the actor factory for specified ID
	ActorFactory*						actorFactory		( ID id ) const
	{ return actor_factories_.value( id, NULL ); }
	
	//! the actuator factory for specified ID
	ActuatorFactory*					actuatorFactory		( ID id ) const
	{ return actuator_factories_.value( id, NULL ); }
		
	//! the brain factory for specified ID
	BrainFactory*						brainFactory		( ID id ) const
	{ return brain_factories_.value( id, NULL ); }
		
	//! the sensor factory for specified ID
	SensorFactory*						sensorFactory		( ID id ) const
	{ return sensor_factories_.value( id, NULL ); }
		
	//! the event factory for specified ID
	EventFactory*						eventFactory		( ID id ) const
	{ return event_factories_.value( id, NULL ); }
		
	//! the event factory for specified ID
	ReflexFactory*						reflexFactory		( ID id ) const
	{ return reflex_factories_.value( id, NULL ); }
	

	///@}
	/* ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo */


	/* OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO */
	/** @name Unique Id's
	 */
	///@{

public:

	//! get the id associated with a name
	/**
	 * @param s_name the string to search (case sensitive)
	 * @return the id that was found or InvalidId
	 */	
	ID				idValue			( const QString & s_name )
	{ return uid_.value( s_name ); }

	//! insert a new ID or update the string associated with one
	void			insertId		( ID id, const QString & s_name )
	{ uid_.insert( id, s_name ); }
	
	//! allocate a new unique id and assigne provided description
	ID				addNewId		( const QString & s_name = QString() )
	{ return uid_.addNew( s_name ); }
	
	//! check if provided description exists; create a new one if not
	ID				checkAddId		( const QString & s_name )
	{ return uid_.checkAdd( s_name ); }

	//! get the string associated with an identifier
	QString			nameForId		( ID id )
	{ return uid_.name( id ); }


	///@}
	/* ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo */


	/* OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO */
	/** @name Actor related methods
	 */
	///@{

public:

	//! first in the list of actors (alive or recently dead)
	Actor *			firstActor			( void ) const;

protected:

	//! used by the Actor class to insert itself
	bool			addActor			( Actor * act );

	//! used by the Actor class to remove itself
	bool			remActor			( Actor * act );


	///@}
	/* ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo */
	
	
	/* OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO */
	/** @name Event related methods
	 */
	///@{

	
	//! first in the list of events (alive or recently dead)
	Event *			firstEvent			( void ) const;

protected:


	//! used by the Event class to insert itself
	bool			addEvent			( Event * act );

	//! used by the Event class to remove itself
	bool			remEvent			( Event * act );
	
	///@}
	/* ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo */


	/* OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO */
	/** @name Factories added and removed here
	 */
	///@{
	
protected:

	//! add one to the list of actor factories
	bool			addActorFactory		( ActorFactory * factory, ID id );

	//! add one to the list of actuator factories
	bool			addActuatorFactory	( ActuatorFactory * factory, ID id );

	//! add one to the list of sensor factories
	bool			addSensorFactory	( SensorFactory * factory, ID id );

	//! add one to the list of brain factories
	bool			addBrainFactory		( BrainFactory * factory, ID id );

	//! add one to the list of event factories
	bool			addEventFactory		( EventFactory * factory, ID id );

	//! add one to the list of event factories
	bool			addReflexFactory	( ReflexFactory * factory, ID id );
	

	//! add one to the list of actor factories
	bool			remActorFactory		( ActorFactory * factory, ID id );

	//! add one to the list of actuator factories
	bool			remActuatorFactory	( ActuatorFactory * factory, ID id );

	//! add one to the list of sensor factories
	bool			remSensorFactory	( SensorFactory * factory, ID id );

	//! add one to the list of brain factories
	bool			remBrainFactory		( BrainFactory * factory, ID id );

	//! add one to the list of event factories
	bool			remEventFactory		( EventFactory * factory, ID id );

	//! add one to the list of event factories
	bool			remReflexFactory	( ReflexFactory * factory, ID id );
	
	///@}
	/* ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo */


	/* OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO */
	/** @name Components are created here
	 */
	///@{

public:

	//! create an actor
	/**
	 * A factory is searched for this ID and, if found, it is requested
	 * to create an Actor.
	 *
	 * @param id_kind the id to search
	 * @return NULL for error, an actor otherwise
	 */
	Actor *			createActor			( ID id_kind );
	
	//! create an actuator
	Actuator *		createActuator		( Actor * actor, ID id );
	
	//! create a brain
	Brain *			createBrain			( Actor * actor, ID id );
	
	//! create a brain
	Sensor *		createSensor		( Actor * actor, ID id );
	
	//! create a brain
	Event *			createEvent			( ID id );
	
	//! create a reflex
	Reflex *		createReflex		( Actor * actor, ID id );
	
	///@}
	/* ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo */


	//! informed when the life of an actor ended
	void			actorDies			( Actor * actor );




	/*  FUNCTIONS    ======================================================= */
	//
	//
	//
	//

};	/*	class World	*/

/*  CLASS    =============================================================== */
//
//
//
//

}   //  namespace   april

#endif // __WORLD_INC__
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
