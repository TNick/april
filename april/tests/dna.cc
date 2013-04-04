#include	<gtest/gtest.h>
#include	<april/aprillibrary.h>
#include	<april/logic/dna.h>
#include	<april/logic/dnaview.h>
#include	<april/logic/factory.h>

using namespace april;

TEST(DNA, basic) {
	initAprilLibrary();
	
	DNA		dna; // default invalid instance
	EXPECT_EQ( dna.isValid(), false );
	EXPECT_EQ( dna.kind(), InvalidId );
	EXPECT_EQ( dna.brains().length(), 0 );
	EXPECT_EQ( dna.actuators().length(), 0 );
	EXPECT_EQ( dna.sensors().length(), 0 );
	EXPECT_EQ( dna.reflexes().length(), 0 );
	
	EXPECT_EQ( dna.getView( InvalidId ).isValid(), false );
	EXPECT_EQ( dna.getView( 0 ).isValid(), false );
	EXPECT_EQ( dna.getView( 1 ).isValid(), false );
	EXPECT_EQ( dna.getView( 2 ).isValid(), false );
	
	QList<quint64>	l1;
	l1.reserve( DNA::OffMax );
	l1.append( 1 );
	l1.append( 0 );
	l1.append( 0 );
	l1.append( 0 );
	l1.append( 0 );
	l1.append( 4 ); // cost
	l1.append( 80 ); // age
	l1.append( 150 ); // birth energy
	dna.setValuesI( l1 );
	EXPECT_EQ( dna.kind(), (quint64)1 );
	EXPECT_EQ( dna.brains().length(), 0 );
	EXPECT_EQ( dna.actuators().length(), 0 );
	EXPECT_EQ( dna.sensors().length(), 0 );
	EXPECT_EQ( dna.reflexes().length(), 0 );
	
	
	
	endAprilLibrary();
}

TEST(DNA, brains) {
	initAprilLibrary();
	
	DNA		dna; // default invalid instance
	EXPECT_EQ( dna.brains().length(), 0 );
	EXPECT_FALSE( dna.addBrain( InvalidId ) );
	EXPECT_EQ( dna.brains().length(), 0 );
	EXPECT_TRUE( dna.addBrain( 1 ) );
	EXPECT_EQ( dna.brains().length(), 1 );
	EXPECT_EQ( dna.brains().at( 0 ), (quint64)1 );
	EXPECT_TRUE( dna.addBrain( 1 ) );
	EXPECT_EQ( dna.brains().length(), 2 );
	EXPECT_EQ( dna.brains().at( 0 ), (quint64)1 );
	EXPECT_EQ( dna.brains().at( 1 ), (quint64)1 );
	EXPECT_TRUE( dna.addBrain( 2 ) );
	EXPECT_EQ( dna.brains().length(), 3 );
	EXPECT_EQ( dna.brains().at( 0 ), (quint64)1 );
	EXPECT_EQ( dna.brains().at( 1 ), (quint64)1 );
	EXPECT_EQ( dna.brains().at( 2 ), (quint64)2 );
	
	endAprilLibrary();
}

TEST(DNA, actuators) {
	initAprilLibrary();
	
	DNA		dna; // default invalid instance
	EXPECT_EQ( dna.actuators().length(), 0 );
	EXPECT_FALSE( dna.addActuator( InvalidId ) );
	EXPECT_EQ( dna.actuators().length(), 0 );
	EXPECT_TRUE( dna.addActuator( 1 ) );
	EXPECT_EQ( dna.actuators().length(), 1 );
	EXPECT_EQ( dna.actuators().at( 0 ), (quint64)1 );
	EXPECT_TRUE( dna.addActuator( 1 ) );
	EXPECT_EQ( dna.actuators().length(), 2 );
	EXPECT_EQ( dna.actuators().at( 0 ), (quint64)1 );
	EXPECT_EQ( dna.actuators().at( 1 ), (quint64)1 );
	EXPECT_TRUE( dna.addActuator( 2 ) );
	EXPECT_EQ( dna.actuators().length(), 3 );
	EXPECT_EQ( dna.actuators().at( 0 ), (quint64)1 );
	EXPECT_EQ( dna.actuators().at( 1 ), (quint64)1 );
	EXPECT_EQ( dna.actuators().at( 2 ), (quint64)2 );
	
	endAprilLibrary();
}

