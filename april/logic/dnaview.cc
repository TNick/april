/* ========================================================================= */
/* ------------------------------------------------------------------------- */
/*!
  \file			dnaview.cc
  \date			Apr 2013
  \author		TNick

  \brief		Contains the implementation of DNAView class


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

#include	"dnaview.h"
#include	"dna.h"


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
#define	_LG_(t)		APRDBG(APRDBG_DNAV,t)
#define	FUNC_ENTRY	APRDBG_FUNC(APRDBG_DNAV)
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
	//! the unique ID of the component
	ID				id_;
	
	//! index of the first value
	int				start_;
	
	//! number of values
	int				count_;
	
	//! the source DNA
	const DNA *		dna_;

/* ------------------------------------------------------------------------- */
DNAView::DNAView	( const DNA * dna, ID id )
	: id_(id),
	  start_(-1),
	  count_(-1),
	  dna_(dna)
{
	APRDBG_CDTOR;
	/* stub */
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
DNAView::~DNAView	( void )
{
	APRDBG_CDTOR;
	/* stub */
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
qreal		DNAView::value		( int i ) const
{ FUNC_ENTRY;
	if ( !isValid() )
	{
		Q_ASSERT( false );
		return 0.0;
	}
	if ( i > count_ )
	{
		Q_ASSERT( false );
		return 0.0;
	}
	
	Q_ASSERT( dna_->values_.length() > start_ + i );
	return dna_->values_.at( start_ + i );
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void		DNAView::setDNA		( const DNA * d )
{ FUNC_ENTRY;
	dna_ = d;
}
/* ========================================================================= */

/*  CLASS    =============================================================== */
//
//
//
//
/* ------------------------------------------------------------------------- */
/* ========================================================================= */