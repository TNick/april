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

//! @cond internal

#define	_LG2_(t1,t2)	APRDBG2(APRDBG_W,t1,t2)
#define	_LG3_(t1,t2,t3)	APRDBG3(APRDBG_W,t1,t2,t3)
#define	_LG_(t)		APRDBG(APRDBG_DNA,t)
#define	FUNC_ENTRY	APRDBG_FUNC(APRDBG_DNA)
//! @endcond

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
{ FUNC_ENTRY;
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
void			DNA::initDNA		( const InitData & init )
{ FUNC_ENTRY;
	parts_.clear();
	values_.clear();
	values_i_.clear();
	
	/* initialise the header */
	values_i_.reserve( OffMax );
	values_i_.append( init.kind_ );
	for ( int i = OffKind+1; i < OffMax; i++ )
	{
		values_i_.append( 0 );
	}
	values_i_[OffCost] = init.cost_;
	values_i_[OffAge] = init.age_;
	values_i_[OffStartEnergy] = init.energy_;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void			DNA::reinitDNA		( const DNA & src, bool clear_content )
{ FUNC_ENTRY;
	
	values_i_ = src.values_i_;
	if ( clear_content )
	{
		parts_.clear();
		values_.clear();
	}
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool			DNA::fromMerge		( const DNA & p1, const DNA & p2 )
{ FUNC_ENTRY;
	Q_UNUSED( p1 );
	Q_UNUSED( p2 );
	
	parts_.clear();
	values_.clear();
	values_i_.clear();
	
	/* initialise the header */
	values_i_.reserve( OffMax );
	values_i_.append( InvalidId );
	for ( int i = OffKind+1; i < OffMax; i++ )
	{
		values_i_.append( 0 );
	}
	
	/* check compatibility */
	if ( p1.values_i_.count() < OffMax )
	{
		return false;
	}
	if ( p2.values_i_.count() < OffMax )
	{
		return false;
	}
	if ( p1.values_i_.at( OffKind ) != p2.values_i_.at( OffKind ) )
	{
		return false;
	}
	if ( p1.values_i_.at( OffKind ) == InvalidId )
	{
		return false;
	}
	if ( p2.values_i_.at( OffKind ) == InvalidId )
	{
		return false;
	}
	values_i_[OffKind] = p2.values_i_.at( OffKind );
	mergeAllParts( p1, p2 );
	mergeAllVals( p1, p2 );
	
	return true;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool			DNA::mergeAllVals		( const DNA & p1, const DNA & p2 )
{ FUNC_ENTRY;
	
	int iter_1 = OffMax;
	int iter_2 = OffMax;
	
	mergeBrains( p1, p2 );
	iter_1 += p1.values_i_.at( OffBrains );
	iter_2 += p2.values_i_.at( OffBrains );
	
	int res;
	for ( int i = OffBrains+1; i < OffLastList; i++ )
	{
		res = mergeUniteEl( 
					iter_1, iter_2, 
					p1.values_i_.at( i ), 
					p2.values_i_.at( i ),
					p1, p2 );
		if ( res == -1 )
			return false;
		values_i_[i] = (quint64)res;
		iter_1 += p1.values_i_.at( i );
		iter_2 += p2.values_i_.at( i );
	}
	
	/* the cost of running the agent as an average */
	values_i_[OffCost] = 
			p1.values_i_.at( OffCost ) + 
			p2.values_i_.at( OffCost ) + 
			qrand() % 4; /* some randomness */
	
	return true;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
int			DNA::mergeUniteEl		( 
		int iter_1, int iter_2,
		int i_max_1, int i_max_2,
		const DNA & p1, const DNA & p2 )
{ FUNC_ENTRY;
	bool b_not_found;
	int cnt = values_i_.count();
	if ( i_max_1 + iter_1 > p1.values_i_.count() )
		return -1;
	if ( i_max_2 + iter_2 > p2.values_i_.count() )
		return -1;
	quint64 val;
	
	/* copy all from first */
	for ( int i = 0; i < i_max_1; i++ )
	{
		val = p1.values_i_.at( iter_1 + i );
		if ( val == InvalidId )
			continue;
		values_i_.append( val );
	}
	
	/* copy id's that were not already in first set */
	for ( int i = 0; i < i_max_2; i++ )
	{
		val = p2.values_i_.at( iter_2 + i );
		if ( val == InvalidId )
			continue;
		b_not_found = true;
		for ( int j = 0; j < i_max_1; j++ )
		{
			if ( val == p1.values_i_.at( iter_1 + j ) )
			{
				b_not_found = false;
				break;
			}
		}
		if ( b_not_found )
		{
			values_i_.append( val );
		}
	}
	
	return values_i_.count() - cnt;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool			DNA::mergeBrains		( const DNA & p1, const DNA & p2 )
{ FUNC_ENTRY;
	int i_max_1 = p1.values_i_.at( OffBrains );
	int i_max_2 = p2.values_i_.at( OffBrains );
	if ( i_max_1 == 0 && i_max_2 == 0 )
	{
		values_i_[OffBrains] = 0;
		return true;
	}
	int iter_1 = OffMax;
	int iter_2 = OffMax;
	
	if ( i_max_1 + iter_1 > p1.values_i_.count() )
		return false;
	if ( i_max_2 + iter_2 > p2.values_i_.count() )
		return false;
	
	if ( i_max_1 == 1 && i_max_2 == 1 )
	{
		if ( p1.values_i_.at( iter_1 ) == p2.values_i_.at( iter_2 ) )
		{
			/* if they are the same there is no decision to be made */
			values_i_.append( p1.values_i_.at( iter_1 ) );
			values_i_[OffBrains] = 1;
			return true;
		}
	}
	
	/* take a (single) random entry */
	int i = qrand() % (i_max_1+i_max_2);
	if ( i >= i_max_1 )
	{
		i -= i_max_1;
		values_i_.append( p1.values_i_.at( iter_1+i ) );
	}
	else
	{
		values_i_.append( p2.values_i_.at( iter_2+i ) );	
	}
	values_i_[OffBrains] = 1;
	return true;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void			DNA::mergeAllParts		( 
		const DNA & p1, const DNA & p2  )
{ FUNC_ENTRY;

/// @cond internal
#	define part_1(i) p1.parts_.at( i )
#	define part_2(i) p2.parts_.at( i )
/// @endcond

	int i_max_1 = p1.parts_.count();
	int i_max_2 = p2.parts_.count();
	int i_max_me;
	bool b_found = false;
	
	/* iterate in partitions from first parent */
	for ( int i = 0; i < i_max_1; i++ )
	{
		if ( part_1(i).id_ == InvalidId )
			continue;
		b_found = false;
		
		/* attempt to locate same id in second parent */
		for ( int j = 0; j < i_max_2; j++ )
		{
			if ( part_2(j).id_ == InvalidId )
				continue;
			
			/* if found merge and step to next in first parent */
			if ( part_1(i).id_ == part_2(j).id_ )
			{
				mergeParts( part_1(i), part_2(j), p1, p2 );
				b_found = true;
				break;
			}
		}
		/* if not found copy only from first parent */
		if ( b_found == false )
		{
			mergePart( part_1(i), p1 );
		}
	}
	i_max_me = values_.count();
	
	/* iterate in partitions from second parent */
	for ( int j = 0; j < i_max_2; j++ )
	{
		if ( part_2(j).id_ == InvalidId )
			continue;
		
		/* only add parts that were not added already */
		for ( int i = 0; i < i_max_me; i++ )
		{
			if ( parts_.at( i ).id_ == InvalidId )
				continue;
			if ( parts_.at( i ).id_ == part_2(j).id_ )
			{
				b_found = true;
				break;				
			}
		}
		
		/* if was not already added, add it now */
		if ( b_found == false )
		{
			mergePart( part_2(j), p2 );
		}
	}
#	undef	part_1
#	undef	part_2
	
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void			DNA::mergeParts		( 
		const Partition & part_1, const Partition & part_2,
		const DNA & p1, const DNA & p2  )
{ FUNC_ENTRY;
	Q_ASSERT( part_1.id_ == part_2.id_ );
	
	Partition pout;
	qreal val;
	
	pout.id_ = part_1.id_;
	pout.start_ = values_.count();
	
	int i_max = qMax( part_1.count_, part_2.count_ );
	int i_min = qMin( part_1.count_, part_2.count_ );
	
	/* take the average of all common data */
	for ( int i = 0; i < i_min; i++ )
	{
		val = p1.values_.at( part_1.start_ + i ) +
				p2.values_.at( part_2.start_ + i ) +
				dnaNoise();
		values_.append( val );
	}
	/* aand copy data that is not common */
	if ( i_max > i_min )
	{
		if ( part_1.count_ > part_2.count_ )
		{
			for ( int i = i_min; i < i_max; i++ )
			{
				val = p1.values_.at( part_1.start_ + i )
						+ 2 * dnaNoise();
			}
		}
		else
		{
			for ( int i = i_min; i < i_max; i++ )
			{
				val = p2.values_.at( part_2.start_ + i )
						+ 2 * dnaNoise();
			}
		}
	}
	pout.count_ = i_max;
	
	parts_.append( pout );
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void			DNA::mergePart			( 
		const Partition & part, const DNA & p  )
{ FUNC_ENTRY;
	int i_max = part.count_;
	Partition pout;
	qreal val;
	
	pout.id_ = part.id_;
	pout.start_ = values_.count();
	pout.count_ = i_max;
	
	for ( int i = 0; i < i_max; i++ )
	{
		val = p.values_.at( part.start_ + i ) +
				2 * dnaNoise();
		values_.append( val );
	}
	
	parts_.append( pout );
	
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
DNAView			DNA::getView			( ID id, Factory * f )
{ FUNC_ENTRY;
	DNAView		view(this,InvalidId);
	
	int i = findID( id );
	if ( i != -1 )
	{ /* id found in a partition */
		view.setBegin( parts_.at( i ).start_ );
		view.setCount( parts_.at( i ).count_ );
	}
	else
	{ /* id was not found inside our parts */
		if ( getViewNotFound( view, id, f ) == false )
			return view;
	}
	view.setIdentificator( id );
	return view;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
DNAView			DNA::getView			( ID id, int sz, Factory * f )
{ FUNC_ENTRY;
	DNAView		view(this,InvalidId);
	int i = findID( id );
	if ( i != -1 )
	{ /* id found in a partition */
		Partition & part = parts_[i];
		if ( part.count_ >= sz )
		{
			view.setBegin( part.start_ );
			view.setCount( part.count_ );
		}
		else
		{
			QList<qreal> vals = f->averageDNA( id );
			Partition newpart;
			int i;
			int i_max = vals.count();
			newpart.id_ = id;
			newpart.start_ = values_.count();
			
			/* copy old values */
			for ( i = 0; i < part.count_; i++ )
			{
				values_.append( values_.at( part.start_+i ) );
			}
			
			/* copy defaults in other places */
			while ( i < i_max )
			{
				values_.append( vals.at( i ) );
				i++;
			}
			
			/* fill random if that's not enough */
			while ( i < sz )
			{
				values_.append( RAND_ARROUND_0 );
				i++;
			}
			
			newpart.count_ = i;
			part.id_ = InvalidId; // discard old
			parts_.append( newpart );
			
			view.setBegin( newpart.start_ );
			view.setCount( newpart.count_ );
		}
	}
	else
	{ /* id was not found inside our parts */
		if ( getViewNotFound( view, id, f ) == false )
			return view;
	}
	view.setIdentificator( id );
	return view;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool			DNA::getViewNotFound	( DNAView & view, ID id, Factory * f )
{ FUNC_ENTRY;
	if ( f == NULL )
	{ /* no factory provided */
		return false;
	}
	else
	{ /* a factory was provided; attempt to request defaults */
		QList<qreal> vals = f->averageDNA( id );
		Partition part;
		if ( vals.count() == 0 )
		{ /* no return */
			return false;
		}
		
		/* factory gave us the defaults; create new partition */
		part.id_ = id;
		part.count_ = vals.count();
		part.start_ = values_.count();
		parts_.append( part );
		
		/* append the values */
		values_.append( vals );
		
		/* and return a view to them */
		view.setBegin( part.start_ );
		view.setCount( part.count_ );
	}
	return true;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
ID				DNA::kind				( void ) const
{ FUNC_ENTRY;
	quint64 sz = values_i_.length();
	if ( sz < OffMax )
		return InvalidId;
	return values_i_.at( OffKind );
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
QList<ID>		DNA::brains				( void ) const
{ FUNC_ENTRY;
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
QList<ID>		DNA::actuators			( void ) const
{ FUNC_ENTRY;
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
{ FUNC_ENTRY;
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
{ FUNC_ENTRY;
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
{ FUNC_ENTRY;
	int i_max;
	
	if ( isValid() == false )
	{
		_LG_("  Invalid DNA requested to save");
		return false;
	}
	
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
{ FUNC_ENTRY;
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

/* ------------------------------------------------------------------------- */
qreal				DNA::dnaNoise				( void )
{
	/* this should really be customisable */
	static qreal noise_level = 0.000001;
	
	return RAND_ARROUND_0 * noise_level;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool				DNA::addActuator			( ID id )
{ FUNC_ENTRY;
	if ( id == InvalidId )
		return false;
	
	int i = OffMax + 
			values_i_.at( OffBrains ) +
			values_i_.at( OffActuators );
	values_i_.insert( i, id );
	values_i_[OffActuators]++;
	return true;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool				DNA::addBrain				( ID id )
{ FUNC_ENTRY;
	if ( id == InvalidId )
		return false;
	
	int i = OffMax + 
			values_i_.at( OffBrains );
	values_i_.insert( i, id );
	values_i_[OffBrains]++;
	return true;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool				DNA::addReflex				( ID id )
{ FUNC_ENTRY;
	if ( id == InvalidId )
		return false;
	
	int i = OffMax + 
			values_i_.at( OffBrains ) +
			values_i_.at( OffActuators ) +
			values_i_.at( OffSensors ) +
			values_i_.at( OffReflexes );
	values_i_.insert( i, id );
	values_i_[OffReflexes]++;
	return true;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool				DNA::addSensor				( ID id )
{ FUNC_ENTRY;
	if ( id == InvalidId )
		return false;
	
	int i = OffMax + 
			values_i_.at( OffBrains ) +
			values_i_.at( OffActuators ) +
			values_i_.at( OffSensors );
	values_i_.insert( i, id );
	values_i_[OffSensors]++;
	return true;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool				DNA::operator ==	( const DNA & other ) const
{
	if ( values_i_.length() == other.values_i_.length() )
	{
		if ( values_i_ == other.values_i_ )
		{
			if ( values_.length() == other.values_.length() )
			{
				if ( values_ == other.values_ )
				{
					if ( parts_.count() == other.parts_.count() )
					{
						int i_max = parts_.count();
						for ( int i = 0; i < i_max; i++ )
						{
							if ( parts_.at( i ) != other.parts_.at( i ) )
							{
								return false;
							}
						}
						return true;
					}
				}
			}
		}
	}
	return false;
}
/* ========================================================================= */


/*  CLASS    =============================================================== */
//
//
//
//
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
