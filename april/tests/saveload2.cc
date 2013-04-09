#include	<gtest/gtest.h>
#include	<april/aprillibrary.h>
#include	<april/logic/world.h>
#include	<april/logic/worldfactory.h>
#include	<april/logic/actor.h>
#include	<april/logic/actorfactory.h>
#include	<april/logic/brain.h>
#include	<april/logic/brainfactory.h>
#include	<april/logic/actuator.h>
#include	<april/logic/actuatorfactory.h>
#include	<april/logic/reflex.h>
#include	<april/logic/reflexfactory.h>
#include	<april/logic/sensor.h>
#include	<april/logic/sensorfactory.h>

#include	<QTemporaryFile>

using namespace april;

/* ----------------------------------------------------- */
namespace	saveload2_cc		{

static const char * f_name = "World.Factory.Test";
static const char * w_name = "World.Test";

class TstWorld : public World {
friend class TstFact;
protected:
	TstWorld(const QString & s, quint64 tot_energ) : World(s,tot_energ) {
	
	}
};

class TstFact : public WorldFactory	{
public:
	TstFact() : WorldFactory( f_name ) {
	}
	virtual World * create ( const QString & s, quint64 tot_energ ) {
		return new TstWorld( s, tot_energ );
	}
	virtual World * create ( QSettings & stg ) {
		
		return new TstWorld( w_name, 0 );
	}

}; 

Factory * factoryCreatorWorlds ( const QString & s_name )
{
	Q_UNUSED( s_name );
	Factory * f = AprilLibrary::findWorldFactory( f_name );
	if ( f == NULL )
	{
		f = new TstFact();
	}
	return f;
}
void saveWorld ( World * w, const QString & s_file )
{
	QSettings s_out( s_file, QSettings::IniFormat );
	EXPECT_TRUE( w->save( s_out ) );
	s_out.sync();
}
World * loadWorld ( const QString & s_file )
{
	QSettings s_out( s_file, QSettings::IniFormat );
	World * ret = World::fromStg( s_out );
	EXPECT_TRUE( ret != NULL );
	return ret;
}

}	/* namespace saveload2_cc */
/* ----------------------------------------------------- */

TEST(SaveLoad2, basic) {

	QTemporaryFile	tf;
	tf.open();
	
	initAprilLibrary();
	AprilLibrary::registerFactory( 
	saveload2_cc::f_name, 
	saveload2_cc::factoryCreatorWorlds );
	
	saveload2_cc::TstFact * tstf = new saveload2_cc::TstFact();
	DEC_REF(tstf,tstf);
	saveload2_cc::TstWorld * tstw = 
			static_cast<saveload2_cc::TstWorld *>(tstf->create( "sample-world", 10000 ));
	
	saveload2_cc::saveWorld( tstw, tf.fileName() );
	
	World * loaded_w = saveload2_cc::loadWorld( tf.fileName() );
	EXPECT_TRUE( loaded_w == NULL );
	
	AprilLibrary::unregisterFactory( saveload2_cc::f_name, saveload2_cc::factoryCreatorWorlds );
	endAprilLibrary();
	
}
