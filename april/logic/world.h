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
class Director;
class World;
class EventSource;
class Actuator;
class Brain;
class Sensor;
class Reflex;
class EventLine;

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
	friend class Director;
	friend class EventSource;
	friend class Factory;
	friend class EventLine;
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

	//! associated file
	QString						s_file_;
	
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
	
	//! the list of event lines
	QMap<ID,EventLine*>			event_lines_;
	
	//! the instance that manages the show
	Director *					director_;

	/*  DATA    ============================================================ */
	//
	//
	//
	//
	/*  FUNCTIONS    ------------------------------------------------------- */

public:

	//! constructor; general use
	World				( const QString & name, quint64 tot_energ );

	//! constructor method; creates and loads a world from QSettings
	Q_REQUIRED_RESULT
	static World *		fromStg				( QSettings & s );
	
	//! constructor method; creates and loads a world from a file
	Q_REQUIRED_RESULT
	static World *		fromStg				(
			const QString &			s_file,
			QString &				s_err
			);

protected:

	/**
	*	@brief	destructor;
	*/
	virtual				~World				( void );


public:

	//! the name of this world
	const QString &		name				( void ) const
	{ return s_name_; }

	//! current time in this world
	quint64				currentTime			( void ) const
	{ return time_; }
	
	//! one unit of time passed
	void				advance				( void );
	
	//! name of the factory that created this instance
	virtual QString		factoryName			( void ) const;

	//! associated file
	const QString &		associatedFile		( void ) const
	{ return s_file_; }

	//! has associated file
	bool				hasAssociatedFile	( void ) const
	{ return s_file_.isEmpty() == false; }
	
	//! change associated file
	void				setAssociatedFile	( const QString & s_val )
	{ s_file_ = s_val; }
	

	/* OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO */
	/** @name Director
	 */
	///@{
	
public:

	//! get the director
	inline Director *			director			( void ) const
	{ return director_; }
	
	//! change the director (the world will get a new reference for it)
	bool						setDirector			( Director * new_val );
	
	
	///@}
	/* ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo */


	/* OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO */
	/** @name Running
	 */
	///@{

public:

	/**
	*	@brief	starts this world
	*/
	bool				start				( void );

	/**
	*	@brief	stops this world
	*/
	void				stop				( void );

	/**
	*	@brief	tell if this world is running
	*/
	bool				isRunning			( void ) const
	{ return b_running_; }

protected:

	//! director uses this method to update the time
	void				stepTime			( void )
	{ time_++; }


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
	
	//! allocate a new unique id and assign provided description
	ID				addNewId		( const QString & s_name = QString() )
	{ return uid_.addNew( s_name ); }
	
	//! check if provided description exists; create a new one if not
	ID				checkAddId		( const QString & s_name )
	{ return uid_.checkAdd( s_name ); }
	
	//! check if provided description exists; set this one if not
	void			checkAddId		( ID id, const QString & s_name )
	{ uid_.checkAdd( id, s_name ); }

	//! get the string associated with an identifier
	QString			nameForId		( ID id )
	{ return uid_.name( id ); }

	//! tell if the two unique ID provides are the same
	bool			sameUId			( World * other ) const
	{ return uid_ == other->uid_; }

	//! generate an unique name based on a pattern
	QString			createIdName	( const QString & s_pattern )
	{ return uid_.createName( s_pattern ); }

	//! allocated ids
	QList<ID>		allocatedIds	( void ) const
	{ return uid_.ids(); }

	//! tell if an ID is assigned
	bool			isIDAssigned	( ID id ) const
	{ return uid_.isAssigned( id ); }
	
	///@}
	/* ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo */


	/* OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO */
	/** @name Actor related methods
	 */
	///@{

public:

	//! first in the list of actors (alive or recently dead)
	Actor *			firstActor			( void ) const;

	//! get nth actor (NULL if out of bounds)
	Actor *			actorAt				( int i ) const;

	//! an actor is being killed and its energy transferred to world
	/**
	 * This is simply a shortcut to Actor::killMe
	 * @param a The actor to kill
	 * @return true if everything went well (well, bad for the actor)
	 */
	bool			killActor			( Actor * a );
	
protected:

	//! used by the Actor class to insert itself
	bool			addActor			( Actor * act );

	//! used by the Actor class to remove itself
	bool			remActor			( Actor * act );

	///@}
	/* ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo */
	
	
	/* OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO */
	/** @name EventSource related methods
	 */
	///@{
	
public:
	
	//! first in the list of events (alive or recently dead)
	EventSource *	firstEvent			( void ) const;

protected:

	//! used by the EventSource class to insert itself
	bool			addEvent			( EventSource * act );

	//! used by the EventSource class to remove itself
	bool			remEvent			( EventSource * act );
	
	///@}
	/* ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo */

	
	/* OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO */
	/** @name Eventlines related methods
	 */
	///@{
	
public:
	
	inline EventLine *	eventLine			( ID id )
	{ return event_lines_.value( id, NULL ); }
	
protected:

	//! used by the EventLine class to insert itself
	bool			addEventLine		( EventLine * el, ID id );
	
	//! used by the EventLine class to remove itself
	bool			remEventLine		( EventLine * el, ID id );

	//! access to event lines in the world - first
	QMap<ID,EventLine*>::ConstIterator	firstEventLine		( void )
	{ return event_lines_.constBegin(); }

	//! access to event lines in the world - end
	QMap<ID,EventLine*>::ConstIterator	endEventLine		( void )
	{ return event_lines_.constEnd(); }

	///@}
	/* ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo */


	/* OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO */
	/** @name Factories added, removed and searched here
	 */
	///@{
	
public:

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
	
	

	//! add one to the list of actor factories
	ActorFactory*	findActorFactory	( const QString & s_name );

	//! add one to the list of actuator factories
	ActuatorFactory*findActuatorFactory	( const QString & s_name );

	//! add one to the list of sensor factories
	SensorFactory*	findSensorFactory	( const QString & s_name );

	//! add one to the list of brain factories
	BrainFactory*	findBrainFactory	( const QString & s_name );

	//! add one to the list of event factories
	EventFactory*	findEventFactory	( const QString & s_name );

	//! add one to the list of event factories
	ReflexFactory*	findReflexFactory	( const QString & s_name );
	
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
	EventSource *	createEvent			( ID id );
	
	//! create a reflex
	Reflex *		createReflex		( Actor * actor, ID id );
	
	///@}
	/* ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo */


	/* OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO */
	/** @name Save and load the world
	 */
	///@{

public:

	//! save the world (only when the world is stopped)
	virtual bool	save				( QSettings & stg ) const;
	
	//! load the world (only when the world is stopped)
	virtual bool	load				( QSettings & stg );


	//! save the world (only when the world is stopped)
	virtual bool	saveAsStg			( 
			const QString &			s_file,
			QString &				s_err
			) const;

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
