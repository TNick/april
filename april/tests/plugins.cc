
#include	<gtest/gtest.h>
#include	<april/aprillibrary.h>
#include	<april/logic/world.h>
#include	<april/plugins/aprilplugininterf.h>
#include	<QDir>
#include	<qglobal.h>

using namespace april;

TEST(Plugins, load_unload) {
	
	initAprilLibrary();
	
	AprilPluginInterf *	plg;
	plg = AprilLibrary::loadPlugIn( "inexisting" );
	EXPECT_TRUE( plg == NULL );
	plg = AprilLibrary::findPlugIn( "inexisting" );
	EXPECT_TRUE( plg == NULL );
	plg = AprilLibrary::findPlugInRel( "inexisting" );
	EXPECT_TRUE( plg == NULL );
	
#ifdef Q_OS_WIN
# ifndef QT_NO_DEBUG
	plg = AprilLibrary::loadPlugIn( "sample_debug.dll" );
# else
	plg = AprilLibrary::loadPlugIn( "sample.dll" );		
# endif
#else
# ifndef QT_NO_DEBUG
	plg = AprilLibrary::loadPlugIn( "libsample_debug.so" );
# else
	plg = AprilLibrary::loadPlugIn( "libsample.so" );		
# endif
#endif

	EXPECT_TRUE( plg != NULL );
	EXPECT_EQ( plg->name(), "Sample PlugIn" );
	
	endAprilLibrary();
}
