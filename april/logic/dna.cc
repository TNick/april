/* ========================================================================= */
/* ------------------------------------------------------------------------- */
/*!
  \file			dna.cc
  \date			Apr 2013
  \author		TNick
  
  \brief		Contains the implementation of DNA class
  
  
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

#include	"dna.h"
#include	"world.h"
#include	"actorfactory.h"


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
DNA::DNA		( void )
	: parts_(),
	  values_(),
	  values_i_()
{
	APRDBG_CDTOR;
	for ( int i = 0; i < OffMax; i++ )
	{
		values_i_.append( InvalidId );
	}
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
DNA::DNA		( const World * w, ID kind )
	: parts_(),
	  values_(),
	  values_i_()
{
	ActorFactory * factory = w->actorFactory( kind );
	if ( factory != NULL )
	{
		factory->copyDefaultDNA( *this );
	}
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
DNA::~DNA		( void )
{
	APRDBG_CDTOR;
	/* stub */
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
int				DNA::findID			( ID id ) const
{
	int i_max = parts_.count();
	for ( int i = 0; i < i_max; i++ )
	{
		if ( parts_.at( i ).id_ == id )
		{
			return i;
		}
	}
	return -1;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void			DNA::fromMerge	( const DNA & p1, const DNA & p2 )
{
	Q_UNUSED( p1 );
	Q_UNUSED( p2 );
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
DNAView			DNA::getView	( ID id )
{
	DNAView		view(this,InvalidId);
	
	int i = findID( id );
	if ( i == -1 )
		return view;
	
	view.setIdentificator( id );
	view.setBegin( parts_.at( i ).start_ );
	view.setCount( parts_.at( i ).count_ );
	
	return view;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
ID				DNA::kind		( void ) const
{
	quint64 sz = values_i_.length();
	if ( sz < OffMax )
		return InvalidId;
	return values_i_.at( OffKind );
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
QList<ID>		DNA::brains			( void ) const
{
	QList<ID>	ret_l;
	quint64 sz = values_i_.length();
	if ( sz <= OffMax )
		return ret_l;
	
	quint64	off = OffMax;
	quint64	cnt = values_i_.at( OffBrains );
	
	if ( off + cnt > sz )
		return ret_l;
	
	for ( quint64 i = 0; i < cnt; i++ )
	{
		ret_l.append( values_i_.at( i+off ) );
	}
	return ret_l;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
QList<ID>		DNA::actuators		( void ) const
{
	QList<ID>	ret_l;
	quint64 sz = values_i_.length();
	if ( sz <= OffMax )
		return ret_l;
	
	quint64	off = OffMax;
	off += values_i_.at( OffBrains );
	quint64	cnt = values_i_.at( OffActuators );
	
	if ( off + cnt > sz )
		return ret_l;
	
	for ( quint64 i = 0; i < cnt; i++ )
	{
		ret_l.append( values_i_.at( i+off ) );
	}
	return ret_l;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
QList<ID>		DNA::sensors		( void ) const
{
	QList<ID>	ret_l;
	quint64 sz = values_i_.length();
	if ( sz <= OffMax )
		return ret_l;
	
	quint64	off = OffMax;
	off += values_i_.at( OffBrains );
	off += values_i_.at( OffActuators );
	quint64	cnt = values_i_.at( OffSensors );
	
	if ( off + cnt > sz )
		return ret_l;
	
	for ( quint64 i = 0; i < cnt; i++ )
	{
		ret_l.append( values_i_.at( i+off ) );
	}
	return ret_l;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
QList<ID>		DNA::reflexes		( void ) const
{
	QList<ID>	ret_l;
	quint64 sz = values_i_.length();
	if ( sz <= OffMax )
		return ret_l;
	
	quint64	off = OffMax;
	off += values_i_.at( OffBrains );
	off += values_i_.at( OffActuators );
	off += values_i_.at( OffSensors );
	quint64	cnt = values_i_.at( OffReflexes );
	
	if ( off + cnt > sz )
		return ret_l;
	
	for ( quint64 i = 0; i < cnt; i++ )
	{
		ret_l.append( values_i_.at( i+off ) );
	}
	return ret_l;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool			DNA::isValid			( void ) const
{
	return ( ( values_i_.length() >= OffMax ) && 
			 ( values_i_.at( OffKind ) != InvalidId ) );
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool			DNA::save				( QSettings & stg ) const
{
	int i_max;
	
	if ( isValid() )
		return false;
	stg.beginGroup( "DNA" );
	
	stg.beginWriteArray( "parts_" );
	i_max = parts_.count();
	for ( int i = 0; i < i_max; i++ )
	{
		stg.setArrayIndex( i );
		stg.setValue( "id_", parts_.at( i ).id_ );
		stg.setValue( "start_", parts_.at( i ).start_ );
		stg.setValue( "count_", parts_.at( i ).count_ );
	}
	stg.endArray();
	
	stg.beginWriteArray( "values_" );
	i_max = values_.count();
	for ( int i = 0; i < i_max; i++ )
	{
		stg.setArrayIndex( i );
		stg.setValue( "i", values_.at( i ) );
	}
	stg.endArray();
	
	stg.beginWriteArray( "values_i_" );
	i_max = values_i_.count();
	for ( int i = 0; i < i_max; i++ )
	{
		stg.setArrayIndex( i );
		stg.setValue( "i", values_i_.at( i ) );
	}
	stg.endArray();
	
	stg.endGroup();
	
	return true;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool			DNA::load				( QSettings & stg )
{
	int i_max;
	bool b = true;
	Partition part;
	qreal dval;
	quint64 uval;
	
	
	stg.beginGroup( "DNA" );
	
	parts_.clear();
	values_.clear();
	values_i_.clear();
	
	for ( ;; )
	{
		i_max = stg.beginReadArray( "parts_" );
		parts_.reserve( i_max );
		for ( int i = 0; i < i_max; i++ )
		{
			stg.setArrayIndex( i );
			part.id_ = stg.value( "id_", InvalidId ).toULongLong( &b );
			if ( b == false )
				break;
			part.start_ = stg.value( "start_", InvalidId ).toInt( &b );
			if ( b == false )
				break;
			part.count_ = stg.value( "count_", InvalidId ).toInt( &b );
			if ( b == false )
				break;
			
			parts_.append( part );
		}
		stg.endArray();
		if ( b == false )
			break;
		
		
		i_max = stg.beginReadArray( "values_" );
		values_.reserve( i_max );
		for ( int i = 0; i < i_max; i++ )
		{
			stg.setArrayIndex( i );
			dval = stg.value( "i" ).toDouble( &b );
			if ( b == false )
				break;
			values_.append( dval );
		}
		stg.endArray();
		if ( b == false )
			break;
		
		
		i_max = stg.beginReadArray( "values_i_" );
		values_i_.reserve( i_max );
		for ( int i = 0; i < i_max; i++ )
		{
			stg.setArrayIndex( i );
			uval = stg.value( "i" ).toULongLong( &b );
			if ( b == false )
				break;
			values_i_.append( uval );
		}
		stg.endArray();
		if ( b == false )
			break;
		
		break;
	}
	
	stg.endGroup();
	return b;
}
/* ========================================================================= */

/*  CLASS    =============================================================== */
//
//
//
//
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
