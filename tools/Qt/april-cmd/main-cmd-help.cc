#include	<QCoreApplication>
#include	<QStringList>
#include	<QSettings>
#include	<april/cmd/aprilmodule.h>

#define	NO_ARGUMENT		QString()

/* ------------------------------------------------------------------------- */
//! appliation entry point
int			main			( int argc, char *argv[] )
{
	int i_ret = 0;
	
	/* prepare to start */
	QCoreApplication apl( argc, argv );
	Q_UNUSED( apl );
	
	/* 000000000000000000000000000000000000000000000000000000000000000000000 */
	april::AprilModule::setUsage( 
				"a.new",
				QStringList()
				<< "<kind>",
				QStringList() 
				<< "create new actor instance",
				QStringList()
				<< "kind",
				QList<QStringList>()
				<< (QStringList()
					<< "the kind of the actor to produce;"
					<< "to create a kind use dna.new"),
				QStringList()
				<< "This function creates a new actor in current world."
				<< "The kind must be one that has an associated DNA."
				<< "The energy for the actor is taken from the free"
				<< "energy of the world."
				);
	april::AprilModule::setUsage( 
				"a.list",
				QStringList()
				<< NO_ARGUMENT,
				QStringList() 
				<< "lists actors in current world",
				QStringList(),
				QList<QStringList>(),
				QStringList() 
				<< "This function lists actors in current world"
				<< "and some of their basic properties"
				<< "(id, name of the id, date of birth and death,"
				<< "current age and ammount of energy inside)."
				);
	april::AprilModule::setUsage( 
				"a.kill",
				QStringList()
				<< "<index>",
				QStringList() 
				<< "kills an actor in current world",
				QStringList()
				<< "index",
				QList<QStringList>() 
				<< (QStringList() 
					<< "the index of the actor in the world"),
				QStringList() 
				<< "This function terminates an actor in current world"
				<< "(the actor may not be removed immediatelly but"
				<< "will be dead)."
				<< "The energy of the actor and of alll of its components"
				<< "will be added to the free energy of the current world."
				);
	april::AprilModule::setUsage( 
				"a.kinds",
				QStringList()
				<< NO_ARGUMENT,
				QStringList() 
				<< "list kinds of actors",
				QStringList(),
				QList<QStringList>(),
				QStringList() 
				<< "The list of registered types of actors."
				<< "This function lists all types but a.new"
				<< "is only capable of creating actors"
				<< "of kinds created with dna.new"
				);
	/* 000000000000000000000000000000000000000000000000000000000000000000000 */
	april::AprilModule::setUsage( 
				"ak.new",
				QStringList()
				<< "<actor> <id>",
				QStringList() 
				<< "create new actuator instance",
				QStringList()
				<< "actor"
				<< "id",
				QList<QStringList>()
				<< (QStringList()
					<< "destination actor where new actuator is created;"
					<< "this is the offset of the actor in the world list")
				<< (QStringList()
					<< "the ID of the new actuator to create;"
					<< "if the id is invalid or represents a different"
					<< "component the function fails."),
				QStringList()
				<< "This function creates a new actuator in an actor"
				<< "in current world."
				<< "The energy for the actuator is taken from the free"
				<< "energy of the world."
				);
	april::AprilModule::setUsage( 
				"ak.list",
				QStringList()
				<< "<actor>",
				QStringList() 
				<< "lists actors in current world",
				QStringList()
				<< "actor",
				QList<QStringList>()
				<< (QStringList()
					<< "the actor who'se actuators are listed;"
					<< "this is the offset of the actor in the world list"),
				QStringList() 
				<< "This function lists actuators in an actor in current world"
				<< "and some of their basic properties"
				<< "(id, name of the id, running cost and packed energy)."
				);
	april::AprilModule::setUsage( 
				"ak.kinds",
				QStringList()
				<< NO_ARGUMENT,
				QStringList() 
				<< "list kinds of actors",
				QStringList(),
				QList<QStringList>(),
				QStringList() 
				<< "The list of registered types of actuators in current world."
				);
	/* 000000000000000000000000000000000000000000000000000000000000000000000 */
	april::AprilModule::setUsage( 
				"april.commands",
				QStringList()
				<< NO_ARGUMENT,
				QStringList() 
				<< "lists the commands",
				QStringList(),
				QList<QStringList>(),
				QStringList()
				<< "The command lists ALL commands that are registered"
				<< "with the command system. If a command is accesible"
				<< "it is present in this list."
				);
	april::AprilModule::setUsage( 
				"april.modules",
				QStringList()
				<< NO_ARGUMENT,
				QStringList() 
				<< "lists the modules",
				QStringList(),
				QList<QStringList>(),
				QStringList()
				<< "The command lists ALL modules that are registered"
				<< "with the command system. This lists the long names"
				<< "that can't be used in a real command - these often use"
				<< "shorter forms for the commands."
				);
	april::AprilModule::setUsage( 
				"april.version",
				QStringList()
				<< NO_ARGUMENT,
				QStringList() 
				<< "display the version",
				QStringList(),
				QList<QStringList>(),
				QStringList()
				);
	april::AprilModule::setUsage( 
				"april.copyright",
				QStringList()
				<< NO_ARGUMENT,
				QStringList() 
				<< "display information about copyright",
				QStringList(),
				QList<QStringList>(),
				QStringList()
				<< "The command prints the content of the COPYING"
				<< "file if found, otherwise ives general directions."
				);
	april::AprilModule::setUsage( 
				"april.prompt",
				QStringList()
				<< "<new prompt>",
				QStringList() 
				<< "changes current prompt to new value",
				QStringList(),
				QList<QStringList>(),
				QStringList()
				<< "Any string provided as argument will be"
				<< "printed at the beginning of each command line."
				);
	/* 000000000000000000000000000000000000000000000000000000000000000000000 */
	april::AprilModule::setUsage( 
				"b.new",
				QStringList()
				<< "<actor> <id>",
				QStringList() 
				<< "create new brain instance",
				QStringList()
				<< "actor"
				<< "id",
				QList<QStringList>()
				<< (QStringList()
					<< "destination actor where new brain is created;"
					<< "this is the offset of the actor in the world list")
				<< (QStringList()
					<< "the ID of the new brain to create;"
					<< "if the id is invalid or represents a different"
					<< "component the function fails."),
				QStringList()
				<< "This function creates a new brain in an actor"
				<< "in current world."
				<< "The energy for the brain is taken from the free"
				<< "energy of the world."
				);
	april::AprilModule::setUsage( 
				"b.list",
				QStringList()
				<< "<actor>",
				QStringList() 
				<< "lists actors in current world",
				QStringList()
				<< "actor",
				QList<QStringList>()
				<< (QStringList()
					<< "the actor who'se brains are listed;"
					<< "this is the offset of the actor in the world list"),
				QStringList() 
				<< "This function lists brains in an actor in current world"
				<< "and some of their basic properties"
				<< "(id, name of the id, running cost and packed energy)."
				);
	april::AprilModule::setUsage( 
				"b.kinds",
				QStringList()
				<< NO_ARGUMENT,
				QStringList() 
				<< "list kinds of actors",
				QStringList(),
				QList<QStringList>(),
				QStringList() 
				<< "The list of registered types of brains in current world."
				);				
	/* 000000000000000000000000000000000000000000000000000000000000000000000 */
	april::AprilModule::setUsage( 
				"dna.new",
				QStringList()
				<< "[id] [cost] [age] [energy]",
				QStringList() 
				<< "creates a new kind",
				QStringList()
				<< "id"
				<< "cost"
				<< "age"
				<< "energy",
				QList<QStringList>() 
				<< (QStringList()
					<< "the name to assign to the new numeric ID that"
					<< "will be generated. If ommited, a new, unique"
					<< "name will be generated."
					<< "A form like this is recomended: Actor.Kind.<name>.")
				<< (QStringList()
					<< "the intrinsec energy cost for the agent per time"
					<< "unit; other components that are added will"
					<< "increase the total cost for running the agent.n"
					<< "This value must be an integer larger than 0."
					<< "By default the cost is set to 10.")
				<< (QStringList()
					<< "average age of death. This is an orientative"
					<< "value (suggestion). It must be larger than 0."
					<< "By default it is set to 100.")
				<< (QStringList()
					<< "energy required at birth. At least this ammount"
					<< "of energy units are assigned at birt to an agent"
					<< "of this kind. When the user creates the agent,"
					<< "the energy is substracted from the free energy"
					<< "of the world."
					<< "By default it is set to 10.")
				,
				QStringList()
				);
	april::AprilModule::setUsage( 
				"dna.list",
				QStringList()
				<< NO_ARGUMENT,
				QStringList() 
				<< "lists available kinds in this world",
				QStringList(),
				QList<QStringList>(),
				QStringList()
				<< "These are the IDs that are available for a.new command."
				);
	april::AprilModule::setUsage( 
				"dna.info",
				QStringList()
				<< "<id>",
				QStringList() 
				<< "detalied information about a kind",
				QStringList()
				<< "id",
				QList<QStringList>()
				<< (QStringList() 
					<< "An id previously registered using dna.new"),
				QStringList()
				<< "The function provides a lot of details about"
				<< "the DNA for a certain kind. This includes:"
				<< "- id and name"
				<< "- running cost for the actor"
				<< "- ammount of energy at birth"
				<< "- list of brains, reflexes, sensors and actuators"
				<< "- the list of partitions and details about them"
				);
	april::AprilModule::setUsage( 
				"dna.s",
				QStringList()
				<< "<kind> <id>",
				QStringList() 
				<< "add a sensor to a DNA sequence",
				QStringList()
				<< "kind"
				<< "id",
				QList<QStringList>()
				<< (QStringList() 
					<< "A kind previously registered using dna.new (id)")
				<< (QStringList() 
					<< "The id of the sensor to add; this id must be"
					<< "valid (the function checks it before proceeding)"),
				QStringList()
				<< "The actors created based on this DNA will all attempt"
				<< "to create for themselves a sensor of this kind."
				);
	april::AprilModule::setUsage( 
				"dna.ak",
				QStringList()
				<< "<kind> <id>",
				QStringList() 
				<< "add a actuator to a DNA sequence",
				QStringList()
				<< "kind"
				<< "id",
				QList<QStringList>()
				<< (QStringList() 
					<< "A kind previously registered using dna.new (id)")
				<< (QStringList() 
					<< "The id of the actuator to add; this id must be"
					<< "valid (the function checks it before proceeding)"),
				QStringList()
				<< "The actors created based on this DNA will all attempt"
				<< "to create for themselves a actuator of this kind."
				);
	april::AprilModule::setUsage( 
				"dna.b",
				QStringList()
				<< "<kind> <id>",
				QStringList() 
				<< "add a brain to a DNA sequence",
				QStringList()
				<< "kind"
				<< "id",
				QList<QStringList>()
				<< (QStringList() 
					<< "A kind previously registered using dna.new (id)")
				<< (QStringList() 
					<< "The id of the brain to add; this id must be"
					<< "valid (the function checks it before proceeding)"),
				QStringList()
				<< "The actors created based on this DNA will all attempt"
				<< "to create for themselves a brain of this kind."
				<< "Note that there is nothing stpping an actor to have"
				<< "more than one brains."
				);
	april::AprilModule::setUsage( 
				"dna.r",
				QStringList()
				<< "<kind> <id>",
				QStringList() 
				<< "add a reflex to a DNA sequence",
				QStringList()
				<< "kind"
				<< "id",
				QList<QStringList>()
				<< (QStringList() 
					<< "A kind previously registered using dna.new (id)")
				<< (QStringList() 
					<< "The id of the reflex to add; this id must be"
					<< "valid (the function checks it before proceeding)"),
				QStringList()
				<< "The actors created based on this DNA will all attempt"
				<< "to create for themselves a reflex of this kind."
				);
	/* 000000000000000000000000000000000000000000000000000000000000000000000 */
	april::AprilModule::setUsage( 
				"e.new",
				QStringList()
				<< "<id>",
				QStringList() 
				<< "create new event source",
				QStringList()
				<< "id",
				QList<QStringList>()
				<< (QStringList()
					<< "a previously registered id for the event to create;"
					<< "the function checks this id for validity before proceding."),
				QStringList()
				<< "This function creates a new event source"
				<< "in current world."
				);
	april::AprilModule::setUsage( 
				"e.list",
				QStringList()
				<< NO_ARGUMENT,
				QStringList() 
				<< "lists event sources in current world",
				QStringList(),
				QList<QStringList>(),
				QStringList() 
				<< "This function lists event sources in current world"
				<< "and some of their basic properties"
				<< "(id, name of the id)."
				);
	april::AprilModule::setUsage( 
				"e.kinds",
				QStringList()
				<< NO_ARGUMENT,
				QStringList() 
				<< "list registered kinds of events",
				QStringList(),
				QList<QStringList>(),
				QStringList() 
				<< "The list of registered types of event sources"
				<< "in current world."
				);
	/* 000000000000000000000000000000000000000000000000000000000000000000000 */
	april::AprilModule::setUsage( 
				"id.new",
				QStringList()
				<< "<name>",
				QStringList() 
				<< "create new unique id in current world",
				QStringList()
				<< "name",
				QList<QStringList>()
				<< (QStringList()
					<< "the string to be associated with the new"
					<< "numeric id that will be created."),
				QStringList()
				<< "This function will check if that name"
				<< "is already associted with an id and will"
				<< "refuse to create the id if that is the case."
				);
	april::AprilModule::setUsage( 
				"id.list",
				QStringList()
				<< NO_ARGUMENT,
				QStringList() 
				<< "lists registered IDs in current world",
				QStringList(),
				QList<QStringList>(),
				QStringList() 
				<< "Along with the numeric value the strings"
				<< "associated with them are also printed."
				);
	april::AprilModule::setUsage( 
				"id.info",
				QStringList()
				<< "<id>",
				QStringList() 
				<< "information about this id",
				QStringList()
				<< "id",
				QList<QStringList>()
				<< (QStringList()
					<< "An id previously registered with id.new"
					<< "or with other functions that register IDs"),
				QStringList()
				);
	/* 000000000000000000000000000000000000000000000000000000000000000000000 */
	april::AprilModule::setUsage( 
				"p.load",
				QStringList()
				<< "<file-name>" ,
				QStringList() 
				<< "loads specified plug-in file",
				QStringList(),
				QList<QStringList>(),
				QStringList()
				);
	april::AprilModule::setUsage( 
				"p.unload",
				QStringList()
				<< "<index>"
				<< "<name>" ,
				QStringList() 
				<< "unloads the plug-in at specified index"
				<< "unloads the plug-in having that name",
				QStringList(),
				QList<QStringList>(),
				QStringList()
				);
	april::AprilModule::setUsage( 
				"p.list",
				QStringList()
				<< NO_ARGUMENT,
				QStringList() 
				<< "lists the plug-ins and their paths",
				QStringList(),
				QList<QStringList>(),
				QStringList()
				);
	/* 000000000000000000000000000000000000000000000000000000000000000000000 */
	april::AprilModule::setUsage( 
				"r.new",
				QStringList()
				<< "<actor> <id>",
				QStringList() 
				<< "create new reflex instance",
				QStringList()
				<< "actor"
				<< "id",
				QList<QStringList>()
				<< (QStringList()
					<< "destination actor where new reflex is created;"
					<< "this is the offset of the actor in the world list")
				<< (QStringList()
					<< "the ID of the new reflex to create;"
					<< "if the id is invalid or represents a different"
					<< "component the function fails."),
				QStringList()
				<< "This function creates a new reflex in an actor"
				<< "in current world."
				<< "The energy for the reflex is taken from the free"
				<< "energy of the world."
				);
	april::AprilModule::setUsage( 
				"r.list",
				QStringList()
				<< "<actor>",
				QStringList() 
				<< "lists actors in current world",
				QStringList()
				<< "actor",
				QList<QStringList>()
				<< (QStringList()
					<< "the actor who'se reflexs are listed;"
					<< "this is the offset of the actor in the world list"),
				QStringList() 
				<< "This function lists reflexs in an actor in current world"
				<< "and some of their basic properties"
				<< "(id, name of the id, running cost and packed energy)."
				);
	april::AprilModule::setUsage( 
				"r.kinds",
				QStringList()
				<< NO_ARGUMENT,
				QStringList() 
				<< "list kinds of actors",
				QStringList(),
				QList<QStringList>(),
				QStringList() 
				<< "The list of registered types of reflexs in current world."
				);
	/* 000000000000000000000000000000000000000000000000000000000000000000000 */
	april::AprilModule::setUsage( 
				"s.new",
				QStringList()
				<< "<actor> <id>",
				QStringList() 
				<< "create new sensor instance",
				QStringList()
				<< "actor"
				<< "id",
				QList<QStringList>()
				<< (QStringList()
					<< "destination actor where new sensor is created;"
					<< "this is the offset of the actor in the world list")
				<< (QStringList()
					<< "the ID of the new sensor to create;"
					<< "if the id is invalid or represents a different"
					<< "component the function fails."),
				QStringList()
				<< "This function creates a new sensor in an actor"
				<< "in current world."
				<< "The energy for the sensor is taken from the free"
				<< "energy of the world."
				);
	april::AprilModule::setUsage( 
				"s.list",
				QStringList()
				<< "<actor>",
				QStringList() 
				<< "lists actors in current world",
				QStringList()
				<< "actor",
				QList<QStringList>()
				<< (QStringList()
					<< "the actor who'se sensors are listed;"
					<< "this is the offset of the actor in the world list"),
				QStringList() 
				<< "This function lists sensors in an actor in current world"
				<< "and some of their basic properties"
				<< "(id, name of the id, running cost and packed energy)."
				);
	april::AprilModule::setUsage( 
				"s.kinds",
				QStringList()
				<< NO_ARGUMENT,
				QStringList() 
				<< "list kinds of actors",
				QStringList(),
				QList<QStringList>(),
				QStringList() 
				<< "The list of registered types of sensors in current world."
				);
	/* 000000000000000000000000000000000000000000000000000000000000000000000 */
	april::AprilModule::setUsage( 
				"w.new",
				QStringList()
				<< NO_ARGUMENT
				<< "[name] [energy]" ,
				QStringList() 
				<< "creates a new world with default values"
				<< "creates a world with given name and energy",
				QStringList()
				<< "name"
				<< "energy",
				QList<QStringList>()
				<< (QStringList()
					<< "the name of the world; this will identify the"
					<< "world in future dialogs; when no name is given"
					<< "an unique one is generated;")
				<< (QStringList()
					<< "the ammount of energy in the world; this must be"
					<< "a positive integer. In order to set the energy"
					<< "you MUST set a name. By default the energy is set"
					<< "to 100000 units."),
				QStringList()
				);
	april::AprilModule::setUsage( 
				"w.open",
				QStringList()
				<< "<file-name>" ,
				QStringList() 
				<< "opens specified file and loads the world inside",
				QStringList(),
				QList<QStringList>(),
				QStringList()
				);
	april::AprilModule::setUsage( 
				"w.save",
				QStringList()
				<< "[name] [file]"
				<< "[index] [file]" ,
				QStringList() 
				<< "saves specified world to a file"
				<< "saves specified world to a file",
				QStringList()
				<< "name"
				<< "energy",
				QList<QStringList>()
				<< (QStringList()
					<< "the name of the world.")
				<< (QStringList()
					<< "where to save; if not specified the"
					<< "file asociated with the world is used."),
				QStringList() 
				<< "If the opperation is succefull the internal association"
				<< "is also updated."
				);
	april::AprilModule::setUsage( 
				"w.close",
				QStringList()
				<< "<index>"
				<< "<name>" ,
				QStringList() 
				<< "close the world at specified index"
				<< "close the world having that name",
				QStringList(),
				QList<QStringList>(),
				QStringList()
				);
	april::AprilModule::setUsage( 
				"w.list",
				QStringList()
				<< NO_ARGUMENT,
				QStringList() 
				<< "lists the worlds and basic properties",
				QStringList(),
				QList<QStringList>(),
				QStringList()
				);
	april::AprilModule::setUsage( 
				"w.start",
				QStringList()
				<< "<index>"
				<< "<name>" ,
				QStringList() 
				<< "starts the world at specified index"
				<< "starts the world having that name",
				QStringList(),
				QList<QStringList>(),
				QStringList()
				);
	april::AprilModule::setUsage( 
				"w.stop",
				QStringList()
				<< "<index>"
				<< "<name>" ,
				QStringList() 
				<< "stops the world at specified index"
				<< "stops the world having that name",
				QStringList(),
				QList<QStringList>(),
				QStringList()
				);
	april::AprilModule::setUsage( 
				"w.adv",
				QStringList()
				<< "<index> [steps]"
				<< "<name> [steps]" ,
				QStringList() 
				<< "advances the world at specified index 'steps' time units"
				<< "advances the world having that name 'steps' time units",
				QStringList(),
				QList<QStringList>(),
				QStringList()
				);
	april::AprilModule::setUsage( 
				"w.crt",
				QStringList()
				<< NO_ARGUMENT
				<< "<index>"
				<< "<name>" ,
				QStringList() 
				<< "prints the name of current world"
				<< "changes current world to the one indicated by index"
				<< "changes current world to the one indicated by name",
				QStringList(),
				QList<QStringList>(),
				QStringList()
				);
	/* 000000000000000000000000000000000000000000000000000000000000000000000 */
	
	/* --------------------------------------------------------------------- */
	/* now read 'em */
	/* --------------------------------------------------------------------- */
	
	QSettings	stg( "help.dat", QSettings::IniFormat );
	QStringList sl = stg.childGroups();
	sl.sort();
	foreach( QString s, sl )
	{
		qDebug() << QString( 2, QChar( '\n' ) ).toLatin1().constBegin();
		qDebug() << QString( 80, QChar( '=' ) ).toLatin1().constBegin();
		qDebug() << QString( ">" + s + " help" ).toLatin1().constBegin();
		qDebug() << april::AprilModule::getCLUsage( s ).toLatin1().constBegin();
		qDebug() << QString( 80, QChar( '=' ) ).toLatin1().constBegin();
	}
	
	return i_ret;
}
/* ========================================================================= */
