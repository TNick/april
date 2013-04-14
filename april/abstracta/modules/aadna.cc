/* ========================================================================= */
/* ------------------------------------------------------------------------- */
/*!
  \file			aadna.cc
  \date			Apr 2013
  \author		TNick
  
  \brief		Contains the implementation of AaDNA class
  
  
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

#include	"aadna.h"
#include	<april/abstracta/abstractapril.h>
#include	<april/abstracta/commandmap.h>
#include	<april/abstracta/aatokenizer.h>
#include	<april/abstracta/aaoutput.h>
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
AaDNA::AaDNA	( void )
	: AaModule()
{
	APRDBG_CDTOR;
	/* stub */
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
AaDNA::~AaDNA	( void )
{
	APRDBG_CDTOR;
	/* stub */
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void			AaDNA::insertCommands			( void )
{
	/// @cond internal
	
	//! register a command from this package 
#define addOneCmd(c)	\
	AbstractApril::addCommand( QObject::tr( "dna." stringify(c) ), AaDNA::c##DNA )
	
	addOneCmd(new);
	addOneCmd(list);
	
#undef addOneCmd
	//! @endcond
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void			AaDNA::removeCommands			( void )
{
	/// @cond internal
	
	//! unregister a command from this package @internal
#define remOneCmd(c)	\
	AbstractApril::remCommand( QObject::tr( "dna." stringify(c) ), AaDNA::c##DNA );
	
	remOneCmd(new);
	remOneCmd(list);
	
#undef remOneCmd
	//! @endcond
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
QString			AaDNA::name					( void )
{
	return QObject::tr( "DNA" );
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool			AaDNA::newDNA				(
		const QString & s_cmd, const AaTkString & atks, QString & s_err )
{
	Q_ASSERT( s_cmd == "dna.new" );
	Q_UNUSED( s_cmd );
	
	int arg_cnt = atks.tk_.count() - 1;
	QString arg1;
	DNA::InitData init_d;
	init_d.cost_ = InvalidId;
	init_d.cost_ = 10;
	init_d.age_ = 100;
	init_d.energy_ = 10;
	World * w = NULL;
	for ( ;; )
	{
		if ( arg_cnt > 0 )
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
				if ( arg_cnt > 2 )
				{
					if ( arg_cnt > 3 )
					{
						/** @todo  */
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
			if ( w->idValue( arg1 ) != InvalidId )
			{
				s_err.append( QObject::tr( 
								  "ID name %1 is already assigned.\n"
								  "Please choose a different one.\n\n"
								  ).arg( arg1 ) );
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
	s_err.append( QObject::tr( 
					  "Usage:\n"
					  "    dna.new [id] [cost] [age] [energy]    "
					  "creates a new kind\n"
					  "    dna.new help                          "
					  "prints usage instructions\n"
					  "\n"
					  "Options:\n"
					  "  id       the name to assign to the new numeric ID that\n"
					  "           will be generated. If ommited, a new, unique\n"
					  "           name will be generated.\n"
					  "           A form like this is recomended: Actor.Kind.<name>.\n"
					  "  cost     the intrinsec energy cost for the agent per time\n"
					  "           unit; other components that are added will\n"
					  "           increase the total cost for running the agent.n"
					  "           This value must be an integer larger than 0.\n"
					  "           By default the cost is set to 10.\n"
					  "  age      average age of death. This is an orientative\n"
					  "           value (suggestion). It must be larger than 0.\n"
					  "           By default it is set to 100.\n"
					  "  energy   energy required at birth. At least this ammount\n"
					  "           of energy units are assigned at birt to an agent\n"
					  "           of this kind. When the user creates the agent,\n"
					  "           the energy is substracted from the free energy\n"
					  "           of the world.\n"
					  "           By default it is set to 10.\n"
					  "\n"
					  ) );
	return false;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool			AaDNA::listDNA				(
		const QString & s_cmd, const AaTkString & atks, QString & s_err )
{
	Q_ASSERT( atks.tk_.count() >= 1 );
	Q_ASSERT( s_cmd == "dna.list" );
	
	
	int arg_cnt = atks.tk_.count() - 1;
	QString arg1;
	for ( ;; )
	{
		if ( arg_cnt == 0 )
		{
			World * w = AprilLibrary::crtWorld();
			if ( w == NULL )
			{
				errorNoCurrentWorld( s_err );
				return false;
			}
			GenericActorFactory * gf = GenericActorFactory::findMyself( w );
			Q_ASSERT( gf != NULL );
			
			
			GenericActorFactory::IdDnaMapIterC itr = gf->dnaList().constBegin();
			GenericActorFactory::IdDnaMapIterC itr_e = gf->dnaList().constEnd();
			if ( itr == itr_e )
			{
				s_err.append( QObject::tr( 
								  "No kinds registered in this world.\n"
								  ) );
				return false;
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
				AaOutput::showTable( datao, true, false );
				return true;
			}
		}
		else if ( arg_cnt == 1 )
		{
			arg1 = atks.getToken( 1 );
			if ( arg1 == QObject::tr( "help" ) )
				break;
			errorUnknownOprion( s_err, arg1 );
			break;
		}
		else
		{
			errorNumberOfArguments( s_err );
			break;
		}
	}
	/* print the usage */
	s_err.append( QObject::tr( 
					  "Usage:\n"
					  "    dna.list               "
					  "lists the available kinds in this world\n"
					  "    dna.list help          "
					  "prints usage instructions\n"
					  "\n"
					  ) );
	return false;
}
/* ========================================================================= */

/*  CLASS    =============================================================== */
//
//
//
//
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