TEST(DNA, sensors) {
	initAprilLibrary();
	
	DNA		dna; // default invalid instance
	EXPECT_EQ( dna.sensors().length(), 0 );
	EXPECT_FALSE( dna.addSensor( InvalidId ) );
	EXPECT_EQ( dna.sensors().length(), 0 );
	EXPECT_TRUE( dna.addSensor( 1 ) );
	EXPECT_EQ( dna.sensors().length(), 1 );
	EXPECT_EQ( dna.sensors().at( 0 ), (quint64)1 );
	EXPECT_TRUE( dna.addSensor( 1 ) );
	EXPECT_EQ( dna.sensors().length(), 2 );
	EXPECT_EQ( dna.sensors().at( 0 ), (quint64)1 );
	EXPECT_EQ( dna.sensors().at( 1 ), (quint64)1 );
	EXPECT_TRUE( dna.addSensor( 2 ) );
	EXPECT_EQ( dna.sensors().length(), 3 );
	EXPECT_EQ( dna.sensors().at( 0 ), (quint64)1 );
	EXPECT_EQ( dna.sensors().at( 1 ), (quint64)1 );
	EXPECT_EQ( dna.sensors().at( 2 ), (quint64)2 );
	
	endAprilLibrary();
}

TEST(DNA, reflexes) {
	initAprilLibrary();
	
	DNA		dna; // default invalid instance
	EXPECT_EQ( dna.reflexes().length(), 0 );
	EXPECT_FALSE( dna.addReflex( InvalidId ) );
	EXPECT_EQ( dna.reflexes().length(), 0 );
	EXPECT_TRUE( dna.addReflex( 1 ) );
	EXPECT_EQ( dna.reflexes().length(), 1 );
	EXPECT_EQ( dna.reflexes().at( 0 ), (quint64)1 );
	EXPECT_TRUE( dna.addReflex( 1 ) );
	EXPECT_EQ( dna.reflexes().length(), 2 );
	EXPECT_EQ( dna.reflexes().at( 0 ), (quint64)1 );
	EXPECT_EQ( dna.reflexes().at( 1 ), (quint64)1 );
	EXPECT_TRUE( dna.addReflex( 2 ) );
	EXPECT_EQ( dna.reflexes().length(), 3 );
	EXPECT_EQ( dna.reflexes().at( 0 ), (quint64)1 );
	EXPECT_EQ( dna.reflexes().at( 1 ), (quint64)1 );
	EXPECT_EQ( dna.reflexes().at( 2 ), (quint64)2 );
	
	endAprilLibrary();
}

TEST(DNA, basicMerge) {
	initAprilLibrary();
	
	DNA		dna; // default invalid instance
	DNA		dnap1;
	DNA		dnap2;
	
	EXPECT_EQ( dna.fromMerge( dnap1, dnap2 ), false );
	
	QList<quint64>	l1;
	l1.reserve( DNA::OffMax );
	l1.append( 1 );
	l1.append( 0 );
	l1.append( 0 );
	l1.append( 0 );
	l1.append( 0 );
	l1.append( 4 ); // cost
	l1.append( 80 ); // age
	l1.append( 150 ); // birth energy
	
	dna.setValuesI( l1 ); // values are clerared by the merge
	EXPECT_EQ( dna.fromMerge( dnap1, dnap2 ), false );
	EXPECT_EQ( dna.kind(), InvalidId );
	EXPECT_EQ( dna.brains().length(), 0 );
	EXPECT_EQ( dna.actuators().length(), 0 );
	EXPECT_EQ( dna.sensors().length(), 0 );
	EXPECT_EQ( dna.reflexes().length(), 0 );
	
	dnap1.setValuesI( l1 );
	EXPECT_EQ( dna.fromMerge( dnap1, dnap2 ), false );
	EXPECT_EQ( dna.kind(), InvalidId );
	
	dnap2.setValuesI( l1 );
	EXPECT_EQ( dna.fromMerge( dnap1, dnap2 ), true );
	EXPECT_NE( dna.kind(), InvalidId );
	EXPECT_EQ( dna.brains().length(), 0 );
	EXPECT_EQ( dna.actuators().length(), 0 );
	EXPECT_EQ( dna.sensors().length(), 0 );
	EXPECT_EQ( dna.reflexes().length(), 0 );
	
	endAprilLibrary();
}

