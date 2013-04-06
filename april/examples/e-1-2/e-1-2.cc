
#include <iostream>

//! [include]
#include <april/aprillibrary.h>
#include <april/logic/world.h>
//! [include]

using namespace std;

//! [namespace]
using namespace april;
//! [namespace]


//! [const]
enum	Constants		{
	WORLD_ENERGY = 10000
};
//! [const]

int main ()
{
	//! [init]
	if ( initAprilLibrary() == false )
	{
		cerr << "Error! Failed to initialise april library!\n";
		return 1;
	}
	//! [init]
	
	//! [w]
	World * w = new World( "world-name", WORLD_ENERGY );
	cout << "World has been created!\n";
	//! [w]
	
	//! [querry]
	cout << "Total ammount of energy in the world: " << w->energy() <<"\n";
	cout << "Unbounded energy in the world: " << w->energyFree() <<"\n";
	cout << "Bounded (\"used\") energy: " << w->energyBounded() <<"\n";
	//! [querry]
	
	//! [refc]
	DEC_REF(w,w);
	//! [refc]
	
	
	//! [remw]
	AprilLibrary::remWorld( w );
	cout << "World has been destroyed!\n";
	//! [remw]
	
	
	//! [end]
	endAprilLibrary();
	//! [end]
	
	return 0;
}

