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
static const char * f_act_name = "Actor.Factory.Test";

class TstWorld : public World {
	friend class TstFact;
public:
	int test_int_;
protected:
	TstWorld(const QString & s, quint64 tot_energ) : World(s,tot_energ) {
		test_int_ = rand() % 12345;
	}
	virtual QString		factoryName			( void ) const
	{ return f_name; }
	virtual bool	save				( QSettings & stg ) const
	{
		bool b = true;
		b = b & World::save( stg );
		stg.beginGroup( "TstWorld" );
		stg.setValue( "test_int_", test_int_ );
		stg.endGroup();
		return b;
	}
	virtual bool	load				( QSettings & stg )
	{
		bool b = true;
		
		b = World::load( stg );
		if ( !b ) return false;
		
		stg.beginGroup( "TstWorld" );
		for(;;) {
			
			test_int_ = stg.value( "test_int_", 0 ).toInt( &b );
			if ( !b ) break;
			
			break;
		}
		stg.endGroup();
		
		return b;
	}
}; /* .............................................................. */
class TstFact : public WorldFactory	{
public:
	TstFact() : WorldFactory( f_name ) {
	}
	virtual World * create ( const QString & s, quint64 tot_energ ) {
		return new TstWorld( s, tot_energ );
	}
	virtual World * create ( QSettings & stg ) {
		World * w = new TstWorld( w_name, 0 );
		if ( w->load( stg ) == false )
		{
			DEC_REF(w,w);
			AprilLibrary::remWorld( w );
			return NULL;
		}
		return w;
	}
}; /* .............................................................. */
class TstActor : public Actor {
	friend class TstFactActor;
public:
	int test_int_;
protected:
	TstActor( World * w ) : Actor( w ) {
		test_int_ = rand() % 22345;
	}
	virtual QString		factoryName		( void ) const
	{ return f_act_name; }
	bool			save				( QSettings & s ) const {
		bool b = true;
		
		return b;
	}
	bool			load				( QSettings & s ) {
		bool b = true;
		
		return b;
	}
}; /* .............................................................. */
class TstFactActor : public ActorFactory	{
public:
	TstFactActor( World * w ) : ActorFactory( w ) {
	}
	Actor *			create				( ID id ) {
		Q_UNUSED( id );
		
		return NULL;
	}
	bool			save				( QSettings & s ) const {
		bool b = true;
		
		return b;
	}
	bool			load				( QSettings & s ) {
		bool b = true;
		
		return b;
	}
}; /* .............................................................. */
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
	
	saveload2_cc::TstWorld * loaded_w = 
			static_cast<saveload2_cc::TstWorld *>( saveload2_cc::loadWorld( tf.fileName() ) );
	EXPECT_TRUE( loaded_w != NULL );
	EXPECT_EQ( loaded_w->test_int_, tstw->test_int_ );
	EXPECT_EQ( loaded_w->payload().i_, tstw->payload().i_ );
	EXPECT_EQ( loaded_w->name(), tstw->name() );
	EXPECT_EQ( loaded_w->currentTime(), tstw->currentTime() );
	EXPECT_EQ( loaded_w->energy(), tstw->energy() );
	EXPECT_EQ( loaded_w->energyBounded(), tstw->energyBounded() );
	EXPECT_EQ( loaded_w->energyFree(), tstw->energyFree() );
	EXPECT_TRUE( loaded_w->sameUId( tstw ) );
	
	
	
	
	DEC_REF(loaded_w,loaded_w);
	DEC_REF(tstw,tstw);
	AprilLibrary::unregisterFactory( saveload2_cc::f_name, saveload2_cc::factoryCreatorWorlds );
	endAprilLibrary();
	
}