TEST(DNA, complexMerge) {
	initAprilLibrary();
	
	DNA		dnap1;
	DNA		dnap2;
	
	QList<quint64>	l1;
	l1.reserve( DNA::OffMax );
	l1.append( 1 );
	l1.append( 0 );
	l1.append( 0 );
	l1.append( 0 );
	l1.append( 0 );
	l1.append( 4 ); // cost
	l1.append( 80 ); // age
	l1.append( 150 ); // birth energy
	dnap1.setValuesI( l1 );
	dnap2.setValuesI( l1 );
	
	DNA		dnaout1;
	dnap1.addBrain( 10 );
	dnap2.addBrain( 10 );
	EXPECT_TRUE( dnaout1.fromMerge( dnap1, dnap2 ) );
	EXPECT_TRUE( dnaout1.isValid() );
	EXPECT_EQ( dnaout1.brains().count(), 1 );
	EXPECT_EQ( dnaout1.brains().at( 0 ), (quint64)10 );
	
	DNA		dnaout2;
	dnap1.addBrain( 11 );
	dnap2.addBrain( 13 );
	EXPECT_TRUE( dnaout2.fromMerge( dnap1, dnap2 ) );
	EXPECT_TRUE( dnaout2.isValid() );
	EXPECT_EQ( dnaout2.brains().count(), 1 );
	EXPECT_TRUE( dnaout2.brains().contains( 10 ) || 
				 dnaout2.brains().contains( 11 ) ||
				 dnaout2.brains().contains( 13 ) );
	
	DNA		dnaout3;
	dnap1.addActuator( 10 );
	dnap2.addActuator( 10 );
	EXPECT_TRUE( dnaout3.fromMerge( dnap1, dnap2 ) );
	EXPECT_TRUE( dnaout3.isValid() );
	EXPECT_EQ( dnaout3.actuators().count(), 1 );
	EXPECT_EQ( dnaout3.actuators().at( 0 ), (quint64)10 );
	
	DNA		dnaout4;
	dnap1.addSensor( 15 );
	dnap2.addSensor( 15 );
	EXPECT_TRUE( dnaout4.fromMerge( dnap1, dnap2 ) );
	EXPECT_TRUE( dnaout4.isValid() );
	EXPECT_EQ( dnaout4.sensors().count(), 1 );
	EXPECT_EQ( dnaout4.sensors().at( 0 ), (quint64)15 );

	DNA		dnaout6;
	dnap1.addReflex( 69 );
	dnap2.addReflex( 69 );
	EXPECT_TRUE( dnaout6.fromMerge( dnap1, dnap2 ) );
	EXPECT_TRUE( dnaout6.isValid() );
	EXPECT_EQ( dnaout6.reflexes().count(), 1 );
	EXPECT_EQ( dnaout6.reflexes().at( 0 ), (quint64)69 );

	DNA		dnaout7;
	dnap1.addReflex( 76 );
	dnap2.addReflex( 91 );
	EXPECT_TRUE( dnaout7.fromMerge( dnap1, dnap2 ) );
	EXPECT_TRUE( dnaout7.isValid() );
	EXPECT_EQ( dnaout7.reflexes().count(), 3 );
	EXPECT_EQ( dnaout7.reflexes().at( 0 ), (quint64)69 );
	EXPECT_EQ( dnaout7.reflexes().at( 1 ), (quint64)76 );
	EXPECT_EQ( dnaout7.reflexes().at( 2 ), (quint64)91 );
	
	endAprilLibrary();
}

