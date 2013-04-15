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





















//	Q_ASSERT( atks.tk_.count() >= 1 );
//	Q_ASSERT( s_cmd == "dna.list" );


//	int arg_cnt = atks.tk_.count() - 1;
//	QString arg1;
//	for ( ;; )
//	{
//		if ( arg_cnt == 0 )
//		{

//		}
//		else if ( arg_cnt == 1 )
//		{
//			arg1 = atks.getToken( 1 );
//			if ( arg1 == QObject::tr( "help" ) )
//				break;
//			errorUnknownOprion( s_err, arg1 );
//			break;
//		}
//		else
//		{
//			errorNumberOfArguments( s_err );
//			break;
//		}
//	}
//	/* print the usage */
//	s_err.append( QObject::tr( 
//					  "Usage:\n"
//					  "    dna.list               "
//					  "lists the available kinds in this world\n"
//					  "    dna.list help          "
//					  "prints usage instructions\n"
//					  "\n"
//					  ) );
//	return false;
//}
///* ========================================================================= */

/*  CLASS    =============================================================== */
//
//
//
//
/* ------------------------------------------------------------------------- */
/* ========================================================================= */
