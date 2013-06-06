/* ========================================================================= */
/* ------------------------------------------------------------------------- */
/*!
  \file			pluginsdlg.cc
  \date			Apr 2013
  \author		TNick
  
  \brief		Contains the implementation for PluginsDlg class
  
  
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

#include	"pluginsdlg.h"
#include	<QTreeWidgetItem>
#include	<QDir>
#include	<QLibrary>
#include	<QSettings>
#include	<QFileInfo>
#include	<QFileDialog>
#include	<april/aprillibrary.h>
#include	<april/plugins/aprilplugininterf.h>

/*  INCLUDES    ============================================================ */
//
//
//
//
/*  DEFINITIONS    --------------------------------------------------------- */

using namespace april;
using namespace april::Gui;

namespace   april	{

namespace	Gui		{

//! columns in the plug-in tree
/**
*	@internal
*/
enum		PlgInCols	{
	ColName = 0,
	ColStatus,
	ColPath
};


//! an entry in the list of plug-ins
/**
*	@internal
*/
class	PlginEntry : public QTreeWidgetItem {
	
	//! initial status
	bool		b_init_loaded_;
public:
	
	//! constructor
	PlginEntry( const QString & s_file )
		: QTreeWidgetItem(),
		b_init_loaded_( false )
	{
		QFileInfo fi( s_file );
		setText( ColName, fi.baseName() );
		setUnloaded();
		setText( ColPath, fi.absoluteFilePath() );
	}
	
	//! mark as being loaded in library
	void			setLoaded			( void )
	{
		b_init_loaded_ = true;
		setCheckState( ColName, Qt::Checked );
		setText( ColStatus, QObject::tr( "Not loaded" ) );
	}
	
	//! mark as being unloaded in library
	void			setUnloaded			( void )
	{
		b_init_loaded_ = false;
		setCheckState( ColName, Qt::Checked );
		setText( ColStatus, QObject::tr( "Loaded" ) );
	}
	
	//! tell if plug-in is loaded in library
	bool			wasLoaded			( void ) const
	{ return b_init_loaded_; }
	
	//! should we load this plug-in?
	bool			shouldBeLoaded		( void ) const
	{ return checkState( ColName ) == Qt::Checked; }
	
