/* ========================================================================= */
/* ------------------------------------------------------------------------- */
/*!
  \file			aoutput.cc
  \date			Apr 2013
  \author		TNick
  
  \brief		Contains the implementation of AOutput class
  
  
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

#include	"aoutput.h"
#include	<QDebug>
#include	<QString>
#include	<QSettings>
#include	<iostream>

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

AOutput *		AOutput::uniq_ = NULL;

/*  DATA    ================================================================ */
//
//
//
//
/*  CLASS    --------------------------------------------------------------- */

/* ------------------------------------------------------------------------- */
bool				AOutput::init					( void )
{
	if ( uniq_ != NULL )
		return true;
	uniq_ = new AOutput();
	
	QSettings	stg;
	stg.beginGroup( "AOutput" );
	QString s_prompt = stg.value( "prompt_string", ">" ).toString();
	if ( s_prompt.isEmpty() )
	{
		s_prompt = ">";
	}
	uniq_->prompt_string = s_prompt.toStdString();
	
	stg.endGroup();
	return true;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void				AOutput::end					( void )
{
	if ( uniq_ == NULL )
		return;
		
	QSettings	stg;
	stg.beginGroup( "AOutput" );
	stg.setValue( "prompt_string", 
	QString::fromStdString( uniq_->prompt_string ) );
	stg.endGroup();
	
	delete uniq_;
	uniq_ = NULL;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void				AOutput::showInfo				( const QString & s_msg )
{
	qDebug() << s_msg.toLatin1().constBegin();
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void				AOutput::showWarning			( const QString & s_msg )
{
	qWarning() << s_msg.toLatin1().constBegin();
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void				AOutput::showError				( const QString & s_msg )
{
	qCritical() << s_msg.toLatin1().constBegin();
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void				AOutput::showInfo				( 
		const QString & s_title, const QString & s_msg )
{
	qDebug() << "[" << s_title.toLatin1().constBegin() << "]: "
			 << s_msg.toLatin1().constBegin();
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void				AOutput::showWarning			( 
		const QString & s_title, const QString & s_msg )
{
	qWarning() << "[" << s_title.toLatin1().constBegin() << "]: "
			   << s_msg.toLatin1().constBegin();
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void				AOutput::showError				( 
		const QString & s_title, const QString & s_msg )
{
	qCritical() << "[" << s_title.toLatin1().constBegin() << "]: "
				<< s_msg.toLatin1().constBegin();
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void				AOutput::showTable				(
		const QList<QStringList> & table, bool has_header, bool row_index )
{
	int i_row = 0;
	int i_row_max = table.count();
	int i_col_max = table.at( 0 ).count();
	if ( i_row_max == 0 )
		return;
	if ( i_col_max == 0 )
		return;
	
	QString s_res;
	
	/* initialise the table of column widths */
	QList<int>	cols;
	cols.reserve( i_col_max );
	for ( int i = 0; i < i_col_max; i++ )
	{
		cols.append( 0 );
	}
	
	/* compute column widths */
	for ( int i = 0; i < i_row_max; i++ )
	{
		const QStringList & sl = table.at( i );
		int col_cnt = sl.count();
		Q_ASSERT( col_cnt == i_col_max );
		for ( int j = 0; j < col_cnt; j++ )
		{
			const QString & s = sl.at( j );
			cols[j] = qMax( cols[j],s.length() );
		}
	}
	
	/* compute total lenght */
	int total_lenght = row_index ? 4 : 1; /* start with row number */
	for ( int i = 0; i < i_col_max; i++ )
	{
		total_lenght += cols.at( i ) + 1;
	}
	
	if ( has_header )
	{
		const QStringList & sl = table.at( 0 );
		int col_cnt = sl.count();
		if ( row_index )
			s_res.append( "    " );/* start with row number */
		else
			s_res.append( " " );
		for ( int j = 0; j < col_cnt; j++ )
		{
			const QString & s = sl.at( j );
			s_res.append( s );
			s_res.append( QString( (cols.at( j ) + 1) - s.length() , QChar(' ') ) );
		}
		s_res.append( "\n" );
		s_res.append( QString( total_lenght, QChar('-') ) );
		s_res.append( "\n" );

		i_row++;
	}
	
	int i_printed_row = 0;
	QString s_row;
	while ( i_row < i_row_max )
	{
		const QStringList & sl = table.at( i_row );
		
		int col_cnt = sl.count();
		
		/* start with row number */
		if ( row_index )
		{
			s_row = QString::number( i_printed_row );
			s_res.append( QString( 3 - s_row.length() , QChar(' ') ) );
			s_res.append( s_row );
		}
		s_res.append( QChar(' ') );
		
		for ( int j = 0; j < col_cnt; j++ )
		{
			const QString & s = sl.at( j );
			s_res.append( s );
			s_res.append( QString( (cols.at( j ) + 1) - s.length() , QChar(' ') ) );
		}
		s_res.append( "\n" );
		
		i_row++; i_printed_row++;
	}
	
	qDebug() << s_res.toLatin1().constBegin();
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void			AOutput::setPrompt			( const QString & s_new_prompt )
{
	if ( s_new_prompt.isEmpty() )
		return;
	uniq_->prompt_string = s_new_prompt.toStdString();
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void			AOutput::showPrompt		( void )
{
	std::cout << uniq_->prompt_string;
}
/* ========================================================================= */

/*  CLASS    =============================================================== */
//
//
//
//
/* ------------------------------------------------------------------------- */
/* ========================================================================= */

