
#include	<gtest/gtest.h>
#include	<april/aprillibrary.h>
#include	<april/logic/world.h>
#include	<april/plugins/aprilplugininterf.h>
#include	<QDir>

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
	
#ifndef QT_NO_DEBUG
	plg = AprilLibrary::loadPlugIn( "libsample_debug.so" );
#else
	plg = AprilLibrary::loadPlugIn( "libsample.so" );		
#endif
	EXPECT_TRUE( plg != NULL );
	EXPECT_EQ( plg->name(), "Sample PlugIn" );
	
	endAprilLibrary();
}
