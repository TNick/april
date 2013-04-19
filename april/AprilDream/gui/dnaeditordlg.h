/* ========================================================================= */
/* ------------------------------------------------------------------------- */
/*!
  \file			dnaeditordlg.h
  \date			Apr 2013
  \author		TNick

  \brief		Contains the definition for DNAEditorDlg class


*//*


 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Please read COPYING and README files in root folder
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
#ifndef __DNAEDITORDLG_INC__
#define __DNAEDITORDLG_INC__
//
//
//
//
/*  INCLUDES    ------------------------------------------------------------ */

#include    <QDialog>
#include    <april/april.h>
#include    <april/logic/uniqueid.h>
#include    <april/logic/dna.h>
#include	"ui_dnaeditordlg.h"

/*  INCLUDES    ============================================================ */
//
//
//
//
/*  DEFINITIONS    --------------------------------------------------------- */

namespace   april	{

class	World;
class	DNA;

namespace	Gui		{

class	MW;

/*  DEFINITIONS    ========================================================= */
//
//
//
//
/*  CLASS    --------------------------------------------------------------- */


/**
*	@brief	Dialog to create or edit a kind
*/
class DNAEditorDlg : public QDialog, public MemTrack		{
	Q_OBJECT
	BBM_TRACK( DNAEditorDlg );

	//
	//
	//
	//
	/*  DEFINITIONS    ----------------------------------------------------- */

	//! te order of the tabs
	enum Tabs {
		TabGeneral = 0,
		TabSensors,
		TabReflexes,
		TabBrains,
		TabActuators
	};


	/*  DEFINITIONS    ===================================================== */
	//
	//
	//
	//
	/*  DATA    ------------------------------------------------------------ */

private:

	//! GUI components embedded in this instance
	Ui::DNAEditorDlg 			ui;

	//! the world we're editing
	World *						w_;
	
	//! the DNA that we're editing here
	DNA &						dna_;
	
	//! invalid DNA reference
	static DNA					invalid_dna_;
	
	/*  DATA    ============================================================ */
	//
	//
	//
	//
	/*  FUNCTIONS    ------------------------------------------------------- */

public:

	//! constructor; we're creating a new DNA pice
	explicit				DNAEditorDlg		( MW * parent, World * w );

	//! constructor; we're editing an existing DNA pice
	explicit				DNAEditorDlg		( MW * parent, World * w, DNA & dna  );

	//! destructor
	~DNAEditorDlg			(void);
	
private:
	
	//! common initialisation for all constructors
	void					init				( void );
	
protected:
	
	//!@{
	//! other events
	void					changeEvent			( QEvent *e );
	//!@}

protected slots:

	//!@{
	//! list of components
	void					addActuators		( void );
	void					addBrains			( void );
	void					addReflex			( void );
	void					addSensor			( void );
	void					remActuators		( void );
	void					remBrains			( void );
	void					remReflex			( void );
	void					remSensor			( void );
	//!@}
	
	//! check input and accept
	void					validate			( void );

private:


	//!@{
	//! support methods
	QString					getName				( ID & id_for_name );
	void					validateNew			( DNA::InitData &init_d );
	void					validateEdit		( DNA::InitData & init_d );
	void					componentsToDNA		( DNA & dna );
	//!@}

	/*  FUNCTIONS    ======================================================= */
	//
	//
	//
	//

};	/*	class DNAEditorDlg	*/

/*  CLASS    =============================================================== */
//
//
//
//

}	//	namespace	Gui

}   //  namespace   april

#endif // __DNAEDITORDLG_INC__
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
