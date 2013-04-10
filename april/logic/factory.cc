/* ========================================================================= */
/* ------------------------------------------------------------------------- */
/*!
  \file			factory.cc
  \date			Apr 2013
  \author		TNick
  
  \brief		Contains the implementation of Factory class
  
  
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

#include	"factory.h"
#include	"world.h"
#include	<QSettings>

/*  INCLUDES    ============================================================ */
//
//
//
//
/*  DEFINITIONS    --------------------------------------------------------- */

using namespace april;


#define	_LG2_(t1,t2)	APRDBG2(APRDBG_W,t1,t2)
#define	_LG3_(t1,t2,t3)	APRDBG3(APRDBG_W,t1,t2,t3)
#define	_LG_(t)		APRDBG(APRDBG_F,t)
#define	FUNC_ENTRY	APRDBG_FUNC(APRDBG_F)

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
Factory::Factory	( World * w )
	: libbbb::RefCnt(), MemTrack(),
	  w_( w )
{
	APRDBG_CDTOR;
	/* stub */
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
Factory::~Factory	( void )
{
	APRDBG_CDTOR;
	/* stub */
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool			Factory::setEnergy			(
		ActorComp * comp, quint64 energy, quint64 cost )
{ FUNC_ENTRY;
	return w_->setEnergy( comp, energy, cost );
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool			Factory::save				( QSettings & stg ) const
{ FUNC_ENTRY;
	bool b = true;
	stg.beginGroup( "april-Factory" );
	
	for (;;)	{
		
		stg.setValue( "s_name_for_id_", s_name_for_id_ );
		
		break;
	}
	stg.endGroup();
	
	return b;

	return true;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool			Factory::load				( QSettings & stg )
{ FUNC_ENTRY;
	bool b = true;
	stg.beginGroup( "april-Factory" );
	
	for (;;)	{
		
		s_name_for_id_ = stg.value( "s_name_for_id_" ).toString();
		
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
