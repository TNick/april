/* ========================================================================= */
/* ------------------------------------------------------------------------- */
/*!
  \file			actorcomp.h
  \date			Apr 2013
  \author		TNick

  \brief		Contains the definition for ActorComp class


*//*


 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Please read COPYING and README files in root folder
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
#ifndef __ACTORCOMP_INC__
#define __ACTORCOMP_INC__
//
//
//
//
/*  INCLUDES    ------------------------------------------------------------ */

#include    <april/april.h>
#include    <april/logic/component.h>

/*  INCLUDES    ============================================================ */
//
//
//
//
/*  DEFINITIONS    --------------------------------------------------------- */

namespace   april    {
class	Actor;
class	World;

/*  DEFINITIONS    ========================================================= */
//
//
//
//
/*  CLASS    --------------------------------------------------------------- */

/**
*	@brief	Base class for components of an Actor
*/
class
	APRILSHARED_EXPORT
	ActorComp		: public Component		{
	BBM_TRACK( ActorComp );

	//
	//
	//
	//
	/*  DEFINITIONS    ----------------------------------------------------- */

	friend class Actor;
	friend class World;
	
	/*  DEFINITIONS    ===================================================== */
	//
	//
	//
	//
	/*  DATA    ------------------------------------------------------------ */

private:

	//! parent actor
	Actor *					actor_;

	//! cost per time unit
	quint64					cost_;

	//! ammount of energy packed inside this component
	quint64					energy_;
	
	/*  DATA    ============================================================ */
	//
	//
	//
	//
	/*  FUNCTIONS    ------------------------------------------------------- */

public:

	//! constructor; sets cost and packed energy to 0
	ActorComp			( Actor * actor );

	//! constructor; sets cost and packed energy
	ActorComp			( Actor * actor, quint64 cost, quint64 energy );

protected:

	//! destructor;
	virtual				~ActorComp		( void );

public:

	//! save to a QSettings object
	virtual bool		save					( QSettings & s ) const;
	
	//! load from a QSettings object
	virtual bool		load					( QSettings & s );

	//! tell if this is a valid instance
	inline bool			isValid		( void ) const
	{ return ( ( cost_ > 0 ) && ( energy_ > 0 ) ); }

	//! parent actor
	inline Actor *		actor		( void ) const
	{ return actor_; }
	
	//! get the name of my ID
	QString				myName		( void ) const;

	//! cost per time unit
	/**
	 *	This value is requested by the actor when started
	 *	and then cached. Changing this value after this (like using
	 *	setCost()) has no effect on the actor.
	 *
	 *	@return the cost
	 */
	inline quint64		cost		( void ) const
	{ return cost_; }


	//! ammount of energy packed inside this component
	inline quint64		energy		( void ) const
	{ return energy_; }


protected:

	//! set cost per time unit
	void				setCost		( quint64 new_val )
	{ cost_ = new_val; }

	//! set cost per time unit
	void				setEnergy	( quint64 new_val )
	{ energy_ = new_val; }

	//! perform steps (called by the Actor)
	virtual void		doSteps		( int steps )
	{ Q_UNUSED( steps ); }



	/*  FUNCTIONS    ======================================================= */
	//
	//
	//
	//

};	/*	class ActorComp	*/

/*  CLASS    =============================================================== */
//
//
//
//

}   //  namespace   april

#endif // __ACTORCOMP_INC__
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
