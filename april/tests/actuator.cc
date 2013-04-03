#include	<gtest/gtest.h>
#include	<april/aprillibrary.h>
#include	<april/logic/world.h>
#include	<april/logic/actuator.h>
#include	<april/logic/actor.h>
#include	<april/logic/actuatorfactory.h>

using namespace april;

TEST(Actuator, init) {

	initAprilLibrary();
	World * w = new World( "test-world", 1000 );
	DEC_REF( w, w );
	
	Actor * ag = new Actor( w );
	DEC_REF(ag,ag);
	Actuator * act = new Actuator( ag );
	DEC_REF(act,act);
	
	
	endAprilLibrary();
}

enum TestId	{
	TestId = 1
};

//class TstFact : public ActuatorFactory	{
//public:
	
//	TstFact( World * w ) 
//		: ActuatorFactory( w )
//	{
//		addMyself( TestId );
//		DNA & d = defaultDNA();
//		DNA src( w, TestId );
//		d = src;
//	}
	
//	virtual Actuator *			create				( ID id )
//	{
//		Q_UNUSED( id );
//		Q_ASSERT( id == TestId );
//		Actuator * ret = new Actuator( world() );
		
//		return ret;
//	}

//	virtual void			copyDefaultDNA		( DNA & destination )
//	{ 
//		destination = defaultDNA();
//	}

//};

//TEST(Actuator, factory) {
	
//	initAprilLibrary();
//	World * w = new World( "test-world", 1000 );
//	DEC_REF( w, w );
	
//	TstFact * fact = new TstFact( w );
//	DEC_REF( fact, fact );
	
//	Actuator * a = w->createActuator( TestId );
//	EXPECT_TRUE( a != NULL );
	
	
	
//	endAprilLibrary();
//}

