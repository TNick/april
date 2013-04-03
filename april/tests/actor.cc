#include	<gtest/gtest.h>
#include	<april/aprillibrary.h>
#include	<april/logic/world.h>
#include	<april/logic/actor.h>
#include	<april/logic/actorfactory.h>

using namespace april;

TEST(Actor, init) {

	initAprilLibrary();
	World * w = new World( "test-world", 1000 );
	DEC_REF( w, w );

	Actor * ag = new Actor( w );
	DEC_REF(ag,ag);
	EXPECT_TRUE( ag->firstSensor() == NULL );
	EXPECT_TRUE( ag->firstActuator() == NULL );
	EXPECT_TRUE( ag->firstReflex() == NULL );
	EXPECT_TRUE( ag->firstBrain() == NULL );
	EXPECT_EQ( ag->kind(), InvalidId );
	EXPECT_EQ( ag->kindName(), QString() );
	EXPECT_EQ( ag->birth(), (quint64)0 );
	EXPECT_EQ( ag->death(), (quint64)0 );
	EXPECT_EQ( ag->age(), (quint64)0 );
	EXPECT_EQ( ag->toLive(), (quint64)0 );
	EXPECT_EQ( ag->energy(), (quint64)0 );
	EXPECT_EQ( ag->cost(), (quint64)0 );
	EXPECT_EQ( ag->isAlive(), false );
	EXPECT_EQ( ag->dies(), true );
	EXPECT_TRUE( ag->payload().p_ == NULL );
	
	endAprilLibrary();
}

enum TestId	{
	TestId = 1
};

class TstFact : public ActorFactory	{
public:
	
	TstFact( World * w ) 
		: ActorFactory( w )
	{
		addMyself( TestId );
		DNA & d = defaultDNA();
		DNA src( w, TestId );
		d = src;
	}
	
	virtual Actor *			create				( ID id )
	{
		Q_UNUSED( id );
		Q_ASSERT( id == TestId );
		Actor * ret = new Actor( world() );
		
		return ret;
	}

	virtual void			copyDefaultDNA		( DNA & destination )
	{ 
		destination = defaultDNA();
	}

};

TEST(Actor, factory) {
	
	initAprilLibrary();
	World * w = new World( "test-world", 1000 );
	DEC_REF( w, w );
	
	TstFact * fact = new TstFact( w );
	DEC_REF( fact, fact );
	
	Actor * a = w->createActor( TestId );
	EXPECT_TRUE( a != NULL );
	
	
	
	endAprilLibrary();
}
