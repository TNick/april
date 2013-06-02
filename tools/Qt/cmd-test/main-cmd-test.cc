
#include <iostream>
using namespace std;

#include <QString>
#include <QStringList>
#include <QTextStream>
#include <QRegExp>
#include <QDebug>
#include <QFile>
#include <QApplication>

#include	"cmdtest.h"

using namespace cmd_test;

/* ------------------------------------------------------------------------- */
//! application entry point
int			main			( int argc, char *argv[] )
{
	int i_ret = 1;
	
	QApplication app( argc, argv );
	
	for ( ;; )
	{
		if ( argc != 2 )
		{
			cerr << "Invalid number of arguments!";
			break;
		}
		QString the_file = argv[1];
		if ( ( the_file == "help" ) || ( the_file == "h" ) )
		{
			i_ret = 0;
			break;
		}
		CmdTest::init();
		
		i_ret = CmdTest::processFile( the_file ) ? 0 : 1;	
		
		CmdTest::end();
		
		return i_ret;
		
	}
	qDebug() << "\n\n" "Usage:" "\n" "\tcmd-test file" "\n\n";
	return i_ret;
	
}
/* ========================================================================= */
