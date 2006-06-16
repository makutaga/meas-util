/*
 $Id: appwidget.cpp,v 1.1 2006/06/16 02:45:38 cvs Exp $
 */

#include "appwidget.h"
#include "control.h"
#include "field.h"

AppWidget::AppWidget(QWidget* parent)
	:QWidget(parent)
{

	QVBoxLayout* bl = new QVBoxLayout(this);

	ControlPanel* cp = new ControlPanel(this);
	Field* fld = new Field(this);

	bl->addWidget(cp);
	bl->addWidget(fld, 1);
	
	connect(cp, SIGNAL(replot()), fld, SLOT(replot()));
	connect(cp, SIGNAL(setNumber(int)), fld, SLOT(setNumber(int)));
	connect(cp, SIGNAL(setSD(double)), fld, SLOT(setSD(double)));
	resize(800,600);

}

