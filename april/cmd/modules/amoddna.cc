/* ========================================================================= */
/* ------------------------------------------------------------------------- */
/*!
  \file			amoddna.cc
  \date			Apr 2013
  \author		TNick
  
  \brief		Contains the implementation of AModDNA class
  
  
*//*


 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 Please read COPYING and README files in root folder
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
//
//
//
//
/*  INCLUDES    ------------------------------------------------------------ */

#include	"amoddna.h"
#include	<april/cmd/commandmap.h>
#include	<april/cmd/apriltokenizer.h>
#include	<april/logic/aoutput.h>
#include	<april/logic/world.h>
#include	<april/logic/genericactorfactory.h>
#include	<april/plugins/aprilplugininterf.h>
#include	<april/aprillibrary.h>
#include	<QObject>
#include	<QStringList>

/*  INCLUDES    ============================================================ */
//
//
//
//
/*  DEFINITIONS    --------------------------------------------------------- */

using namespace april;

/*  DEFINITIONS    ========================================================= */
//
//
//
//
/*  DATA    ---------------------------------------------------------------- */

/*  DATA    ================================================================ */
//
//
//
//
/*  CLASS    --------------------------------------------------------------- */

/* ------------------------------------------------------------------------- */
AModDNA::AModDNA	( CommandMap * cmd_map )
	: AprilModule(cmd_map)
{
	APRDBG_CDTOR;
	/* stub */
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
AModDNA::~AModDNA	( void )
{
	APRDBG_CDTOR;
	/* stub */
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void			AModDNA::insertCommands			( CommandMap * cm )
{
	/// @cond internal
	
	//! register a command from this package 
#define addOneCmd(c)	\
	cm->addCommand( QObject::tr( "dna." stringify(c) ), AModDNA::c##DNA )
	
	addOneCmd(new);
	addOneCmd(list);
	addOneCmd(info);
	addOneCmd(s);
	addOneCmd(ak);
	addOneCmd(r);
	addOneCmd(b);
	
#undef addOneCmd
	//! @endcond
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void			AModDNA::removeCommands			( CommandMap * cm )
{
	/// @cond internal
	
	//! unregister a command from this package @internal
#define remOneCmd(c)	\
	cm->remCommand( QObject::tr( "dna." stringify(c) ), AModDNA::c##DNA );
	
	remOneCmd(new);
	remOneCmd(list);
	remOneCmd(info);
	remOneCmd(s);
	remOneCmd(ak);
	remOneCmd(r);
	remOneCmd(b);
	
	
#undef remOneCmd
	//! @endcond
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
QString			AModDNA::name					( void )
{
	return QObject::tr( "DNA" );
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool			AModDNA::newDNA				(
		const QString & s_cmd, const AaTkString & atks, QString & s_err )
{
	Q_ASSERT( s_cmd == "dna.new" );
	Q_UNUSED( s_cmd );
	
	int arg_cnt = atks.tk_.count() - 1;
	QString arg1;
	DNA::InitData init_d;
	init_d.kind_ = InvalidId;
	init_d.cost_ = 10;
	init_d.age_ = 100;
	init_d.energy_ = 10;
	World * w = NULL;
	for ( ;; )
	{
		if ( arg_cnt > 4 )
		{
			errorNumberOfArguments( s_err );
			break;
		}
		else if ( arg_cnt > 0 )
		{
			arg1 = atks.getToken( 1 );
			if ( arg1 == QObject::tr( "help" ) )
				break;
			
			w = AprilLibrary::crtWorld();
			if ( w == NULL )
			{
				errorNoCurrentWorld( s_err );
				return false;
			}
			
			if ( arg_cnt > 1 )
			{
				if ( !AprilModule::getUIntArg( 
						 atks, 2, s_err, &init_d.cost_ ) )
					break;
				if ( arg_cnt > 2 )
				{
					if ( !AprilModule::getUIntArg( 
							 atks, 3, s_err, &init_d.age_ ) )
						break;
					if ( arg_cnt > 3 )
					{
						if ( !AprilModule::getUIntArg( 
								 atks, 4, s_err, &init_d.energy_ ) )
							break;
					}
				}
			}
		}
		else
		{ /* no arguments were provided */
			w = AprilLibrary::crtWorld();
			if ( w == NULL )
			{
				errorNoCurrentWorld( s_err );
				return false;
			}
		}
		
		/* get an ID for this new kind */
		if ( arg1.isEmpty() == false )
		{
			ID other_id = w->idValue( arg1 );
			if ( other_id != InvalidId )
			{
				s_err.append( QObject::tr( 
								  "ID name %1 is already assigned to id %2.\n"
								  "Please choose a different one.\n\n"
								  ).arg( arg1 ).arg( other_id ) );
				return false;
			}
		}
		else
		{
			arg1 = w->createIdName( "Actor.Kind.%1" );
		}
		init_d.kind_ = w->addNewId( arg1 );
		
		GenericActorFactory * gf = GenericActorFactory::findMyself( w );
		Q_ASSERT( gf != NULL );
		gf->addNewKind( init_d );
		w->addActorFactory( gf, init_d.kind_ );
		DEC_REF(gf,gf);
		
		s_err.append( QObject::tr( 
						  "A new kind was created and assigned ID %1\n"
						  ).arg( init_d.kind_ ) );
		return false;
	}
	
	/* print the usage */
	s_err.append( getCLUsage( s_cmd ) );
	return false;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
static QString	do_dna_list					( void )
{
	QString s;
	World * w = AprilLibrary::crtWorld();
	if ( w == NULL )
	{
		AprilModule::errorNoCurrentWorld( s );
		return s;
	}
	GenericActorFactory * gf = GenericActorFactory::findMyself( w );
	Q_ASSERT( gf != NULL );
	
	GenericActorFactory::IdDnaMapIterC itr = gf->dnaList().constBegin();
	GenericActorFactory::IdDnaMapIterC itr_e = gf->dnaList().constEnd();
	if ( itr == itr_e )
	{
		return QObject::tr( 
					"No kinds registered in this world.\n"
					);
	}
	else
	{
		QList<QStringList>	datao;
		QStringList			sl;
		
		sl.append( QObject::tr( "ID" ) );
		sl.append( QObject::tr( "Name" ) );
		datao.append( sl ); sl.clear();
		while ( itr != itr_e )
		{
			sl.append( QString::number( itr.key() ) );
			sl.append( w->nameForId( itr.key() ) );
			datao.append( sl ); sl.clear();
			itr++;
		}
		AOutput::showTable( datao, true, false );
		return QString();
	}	
}
bool			AModDNA::listDNA				(
		const QString & s_cmd, const AaTkString & atks, QString & s_err )
{
	Q_ASSERT( s_cmd == "dna.list" );
	return funcArg0( s_cmd, atks, s_err, do_dna_list );
}
/* ========================================================================= */


/* ------------------------------------------------------------------------- */
static QString	do_dna_info					( 
		World * w, const QString & s_arg_1, const AaToken & tk1 )
{
	ID id;
	QString s;
	QString s_name;
	if ( tk1.isInteger() == false )
	{
		AprilModule::errorIdExpected( s, s_arg_1 );
		return s;
	}
	bool b;
	id = s_arg_1.toULongLong( &b );
	if ( ( b == false ) || ( id == InvalidId ) )
	{
		AprilModule::errorIdExpected( s, s_arg_1 );
		return s;
	}
	GenericActorFactory * gf = 
			GenericActorFactory::findMyself( w );
	Q_ASSERT( gf != NULL );
	const DNA & dna = gf->dna( id );
	if ( dna.isValid() == false )
	{
		s = QObject::tr( 
					"DNA with ID %1 does not exists.\n"
					).arg( id );
		DEC_REF(gf,gf);
		return s;
	}
	s.append( QObject::tr( "Information about DNA with ID %1:\n" ).arg( id ) );
	
	s.append( QString( 4, QChar( ' ' ) ) );
	s.append( QObject::tr( "name: " ) );
	s_name = w->nameForId( id );
	s.append( s_name.isEmpty() ? QObject::tr( "none" ) : s_name );
	s.append( QChar( '\n' ) );
	
	s.append( QString( 4, QChar( ' ' ) ) );
	s.append( QObject::tr( "id: " ) );
	s.append( QString::number( dna.kind() ) );
	s.append( QChar( '\n' ) );
	
	s.append( QString( 4, QChar( ' ' ) ) );
	s.append( QObject::tr( "cost: " ) );
	s.append( QString::number( dna.cost() ) );
	s.append( QChar( '\n' ) );
	
	s.append( QString( 4, QChar( ' ' ) ) );
	s.append( QObject::tr( "age: " ) );
	s.append( QString::number( dna.age() ) );
	s.append( QChar( '\n' ) );
	
	s.append( QString( 4, QChar( ' ' ) ) );
	s.append( QObject::tr( "energy: " ) );
	s.append( QString::number( dna.energy() ) );
	s.append( QChar( '\n' ) );
	
	QList<ID> brains = dna.brains();
	QList<ID> actuators = dna.actuators();
	QList<ID> sensors = dna.sensors();
	QList<ID> reflexes = dna.reflexes();
	QVector<DNA::Partition> partitions = dna.partitions();

	s.append( QString( 4, QChar( ' ' ) ) );
	s.append( QObject::tr( "sensors: " ) );
	if ( sensors.count() == 0 )
	{
		s.append( QObject::tr( "none\n" ) );
	}
	else
	{
		s.append( QChar( '\n' ) );
		foreach( ID iter, sensors ) {
			s.append( QString( 8, QChar( ' ' ) ) );
			s.append( QString::number( iter ) );
			s.append( QString( 2, QChar( ' ' ) ) );
			s.append( w->nameForId( iter ) );
			s.append( QChar( '\n' ) );
		}
	}

	s.append( QString( 4, QChar( ' ' ) ) );
	s.append( QObject::tr( "reflexes: " ) );
	if ( reflexes.count() == 0 )
	{
		s.append( QObject::tr( "none\n" ) );
	}
	else
	{
		s.append( QChar( '\n' ) );
		foreach( ID iter, reflexes ) {
			s.append( QString( 8, QChar( ' ' ) ) );
			s.append( QString::number( iter ) );
			s.append( QString( 2, QChar( ' ' ) ) );
			s.append( w->nameForId( iter ) );
			s.append( QChar( '\n' ) );
		}
	}
	
	s.append( QString( 4, QChar( ' ' ) ) );
	s.append( QObject::tr( "brains: " ) );
	if ( brains.count() == 0 )
	{
		s.append( QObject::tr( "none\n" ) );
	}
	else
	{
		s.append( QChar( '\n' ) );
		foreach( ID iter, brains ) {
			s.append( QString( 8, QChar( ' ' ) ) );
			s.append( QString::number( iter ) );
			s.append( QString( 2, QChar( ' ' ) ) );
			s.append( w->nameForId( iter ) );
			s.append( QChar( '\n' ) );
		}
	}
	
	s.append( QString( 4, QChar( ' ' ) ) );
	s.append( QObject::tr( "actuators: " ) );
	if ( actuators.count() == 0 )
	{
		s.append( QObject::tr( "none\n" ) );
	}
	else
	{
		s.append( QChar( '\n' ) );
		foreach( ID iter, actuators ) {
			s.append( QString( 8, QChar( ' ' ) ) );
			s.append( QString::number( iter ) );
			s.append( QString( 2, QChar( ' ' ) ) );
			s.append( w->nameForId( iter ) );
			s.append( QChar( '\n' ) );
		}
	}
	
	s.append( QString( 4, QChar( ' ' ) ) );
	s.append( QObject::tr( "partitions: " ) );
	if ( partitions.count() == 0 )
	{
		s.append( QObject::tr( "none\n" ) );
	}
	else
	{
		s.append( QChar( '\n' ) );
		foreach( DNA::Partition iter, partitions ) {
			s.append( QString( 8, QChar( ' ' ) ) );
			s.append( QObject::tr( "id: " ) );
			s.append( QString::number( iter.id_ ) );
			s.append( QObject::tr( "(%1), " ).arg( w->nameForId( iter.id_ ) ) );
			s.append( QObject::tr( "start: " ) );
			s.append( QString::number( iter.start_ ) );
			s.append( QObject::tr( ", count: " ) );
			s.append( QString::number( iter.count_ ) );
			s.append( QChar( '\n' ) );
		}
	}

	
	DEC_REF(gf,gf);
	return s;
}
bool			AModDNA::infoDNA			(
		const QString & s_cmd, const AaTkString & atks, QString & s_err )
{
	Q_ASSERT( s_cmd == "dna.info" );
	return funcArg1W( s_cmd, atks, s_err, do_dna_info );
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */

//! the type of actor component
enum do_dna_x_type	{
	do_dna_x_sensor,
	do_dna_x_actuator,
	do_dna_x_brain,
	do_dna_x_reflex
};

static QString	do_dna_x					( 
		do_dna_x_type ty, World * w, 
		const QString & s_arg_1, const AaToken & tk1,
		const QString & s_arg_2, const AaToken & tk2 )
{
	ID id1; ID id2;
	bool b;
	QString s;
	QString s_arg = s_arg_1;
	if ( tk1.isInteger() )
	{
		id1 = s_arg_1.toLongLong( &b );
		if ( b && id1 > 0 )
		{
			s_arg = s_arg_2;
			if ( tk2.isInteger() )
			{
				id2 = s_arg_2.toLongLong( &b );
				if ( b && id2 > 0 )
				{
					GenericActorFactory * gf = 
							GenericActorFactory::findMyself( w );
					Q_ASSERT( gf != NULL );
					for ( ;; ) {
						/* find the DNA to alter */
						DNA & dna_target = gf->dna( id1 );
						if ( dna_target.isValid() == false )
						{
							s = QObject::tr( 
										"DNA with ID %1 does not exists.\n"
										).arg( id1 );
							break;
						}
						if ( ty == do_dna_x_sensor )
						{
							SensorFactory * f = w->sensorFactory( id2 );
							if ( f == NULL )
							{
								s = QObject::tr( 
											"Sensor with ID %1 does not exists.\n"
											).arg( id2 );
								break;
							}
							dna_target.addSensor( id2 );
							s = QObject::tr(
										"Sensor type %1 added to kind %2" 
										).arg( id2 ).arg( id1 );
						}
						else if ( ty == do_dna_x_actuator )
						{
							ActuatorFactory * f = w->actuatorFactory( id2 );
							if ( f == NULL )
							{
								s = QObject::tr( 
											"Actuator with ID %1 does not exists.\n"
											).arg( id2 );
								break;
							}
							dna_target.addActuator( id2 );
							s = QObject::tr(
										"Actuator type %1 added to kind %2" 
										).arg( id2 ).arg( id1 );
						}
						else if ( ty == do_dna_x_brain )
						{
							BrainFactory * f = w->brainFactory( id2 );
							if ( f == NULL )
							{
								s = QObject::tr( 
											"Brain with ID %1 does not exists.\n"
											).arg( id2 );
								break;
							}
							dna_target.addBrain( id2 );
							s = QObject::tr(
										"Brain type %1 added to kind %2" 
										).arg( id2 ).arg( id1 );
						}
						else if ( ty == do_dna_x_reflex )
						{
							ReflexFactory * f = w->reflexFactory( id2 );
							if ( f == NULL )
							{
								s = QObject::tr( 
											"Reflex with ID %1 does not exists.\n"
											).arg( id2 );
								break;
							}
							dna_target.addReflex( id2 );
							s = QObject::tr(
										"Reflex type %1 added to kind %2" 
										).arg( id2 ).arg( id1 );
						}
						else
						{	
							Q_ASSERT( false );
						}
						break;
					}
					DEC_REF(gf,gf);
					return s;
				}
			}
		}
	}
	AprilModule::errorIntegerExpected( s, s_arg );
	return s;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
static QString	do_dna_s					( 
		World * w, const QString & s_arg_1, const AaToken & tk1,
		const QString & s_arg_2, const AaToken & tk2 )
{
	return do_dna_x( do_dna_x_sensor, w, s_arg_1, tk1, s_arg_2, tk2 );
}
bool			AModDNA::sDNA				(
		const QString & s_cmd, const AaTkString & atks, QString & s_err )
{
	Q_ASSERT( s_cmd == "dna.s" );
	return funcArg_W2( s_cmd, atks, s_err, do_dna_s );
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
static QString	do_dna_ak					( 
		World * w, const QString & s_arg_1, const AaToken & tk1,
		const QString & s_arg_2, const AaToken & tk2 )
{
	return do_dna_x( do_dna_x_actuator, w, s_arg_1, tk1, s_arg_2, tk2 );
}
bool			AModDNA::akDNA			(
		const QString & s_cmd, const AaTkString & atks, QString & s_err )
{
	Q_ASSERT( s_cmd == "dna.ak" );
	return funcArg_W2( s_cmd, atks, s_err, do_dna_ak );
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
static QString	do_dna_b					( 
		World * w, const QString & s_arg_1, const AaToken & tk1,
		const QString & s_arg_2, const AaToken & tk2 )
{
	return do_dna_x( do_dna_x_brain, w, s_arg_1, tk1, s_arg_2, tk2 );
}
bool			AModDNA::bDNA				(
		const QString & s_cmd, const AaTkString & atks, QString & s_err )
{
	Q_ASSERT( s_cmd == "dna.b" );
	return funcArg_W2( s_cmd, atks, s_err, do_dna_b );
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
static QString	do_dna_r					( 
		World * w, const QString & s_arg_1, const AaToken & tk1,
		const QString & s_arg_2, const AaToken & tk2 )
{
	return do_dna_x( do_dna_x_reflex, w, s_arg_1, tk1, s_arg_2, tk2 );
}
bool			AModDNA::rDNA				(
		const QString & s_cmd, const AaTkString & atks, QString & s_err )
{
	Q_ASSERT( s_cmd == "dna.r" );
	return funcArg_W2( s_cmd, atks, s_err, do_dna_r );
}
/* ========================================================================= */





/*  CLASS    =============================================================== */
//
//
//
//
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
