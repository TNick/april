/* ========================================================================= */
/* ------------------------------------------------------------------------- */
/*!
  \file			dockcrtsel.h
  \date			Apr 2013
  \author		TNick

  \brief		Contains the definition for DockCrtSel class


*//*


 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Please read COPYING and README files in root folder
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
#ifndef __DOCKCRTSEL_INC__
#define __DOCKCRTSEL_INC__
//
//
//
//
/*  INCLUDES    ------------------------------------------------------------ */

#include    <april/april.h>
#include    <april/AprilDream/gui/dock.h>

/*  INCLUDES    ============================================================ */
//
//
//
//
/*  DEFINITIONS    --------------------------------------------------------- */

//class QtBoolPropertyManager;
//class QtIntPropertyManager;
//class QtStringPropertyManager;
//class QtSizePropertyManager;
//class QtRectPropertyManager;
//class QtSizePolicyPropertyManager;
//class QtEnumPropertyManager;
//class QtGroupPropertyManager;
//class QtTreePropertyBrowser;

//class QtProperty;

//class	QtCheckBoxFactory;
//class	QtSpinBoxFactory;
//class	QtLineEditFactory;
//class	QtSliderFactory;
//class	QtScrollBarFactory;
//class	QtEnumEditorFactory;

namespace   april	{

namespace	Gui		{

class	MW;
class	DockCrtSel_p;

/*  DEFINITIONS    ========================================================= */
//
//
//
//
/*  CLASS    --------------------------------------------------------------- */

/**
*	@brief	Properties of current selection
*/
class DockCrtSel		: public Dock		{
	BBM_TRACK( DockCrtSel );

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

	//! data only allocated when visible
	DockCrtSel_p *		d_;

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
	DockCrtSel			( MW * mw );

	/**
	*	@brief	destructor;
	*/
	virtual				~DockCrtSel				( void );

protected:

	//! used to construct the widget
	void				construct				( void );

	//! used to destruct the widget
	void				deconstruct				( void );


	/*  FUNCTIONS    ======================================================= */
	//
	//
	//
	//

};	/*	class DockCrtSel	*/

/*  CLASS    =============================================================== */
//
//
//
//

}   //  namespace   Gui
}   //  namespace   april

#endif // __DOCKCRTSEL_INC__
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