	//! the binary file
	QString			file				( void ) const
	{
		return text( ColPath );
	}
	
}; /* class PlginEntry */

}

}

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
PluginsDlg::PluginsDlg					( QWidget *parent ) :
	QDialog(parent), MemTrack()
{
	APRDBG_CDTOR;
	
	ui.setupUi(this);
	
	loadDirectories();
	rescan();
	
	connect( ui.b_add, SIGNAL( clicked() ),
			 this, SLOT( addDirectory() ) );
	connect( ui.b_del, SIGNAL( clicked() ),
			 this, SLOT( remDirectory() ) );
	connect( ui.b_refresh, SIGNAL( clicked() ),
			 this, SLOT( rescan() ) );
    connect( ui.buttonBox, SIGNAL( accepted() ), 
			 this, SLOT( validateAndClose() ) );
    connect( ui.tv_plugins, SIGNAL( itemDoubleClicked(QTreeWidgetItem*,int) ), 
			 this, SLOT( itemDoubleClicked(QTreeWidgetItem*,int) ) );
	
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
PluginsDlg::~PluginsDlg					( void )
{
	APRDBG_CDTOR;
	/* stub */
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void					PluginsDlg::changeEvent			( QEvent *e )
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

/* ------------------------------------------------------------------------- */
void					PluginsDlg::scanDirectories		( void )
{
	QListWidgetItem * iter;
	int i_max = ui.lv_dirs->count();
	for ( int i = 0; i < i_max; i++ )
	{
		iter = ui.lv_dirs->item( i );
		scanDirectory( iter->text() );
	} /* for ( int i = 0; i < i_max; i++ ) */
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void					PluginsDlg::scanDirectory		( const QString & s )
{
	int j_max;
	PlginEntry * plg;
	QString s_file;
	
	QDir d( s );
	if ( d.exists() )
	{
		d.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
		QFileInfoList list = d.entryInfoList();
		j_max = list.count();
		for ( int j = 0; j < j_max; j++ )
		{
			s_file = list.at( j ).fileName();
			if ( QLibrary::isLibrary( s_file ) )
			{
				plg = findPlugIn( s_file );
				if ( plg == NULL )
				{
					ui.tv_plugins->addTopLevelItem( new PlginEntry( s_file ) );
				}
			}
		}
	}
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void					PluginsDlg::loadDirectories		( void )
{
	QSettings	stg;
	stg.beginGroup( "PluginsDlg" );
	
	int i_max = stg.beginReadArray( "dirs" );
	for ( int i = 0; i < i_max; i++ )
	{
		stg.setArrayIndex( i );
		ui.lv_dirs->addItem( new QListWidgetItem( stg.value( "i" ).toString() ) );
	}
	stg.endArray();
	
	stg.endGroup();
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void					PluginsDlg::saveDirectories		( void )
{
	QSettings	stg;
	stg.beginGroup( "PluginsDlg" );
	
	QListWidgetItem * iter;
	int i_max = ui.lv_dirs->count();
	stg.beginWriteArray( "dirs", i_max );
	for ( int i = 0; i < i_max; i++ )
	{
		stg.setArrayIndex( i );
		iter = ui.lv_dirs->item( i );
		stg.setValue( "i", iter->text() );
		
	} /* for ( int i = 0; i < i_max; i++ ) */
	stg.endArray();
	
	stg.endGroup();
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void					PluginsDlg::loadLibraryPlugins	( void )
{	
	PlginEntry * pe;
	QString s_name;
	AprilPluginLoader *	p = AprilLibrary::firstPlugin();
	while ( p != NULL )
	{
		s_name = p->fileName();
		pe = findPlugIn( s_name );
		
		if ( pe == NULL )
		{
			pe = new PlginEntry( s_name );
			ui.tv_plugins->addTopLevelItem( pe );
		}
		pe->setLoaded();
		p = nextPlugin_(p);
	}
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
PlginEntry *			PluginsDlg::findPlugIn		( const QString & s )
{
	PlginEntry * iter;
	QDir d;
	QString s_file = d.absoluteFilePath( s );
	int i_max = ui.tv_plugins->topLevelItemCount();
	for ( int i= 0; i < i_max; i++ )
	{
		iter = static_cast<PlginEntry*>( ui.tv_plugins->topLevelItem( i ) );
		if ( QString::compare( s_file, iter->file(), Qt::CaseInsensitive ) == 0 )
		{
			return iter;
		}
	}
	return NULL;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void			PluginsDlg::itemDoubleClicked		( 
		QTreeWidgetItem * it, int col )
{
	Q_UNUSED( col );
	PlginEntry * itm = static_cast<PlginEntry *>( it );
	if ( itm->checkState( 0 ) == Qt::Checked )
	{
		itm->setCheckState( 0, Qt::Unchecked );
	}
	else
	{
		itm->setCheckState( 0, Qt::Checked );
	}
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void			PluginsDlg::addDirectory			( void )
{
	static QString s_old_dir;
	QString dir = QFileDialog::getExistingDirectory(
				this, tr("Select Directory"),
				s_old_dir,
				QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
	if ( dir.isEmpty() == false )
	{
		s_old_dir = dir;
		ui.lv_dirs->addItem( new QListWidgetItem( dir ) );
		scanDirectory( dir );
	}
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void			PluginsDlg::remDirectory			( void )
{
	QList<QListWidgetItem*> sel = ui.lv_dirs->selectedItems();
	foreach( QListWidgetItem * itr, sel )
	{
		delete itr;
	}
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void			PluginsDlg::rescan					( void )
{
	scanDirectories();
	loadLibraryPlugins();
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void			PluginsDlg::validateAndClose		( void )
{
	/** @todo track errors; show them */
	PlginEntry * iter;
	int i_max = ui.tv_plugins->topLevelItemCount();
	for ( int i= 0; i < i_max; i++ )
	{
		iter = static_cast<PlginEntry*>( ui.tv_plugins->topLevelItem( i ) );
		if ( iter->shouldBeLoaded() )
		{
			if ( iter->wasLoaded() == false )
			{ /* load this plug-in */
				AprilLibrary::loadPlugIn( iter->file() );
			}
		}
		else
		{
			if ( iter->wasLoaded() )
			{ /* unload this plug-in */
				AprilLibrary::unloadPlugIn( iter->file() );
			}
		}
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