class TstFactory1	: public Factory {
public:
	TstFactory1() : Factory( NULL ) 
	{  }
	virtual QList<qreal> averageDNA ( ID id ) const { 
		Q_UNUSED( id );
		QList<qreal>	l;
		l.append( 13.3 );
		l.append( -113.3 );
		l.append( 913.3 );
		l.append( 0.34848 );
		return l; 
	}
};
class TstFactory2	: public Factory {
public:
	TstFactory2() : Factory( NULL ) 
	{  }
	virtual QList<qreal> averageDNA ( ID id ) const { 
		Q_UNUSED( id );
		QList<qreal>	l;
		l.append( 0.17201 );
		l.append( -78.3 );
		l.append( 13.3333 );
		l.append( 4450.3 );
		return l; 
	}
};
class TstFactory1_2	: public Factory {
public:
	TstFactory1_2() : Factory( NULL ) 
	{  }
	virtual QList<qreal> averageDNA ( ID id ) const { 
		Q_UNUSED( id );
		QList<qreal>	l;
		
		l.append( 17.3 );
		l.append( -89.3 );
		l.append( 1425.3 );
		l.append( 0.1188997 );
		l.append( 778899.3 );
		l.append( -0.1188997 );
		l.append( -778899.3 );
		return l; 
	}
};





TEST(DNA, getView) {
	initAprilLibrary();
	
//	DNA		dnaout1;
//	DNA		dnap1;
	DNA		dnap1;
	
	QList<quint64>	l1;
	l1.reserve( DNA::OffMax );
	l1.append( 1 );
	l1.append( 0 );
	l1.append( 0 );
	l1.append( 0 );
	l1.append( 0 );
	l1.append( 4 ); // cost
	l1.append( 80 ); // age
	l1.append( 150 ); // birth energy
	dnap1.setValuesI( l1 );
	
	TstFactory1 * tf1 = new TstFactory1();
	// will request default values from the factory
	DNAView view1 = dnap1.getView( 1, tf1 );
	EXPECT_TRUE( view1.isValid() );
	EXPECT_EQ( view1.value(0), (qreal)13.3 );
	EXPECT_EQ( view1.value(1), (qreal)-113.3 );
	EXPECT_EQ( view1.value(2), (qreal)913.3 );
	EXPECT_EQ( view1.value(3), (qreal)0.34848 );
	EXPECT_EQ( view1.identificator(), (quint64)1 );
	
	TstFactory2 * tf2 = new TstFactory2();
	// will request default values from the factory
	DNAView view2 = dnap1.getView( 2, tf2 );
	EXPECT_TRUE( view2.isValid() );
	EXPECT_EQ( view2.value(0), (qreal)0.17201 );
	EXPECT_EQ( view2.value(1), (qreal)-78.3 );
	EXPECT_EQ( view2.value(2), (qreal)13.3333 );
	EXPECT_EQ( view2.value(3), (qreal)4450.3 );
	EXPECT_EQ( view2.identificator(), (quint64)2 );

	TstFactory1_2 * tf1_2 = new TstFactory1_2();
	// will need reposition op
	DNAView view1_2 = dnap1.getView( 1, 7, tf1_2 );
	EXPECT_TRUE( view1_2.isValid() );
	// old intact
	EXPECT_EQ( view1_2.value(0), (qreal)13.3 );
	EXPECT_EQ( view1_2.value(1), (qreal)-113.3 );
	EXPECT_EQ( view1_2.value(2), (qreal)913.3 );
	EXPECT_EQ( view1_2.value(3), (qreal)0.34848 );
	// new
	EXPECT_EQ( view1_2.value(4), (qreal)778899.3 );
	EXPECT_EQ( view1_2.value(5), (qreal)-0.1188997 );
	EXPECT_EQ( view1_2.value(6), (qreal)-778899.3 );

	EXPECT_EQ( view1_2.identificator(), (quint64)1 );

	REMOVE_CONSTRUCTOR_REF(tf1);
	REMOVE_CONSTRUCTOR_REF(tf2);
	endAprilLibrary();
}


