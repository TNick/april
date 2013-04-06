/* ========================================================================= */
/* ------------------------------------------------------------------------- */
/*!
  \file			uniqueid.h
  \date			Apr 2013
  \author		TNick

  \brief		Contains the definition for UniqueId class


*//*


 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Please read COPYING and README files in root folder
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
#ifndef __UNIQUEID_INC__
#define __UNIQUEID_INC__
//
//
//
//
/*  INCLUDES    ------------------------------------------------------------ */

#include    <april/april.h>
#include	<QMap>

/*  INCLUDES    ============================================================ */
//
//
//
//
/*  DEFINITIONS    --------------------------------------------------------- */

class	QSettings;

namespace   april    {

//! the type for an ID
typedef	quint64			ID;


//! special codes for ID values
enum	UniqueIdSpecialCodes	{

	//! defines an invalid id
	InvalidId = 0
	
};

/*  DEFINITIONS    ========================================================= */
//
//
//
//
/*  CLASS    --------------------------------------------------------------- */

/**
*	@brief	Provides support for unique identificators
*/
class
	APRILSHARED_EXPORT
	UniqueId				{
	BBM_TRACK( UniqueId );

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

	//! the name for this provider (used to save settings)
	QString					my_name_;

	//! all the values that we know of
	QMap<ID,QString>		map_;

	//! most likelly unassigned id
	ID						first_free_;


	/*  DATA    ============================================================ */
	//
	//
	//
	//
	/*  FUNCTIONS    ------------------------------------------------------- */

public:

	//! create a new codes provider or load an existing one
	UniqueId( const QString & s_name );

private:
	
	//! constructor
	UniqueId(){}

public:
	
	//! destructor
	~UniqueId();
	
public:

	//! get the string associated with an identifier
	QString			name			( ID id );

	//! get the id associated with a name
	/**
	 * @param s_name the string to search (case sensitive)
	 * @return the id that was found or InvalidId
	 */
	ID				value			( const QString & s_name );

	//! insert a new ID or update the string associated with one
	void			insert			( ID id, const QString & s_name );
	
	//! allocate a new unique id and assigne provided description
	ID				addNew			( const QString & s_name = QString() );
	
	//! check if provided description exists; create a new one if not
	ID				checkAdd		( const QString & s_name );
	
	//! check if provided description exists; set this one if not
	void			checkAdd		( ID id, const QString & s_name );

	//! save the list of values and strings
	void			save			( QSettings & stg );

	//! load the list of values and strings; current content is wiped out
	void			load			( QSettings & stg );
	

	/*  FUNCTIONS    ======================================================= */
	//
	//
	//
	//

};	/*	class UniqueId	*/

/*  CLASS    =============================================================== */
//
//
//
//

}   //  namespace   april

#endif // __UNIQUEID_INC__
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
