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
#include	<libbbb/1/amorph.h>

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
	quint64					cost_;

	//! alive or dead
	bool					alive_;

	//! associated data
	Amorph					payload_;




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

	//! associated data
	Amorph &			payload					( void )
	{ return payload_; }


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
