/* ========================================================================= */
/* ------------------------------------------------------------------------- */
/*!
  \file			factory.h
  \date			Apr 2013
  \author		TNick
  
  \brief		Contains the definition for Factory class
  
  
*//*


 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Please read COPYING and README files in root folder
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
#ifndef __FACTORY_INC__
#define __FACTORY_INC__
//
//
//
//
/*  INCLUDES    ------------------------------------------------------------ */

#include    <april/april.h>
#include    <april/logic/uniqueid.h>

/*  INCLUDES    ============================================================ */
//
//
//
//
/*  DEFINITIONS    --------------------------------------------------------- */

namespace   april    {

class	World;
class	ActorComp;

//! types of factories
enum	FactoryType		{
	FTyGeneric = 0,
	FTyActor,
	FTyActuator,
	FTyBrain,
	FTyEvent,
	FTyReflex,
	FTySensor,
	FTyWorld,
	
	FTyMax
};


/*  DEFINITIONS    ========================================================= */
//
//
//
//
/*  CLASS    --------------------------------------------------------------- */

/**
*	@brief	Base class for factory classes
*/
class
		APRILSHARED_EXPORT
		Factory		: public libbbb::RefCnt, public MemTrack		{
	BBM_TRACK( Factory );
	
	//
	//
	//
	//
	/*  DEFINITIONS    ----------------------------------------------------- */
	
	friend class ActorComp;
	
	/*  DEFINITIONS    ===================================================== */
	//
	//
	//
	//
	/*  DATA    ------------------------------------------------------------ */
	
private:
	
	//! the world where this class is hosted
	World *				w_;
	
	//! storage space for one name (usually there will only be one)
	QString				s_name_for_id_;
	
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
	Factory						( World * w );
	
protected:
	
	/**
	*	@brief	destructor;
	*/
	virtual						~Factory		( void );
	
public:
	
	//! the generic type of the factory
	virtual FactoryType			factoryType		( void )
	{ return FTyGeneric; }
	
	//! the world that hosts us;
	inline World *				world			( void ) const
	{ return w_; }
	
	//! name of the element represented by provided ID
	virtual const QString &		name			( ID id ) const
	{ Q_UNUSED( id ); return s_name_for_id_; }
	
	//! get the default DNA sequence for a particular ID
	virtual QList<qreal>		averageDNA		( ID id ) const
	{ Q_UNUSED( id ); return QList<qreal>(); }
	
	//! save to a QSettings object
	virtual bool				save			( QSettings & s ) const;
	
	//! load from a QSettings object
	virtual bool				load			( QSettings & s );

protected:
	
	//! chang the name of the element represented by provided ID
	void						setName			( const QString & s )
	{ s_name_for_id_ = s; }
	
	//! set the packed energy and the ammount of energy consumed on each time unit
	/**
	 * This is a simple shortcut to World::setEnergy().
	 * If the world does not have that much energy the opperation is dropped.
	 *
	 * @param comp the component where this is to be set
	 * @param energy packed energy (will be substracted from world's free energy)
	 * @param cost energy consumed on each step by this component
	 * @return true if the opperation succeded
	 */
	bool						setEnergy		(
			ActorComp *				comp, 
			quint64					energy, 
			quint64					cost 
			);


	/*  FUNCTIONS    ======================================================= */
	//
	//
	//
	//
	
};	/*	class Factory	*/

/*  CLASS    =============================================================== */
//
//
//
//

}   //  namespace   april

#endif // __FACTORY_INC__
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
