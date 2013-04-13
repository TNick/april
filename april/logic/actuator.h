/* ========================================================================= */
/* ------------------------------------------------------------------------- */
/*!
  \file			actuator.h
  \date			Apr 2013
  \author		TNick

  \brief		Contains the definition for Actuator class


*//*


 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Please read COPYING and README files in root folder
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
#ifndef __ACTUATOR_INC__
#define __ACTUATOR_INC__
//
//
//
//
/*  INCLUDES    ------------------------------------------------------------ */

#include    <april/april.h>
#include    <april/logic/actorcomp.h>

/*  INCLUDES    ============================================================ */
//
//
//
//
/*  DEFINITIONS    --------------------------------------------------------- */

namespace   april    {

/*  DEFINITIONS    ========================================================= */
//
//
//
//
/*  CLASS    --------------------------------------------------------------- */

/**
*	@brief	Base class for actuators
*
*	This is the output of an actor. This may be a hand or a foot, for example,
*	or the generic action of moving.
*/
class
	APRILSHARED_EXPORT
	Actuator		: public ActorComp		{
	BBM_TRACK( Actuator );

	//
	//
	//
	//
	/*  DEFINITIONS    ----------------------------------------------------- */

	/*  DEFINITIONS    ===================================================== */
	//
	//
	//
	//
	/*  DATA    ------------------------------------------------------------ */

private:



	/*  DATA    ============================================================ */
	//
	//
	//
	//
	/*  FUNCTIONS    ------------------------------------------------------- */

public:

	//! constructor; sets cost and packed energy to 0
	Actuator			( Actor * actor );
	
	//! constructor; sets cost and packed energy
	Actuator			( Actor * actor, quint64 cost, quint64 energy );
	
	//! constructor method; creates and loads an Actuator from QSettings
	Q_REQUIRED_RESULT
	static Actuator *	fromStg				( Actor * a, QSettings & stg );

protected:

	/**
	*	@brief	destructor;
	*/
	virtual				~Actuator		( void );

public:

	//! save to a QSettings object
	virtual bool		save					( QSettings & s ) const;
	
	//! load from a QSettings object
	virtual bool		load					( QSettings & s );


	/*  FUNCTIONS    ======================================================= */
	//
	//
	//
	//
	
};	/*	class Actuator	*/

/*  CLASS    =============================================================== */
//
//
//
//

}   //  namespace   april

#endif // __ACTUATOR_INC__
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
