
#include <iostream>

#include <april/aprillibrary.h>
#include <april/logic/world.h>
//! [incdir]
#include <april/logic/director.h>
//! [incdir]

using namespace std;
using namespace april;

enum	Constants		{
	WORLD_ENERGY = 10000
};

static void advancedCustomDirector(World * w);

int main ()
{
	if ( initAprilLibrary() == false )
	{
		cerr << "Error! Failed to initialise april library!\n";
		return 1;
	}
	
	World * w = new World( "world-name", WORLD_ENERGY );
	cout << "World has been created!\n";
	
	cout << "Total ammount of energy in the world: " << w->energy() << "\n";
	cout << "Unbounded energy in the world: " << w->energyFree() << "\n";
	cout << "Bounded (\"used\") energy: " << w->energyBounded() << "\n";
	
	
	cout << "World is running: " << w->isRunning() << "\n";
	cout << "Current time in the world is: " << w->currentTime() << "\n";
	
	//! [start]
	if ( w->start() )
		//! [start]
	{
		//! [isr]
		cout << "World is running: " << w->isRunning() << "\n";
		//! [isr]
		
		//! [advance]
		for ( int i = 0; i < 3; i++ )
		{
			w->advance();
			cout << "Current time in the world is: " << w->currentTime() << "\n";
		}
		//! [advance]
		
		//! [stop]
		w->stop();
		//! [stop]
	}
	
	advancedCustomDirector( w );
	
	DEC_REF(w,w);
	AprilLibrary::remWorld( w );
	cout << "World has been destroyed!\n";
	
	endAprilLibrary();
	
	return 0;
}

//! [class]
class CustomDirector : public Director {
	//! [class]
public:
	
	
	//! [ctor]
	CustomDirector( World * w ) : Director( w )
	{
		cout << "Custom director created;\n";
	}
	//! [ctor]
	
	//! [cd_start]
	virtual bool		start			( void )
	{ 
		cout << "    - custom director starts the world;\n";
		return true; 
	}
	//! [cd_start]
	
	//! [cd_stop]
	virtual void		stop			( void )
	{
		cout << "    - custom director stops the world;\n";	
	}
	//! [cd_stop]
	
	//! [cd_adv]
	virtual void		advance			( void )
	{
		cout << "    - custom director advances the world;\n";
		stepTime();
		/* todo: advance components */	
	}
	//! [cd_adv]
	
};


static void advancedCustomDirector(World * w)
{
	//! [test_cst]
	CustomDirector * cust_dir = new CustomDirector( w );
	w->setDirector( cust_dir );
	DEC_REF(cust_dir,cust_dir);
	
	cout << "Custom director informs us about the action it takes:\n";
	w->start();
	w->advance();
	w->stop();
	
	w->setDirector( NULL ); // our director gets destroyed at this time
	
	cout << "Default director does not informs us about the action it takes...\n";
	w->start();
	w->advance();
	w->stop();
	cout << "... so no output is shown:\n";
	//! [test_cst]
	
}

