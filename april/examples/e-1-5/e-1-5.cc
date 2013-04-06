
#include <iostream>

#include <april/aprillibrary.h>
#include <april/logic/world.h>
//! [incdir]
#include <april/logic/dna.h>
//! [incdir]
//! [incdirfactory]
#include <april/logic/factory.h>
//! [incdirfactory]

using namespace std;
using namespace april;

enum	Constants		{
	WORLD_ENERGY = 10000,
	IdKind = 1,
	IdBrain,
	IdSensor,
	IdReflex,
	IdActuator
};

//! [dnaproxy]
class DNAProxy	: public DNA	{
public:
	void			initDNAProxy			( const InitData & init )
	{
		initDNA( init );
	}
};
//! [dnaproxy]

//! [fproxy]
class FactoryProxy : public Factory {
public:
	FactoryProxy( World * w ) : Factory( w )
	{ }
	virtual QList<qreal>		averageDNA		( ID id ) const
	{ 
		cout << "Default data requested for id " << id << "\n";
		QList<qreal>	ql;
		ql << 1.5 << 1.6 << 1.7;
		return ql;
	}
};
//! [fproxy]

int main ()
{
	if ( initAprilLibrary() == false )
	{
		cerr << "Error! Failed to initialise april library!\n";
		return 1;
	}
	
	World * w = new World( "world-name", WORLD_ENERGY );
	cout << "World has been created!\n";

//! [dnainst]
	DNAProxy dna;
	cout << "Valid DNA instance: " << dna.isValid() << "\n";
//! [dnainst]
	
//! [dnainit]
	DNA::InitData initd;
	initd.kind_ = IdKind;
	initd.cost_ = 1;
	initd.age_ = 100;
	initd.energy_ = 10;
	dna.initDNAProxy( initd );
	cout << "Valid DNA instance: " << dna.isValid() << "\n";
	cout << "  - kind ID: " << dna.kind() << "\n";
	cout << "  - cost: " << dna.cost() << "\n";
	cout << "  - age: " << dna.age() << "\n";
	cout << "  - energy: " << dna.energy() << "\n";
//! [dnainit]

//! [nocomp]
	cout << "  - number of sensors: " << dna.sensors().count() << "\n";
	cout << "  - number of reflexes: " << dna.reflexes().count() << "\n";
	cout << "  - number of brains: " << dna.brains().count() << "\n";
	cout << "  - number of actuators: " << dna.actuators().count() << "\n";
//! [nocomp]
	
//! [addcomp]
	dna.addBrain( IdBrain );
	dna.addActuator( IdActuator );
	dna.addSensor( IdSensor );
	dna.addReflex( IdReflex );
	
	cout << "DNA instance after component insertion: \n";
	cout << "  - number of sensors: " << dna.sensors().count() << "\n";
	cout << "  - number of reflexes: " << dna.reflexes().count() << "\n";
	cout << "  - number of brains: " << dna.brains().count() << "\n";
	cout << "  - number of actuators: " << dna.actuators().count() << "\n";
//! [addcomp]
	
	
//! [realvals]
	FactoryProxy * fact = new FactoryProxy( w );
	DNAView v = dna.getView( IdBrain, fact );
	cout << "DNA sequence for the brain ID " << v.identificator() << ":\n";
	cout << "  " << v.value( 0 );
	cout << "  " << v.value( 1 );
	cout << "  " << v.value( 2 );
	cout << "\n";
	
	DEC_REF(fact,fact);
//! [realvals]

	DEC_REF(w,w);
	AprilLibrary::remWorld( w );
	cout << "World has been destroyed!\n";
	
	endAprilLibrary();

	return 0;
}

