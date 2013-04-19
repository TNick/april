/* ========================================================================= */
/* ------------------------------------------------------------------------- */
/*!
  \file			newactordlg.cc
  \date			Apr 2013
  \author		TNick

  \brief		Contains the implementation for NewActorDlg class


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

#include	"newactordlg.h"
#include	<april/logic/genericactorfactory.h>
#include	<april/AprilDream/gui/mw.h>


/*  INCLUDES    ============================================================ */
//
//
//
//
/*  DEFINITIONS    --------------------------------------------------------- */

using namespace april;
using namespace april::Gui;

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
NewActorDlg::NewActorDlg					(  MW * parent, World * w ) :
	QDialog(parent), MemTrack(),
	ui(),
	w_( w )
{
	APRDBG_CDTOR;

	ui.setupUi(this);

	GenericActorFactory * gf = 
			GenericActorFactory::findMyself( w );
	Q_ASSERT( gf != NULL );
	
	GenericActorFactory::IdDnaMap lst = gf->dnaList();
	GenericActorFactory::IdDnaMapIterC itr = lst.constBegin();
	GenericActorFactory::IdDnaMapIterC itr_end = lst.constEnd();
	ID id;
	QString s_name;
	while ( itr != itr_end )
	{
		id = itr.key();
		s_name = w_->nameForId( id );
		if ( s_name.isEmpty() )
		{
			s_name = tr( "Kind with id %1" ).arg( id );
		}
		else
		{
			s_name = tr( "%1 (%2)" ).arg( s_name ).arg( id );
		}
		ui.cb_kinds->addItem( s_name, QVariant( id ) );
	}
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
NewActorDlg::~NewActorDlg					( void )
{
	APRDBG_CDTOR;
	/* stub */
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
ID						NewActorDlg::selectedID				( void ) const
{
	return ui.cb_kinds->itemData( ui.cb_kinds->currentIndex() ).toULongLong();
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void					NewActorDlg::changeEvent			( QEvent *e )
{
	QDialog::changeEvent( e );
	switch ( e->type() ) {
	case QEvent::LanguageChange:	{
		ui.retranslateUi( this );
		break;}
	default:						{
		break;}
	}
}
/* ========================================================================= */


/*  CLASS    =============================================================== */
//
//
//
//
/* ------------------------------------------------------------------------- */
/* ========================================================================= */







