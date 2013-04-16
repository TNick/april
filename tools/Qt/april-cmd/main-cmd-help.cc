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
				"april.commands",
				QStringList()
				<< NO_ARGUMENT,
				QStringList() 
				<< "lists the commands",
				QStringList(),
				QList<QStringList>(),
				QStringList()
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
				<< "lists the available kinds in this world",
				QStringList(),
				QList<QStringList>(),
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
	april::AprilModule::setUsage( 
				"a.new",
				QStringList()
				<< NO_ARGUMENT
				<< "<kind>",
				QStringList() 
				<< "the kind of the actor to produce",
				QStringList(),
				QList<QStringList>(),
				QStringList() 
				<< "The kind must be one that has an associated DNA."
				<< "The energy for the actor is taken from the free"
				<< "energy of the world."
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
