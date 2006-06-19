/*
 	Example of statistics
	average and variance
	$Id: main.cpp,v 1.1 2006/06/19 07:51:43 cvs Exp $
*/

#include <QApplication>
#include "appwidget.h"

int
main(int argc, char*argv[])
{
	QApplication app(argc, argv);
	AppWidget* aw = new AppWidget();

	aw->show();

	return app.exec();
}


