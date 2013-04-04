/* ========================================================================= */
/* ------------------------------------------------------------------------- */
/*!
  \file			actor.h
  \date			Apr 2013
  \author		TNick

  \brief		Contains the definition for Actor class


*//*


 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Please read COPYING and README files in root folder
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
#ifndef __ACTOR_INC__
#define __ACTOR_INC__
//
//
//
//
/*  INCLUDES    ------------------------------------------------------------ */

#include    <april/april.h>
#include    <april/logic/component.h>
#include    <april/logic/dna.h>

/*  INCLUDES    ============================================================ */
//
//
//
//
/*  DEFINITIONS    --------------------------------------------------------- */

namespace   april    {

class World;
class Sensor;
class Actuator;
class Brain;
class Actor;
class Reflex;

/*  DEFINITIONS    ========================================================= */
//
//
//
//
/*  CLASS    --------------------------------------------------------------- */

/**
*	@brief	An active ocupier of the world
*
*	When an actor is first constructed it is not alive. This allows the
*	caller to initialise it, decode, DNA, ... Once the actor is made alive
*	using makeAlive() it will recieve time ticks from the World via
*	doSteps(). Because the world may be runned in a multi-thread 
*	environment doSteps() also recieves the number of time units that passed
*	since the actor was last called.
*
*	doSteps() substracts the constant cost from the current energy and
*	if the energy is exhausted the actor dies (sends World::actorDies() to
*	parent world). Same happens if the actor reaches its \b death_ age.
*
*	doSteps() iterates components and sends them ActorComp::doSteps(). 
*	The order is following:
*	- sensors (may generate input for reflexes and brains)
*	- reflexes (may generate input for brains and actuators)
*	- brains (may generate input for actuators)
*	- actuators (may alter outside world)
*
*/
class
	APRILSHARED_EXPORT
	Actor		: public Component		{
	BBM_TRACK( Actor );

	//
	//
	//
	//
	/*  DEFINITIONS    ----------------------------------------------------- */

	friend class Sensor;
	friend class Actuator;
	friend class World;
	friend class Reflex;
	friend class Brain;
	friend class ActorFactory;
	
	/*  DEFINITIONS    ===================================================== */
	//
	//
	//
	//
	/*  DATA    ------------------------------------------------------------ */

private:

	//! the world where we belong
	World *					world_;

	//! header for the list of sensors
	List2Dh					sensors_;
	
	//! header for the list of actuators
	List2Dh					actuators_;
	
	//! header for the list of reflexes
	List2Dh					reflexes_;
	
	//! header for the list of brains
	List2Dh					brains_;
	
	//! the DNA of this actor
	DNA						dna_;
	
	//! the kind cached here (also present in DNA)
	ID						kind_;

	//! time of birth
	quint64					birth_;
	
	//! time of death
	quint64					death_;
	
	//! current age
	quint64					age_;
	
	//! current energy reserve
	quint64					energy_;
	
	//! running cost (energy substracted from energy_ on each time step)
	/**
	 * This value is cached here from DNA::cost().
	 */
	quint64					cost_;

	//! alive or dead
	bool					alive_;




	/*  DATA    ============================================================ */
	//
	//
	//
	//
	/*  FUNCTIONS    ------------------------------------------------------- */

public:


	/**
	*	@brief	constructor; creates an invalid actor that needs 
	*	further initialisation
	*/
	Actor				( World * w );

protected:

	/**
	*	@brief	destructor;
	*/
	virtual				~Actor					( void );

public:

	//! the world where we belong
	inline World *		world					( void ) const
	{ return world_; }


public:
	
	
	//! first sensor in internal list
	Sensor *			firstSensor				( void ) const;
	
	//! first actuator in internal list
	Actuator *			firstActuator			( void ) const;
	
	//! first reflex in internal list
	Reflex *			firstReflex				( void ) const;
	
	//! first brain in internal list
	Brain *				firstBrain				( void ) const;


	//! tell the kind
	inline ID			kind					( void ) const
	{ return kind_; }
	
	//! get the name of the kind (shortcut for UniqueId::name() )
	QString				kindName				( void ) const;
	
	//! the DNA of this actor
	const DNA &			dna						( void ) const
	{ return dna_; }

	//! tell the date of birth
	inline quint64		birth					( void ) const
	{ return birth_; }
	
	//! tell the date of death
	inline quint64		death					( void ) const
	{ return death_; }
	
	//! tell the age of this actor
	inline quint64		age						( void ) const
	{ return age_; }
	
	//! tell the life span of this actor
	inline quint64		toLive					( void ) const
	{ return death_-birth_; }
	
	//! energy reserve
	quint64				energy					( void ) const
	{ return energy_; }
	
	//! energy cost
	quint64				cost					( void ) const
	{ return cost_; }

	//! alive or dead
	bool				isAlive					( void ) const
	{ return alive_; }
	
	//! tell if this is the moment when the agent dies
	inline bool			dies					( void ) const
	{ return (birth_+age_ >= death_); }

protected:

	//! set the DNA to provided sequence (intended for ActorFactory)
	inline void			setDNA					( const DNA & src )
	{ dna_ = src; }

	//! load the components of the actor from the DNA
	bool				decodeDNA				( void );

	//! add an Actuator
	bool				addActuator				( Actuator * act );

	//! add a Sensor
	bool				addSensor				( Sensor * act );

	//! add a Reflex
	bool				addReflex				( Reflex * act );

	//! add a Brain
	bool				addBrain				( Brain * act );

	//! perform steps (called by the World)
	void				doSteps					( int steps  = 1 );

	//! make the actor alive
	void				makeAlive				( void );

	//! total energy packed in this agent (the agent itself and the compoenets)
	quint64				totalEnergy				( void );

	//! make the actor alive (used by the world to initialise actor)
	void				setEnergy				( quint64 new_val )
	{ energy_ = new_val; }


	/*  FUNCTIONS    ======================================================= */
	//
	//
	//
	//

};	/*	class Actor	*/

/*  CLASS    =============================================================== */
//
//
//
//

}   //  namespace   april

#endif // __ACTOR_INC__
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
