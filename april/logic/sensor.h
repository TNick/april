/* ========================================================================= */
/* ------------------------------------------------------------------------- */
/*!
  \file			sensor.h
  \date			Apr 2013
  \author		TNick

  \brief		Contains the definition for Sensor class


*//*


 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Please read COPYING and README files in root folder
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
#ifndef __SENSOR_INC__
#define __SENSOR_INC__
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
class	Actor;

/*  DEFINITIONS    ========================================================= */
//
//
//
//
/*  CLASS    --------------------------------------------------------------- */

/**
*	@brief	Base class for sensors
*/
class
	APRILSHARED_EXPORT
	Sensor		: public ActorComp		{
	BBM_TRACK( Sensor );

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
	Sensor				( Actor * actor );
	
	//! constructor; sets cost and packed energy
	Sensor				( Actor * actor, quint64 cost, quint64 energy );

	//! constructor method; creates and loads a sensor from QSettings
	static Sensor *		fromStg					( Actor * a, QSettings & s );

protected:

	//! destructor;
	virtual				~Sensor			( void );

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

};	/*	class Sensor	*/

/*  CLASS    =============================================================== */
//
//
//
//

}   //  namespace   april

#endif // __SENSOR_INC__
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
