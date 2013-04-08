/* ========================================================================= */
/* ------------------------------------------------------------------------- */
/*!
  \file			uniqueid.cc
  \date			Apr 2013
  \author		TNick

  \brief		Contains the implementation of UniqueId class


*//*


 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Please read COPYING and README files in root folder
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
//
//
//
//
/*  INCLUDES    ------------------------------------------------------------ */

#include	"uniqueid.h"
#include	<QSettings>

/*  INCLUDES    ============================================================ */
//
//
//
//
/*  DEFINITIONS    --------------------------------------------------------- */

using namespace april;

/*  DEFINITIONS    ========================================================= */
//
//
//
//
/*  DATA    ---------------------------------------------------------------- */

/*  DATA    ================================================================ */
//
//
//
//
/*  CLASS    --------------------------------------------------------------- */

/* ------------------------------------------------------------------------- */
UniqueId::UniqueId( const QString & s_name )
	: my_name_( s_name ),
	  map_(),
	  first_free_(InvalidId)
{
	/* stub */
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
UniqueId::~UniqueId()
{
	/* stub */
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
QString			UniqueId::name		( ID id )
{
	return map_.value( id, QString() );
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
ID				UniqueId::value		( const QString & s_name )
{
	if ( s_name.isEmpty() )
		return InvalidId;
	return map_.key( s_name, InvalidId );
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void			UniqueId::insert	( ID id, const QString & s_name )
{
	map_.insert( id, s_name );
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
ID			UniqueId::addNew	( const QString & s_name )
{
	while ( map_.contains( first_free_ ) )
	{
		first_free_++;
	}
	insert( first_free_, s_name );
	first_free_++;
	return first_free_-1;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
ID				UniqueId::checkAdd	( const QString & s_name )
{
	if ( s_name.isEmpty() )
		return InvalidId;
	ID i = map_.key( s_name, InvalidId );
	if ( i == InvalidId )
	{
		i =  addNew( s_name );
	}
	return i;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void			UniqueId::checkAdd	( ID id, const QString & s_name )
{
	QMap<ID,QString>::Iterator itr = map_.find( id );
	if ( itr == map_.end() )
	{
		insert( id, s_name );
	}
	else if ( itr.value().isEmpty() )
	{
		itr.value() = s_name;
	}
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool			UniqueId::save		( QSettings & stg ) const
{
	quint64 i = 0;
	stg.beginGroup( "UniqueId" );
	stg.setValue( "first_free_", first_free_ );
	stg.setValue( "my_name_", my_name_ );
	
	stg.beginWriteArray( "map_" );
	QMap<ID,QString>::ConstIterator itr = map_.constBegin();
	QMap<ID,QString>::ConstIterator itr_e = map_.constEnd();
	while ( itr != itr_e )
	{
		stg.setArrayIndex( i );
		stg.setValue( "id", itr.key() );
		stg.setValue( "value", itr.value() );
	
		itr++;
		i++;
	}
	stg.endArray();
	
	stg.endGroup();
	return true;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool			UniqueId::load		( QSettings & stg )
{
	QString s;
	ID key;
	stg.beginGroup( "UniqueId" );
	first_free_ = stg.value( "first_free_", InvalidId+1 ).toULongLong();
	my_name_ = stg.value( "my_name_" ).toString();
	
	quint64 i_max = stg.beginReadArray( "map_" );
	for ( quint64 i = 0; i < i_max; i++ )
	{
		stg.setArrayIndex( i );
		key = stg.value( "id", InvalidId ).toLongLong();
		s = stg.value( "value", QString() ).toString();
		map_.insert( key, s );
	}
	stg.endArray();
	
	stg.endGroup();
	return true;
}
/* ========================================================================= */

/*  CLASS    =============================================================== */
//
//
//
//
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
