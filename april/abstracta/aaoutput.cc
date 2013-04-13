/* ========================================================================= */
/* ------------------------------------------------------------------------- */
/*!
  \file			aaoutput.cc
  \date			Apr 2013
  \author		TNick
  
  \brief		Contains the implementation of AaOutput class
  
  
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

#include	"aaoutput.h"
#include	<QDebug>
#include	<QString>

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
void				AaOutput::showInfo				( const QString & s_msg )
{
	qDebug() << s_msg.toLatin1().constBegin();
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void				AaOutput::showWarning			( const QString & s_msg )
{
	qWarning() << s_msg.toLatin1().constBegin();
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void				AaOutput::showError				( const QString & s_msg )
{
	qCritical() << s_msg.toLatin1().constBegin();
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void				AaOutput::showInfo				( 
		const QString & s_title, const QString & s_msg )
{
	qDebug() << "[" << s_title.toLatin1().constBegin() << "]: "
			 << s_msg.toLatin1().constBegin();
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void				AaOutput::showWarning			( 
		const QString & s_title, const QString & s_msg )
{
	qWarning() << "[" << s_title.toLatin1().constBegin() << "]: "
			   << s_msg.toLatin1().constBegin();
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void				AaOutput::showError				( 
		const QString & s_title, const QString & s_msg )
{
	qCritical() << "[" << s_title.toLatin1().constBegin() << "]: "
				<< s_msg.toLatin1().constBegin();
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void				AaOutput::showTable				(
		const QList<QStringList> & table, bool has_header )
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
	int total_lenght = 1; /* start with a single space */
	for ( int i = 0; i < i_col_max; i++ )
	{
		total_lenght += cols.at( i ) + 1;
	}
	
	if ( has_header )
	{
		const QStringList & sl = table.at( 0 );
		int col_cnt = sl.count();
		s_res.append( " " );/* start with a single space */
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
	
	while ( i_row < i_row_max )
	{
		const QStringList & sl = table.at( i_row );
		
		int col_cnt = sl.count();
		s_res.append( " " );/* start with a single space */
		for ( int j = 0; j < col_cnt; j++ )
		{
			const QString & s = sl.at( j );
			s_res.append( s );
			s_res.append( QString( (cols.at( j ) + 1) - s.length() , QChar(' ') ) );
		}
		s_res.append( "\n" );
		
		i_row++;
	}
	
	qDebug() << s_res.toLatin1().constBegin();
}
/* ========================================================================= */

/*  CLASS    =============================================================== */
//
//
//
//
/* ------------------------------------------------------------------------- */
/* ========================================================================= */


