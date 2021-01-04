/*
 	$Id: appwidget.cpp,v 1.1 2006/06/16 02:45:38 cvs Exp $
 */

#include "appwidget.h"
#include "control.h"
#include "field.h"

#include <QVBoxLayout>

AppWidget::AppWidget(QWidget* parent)
	:QWidget(parent)
{

	QVBoxLayout* bl = new QVBoxLayout(this);

	ControlPanel* cp = new ControlPanel(this);
	Field* fld = new Field(this);

	bl->addWidget(cp);
	bl->addWidget(fld, 1);
	
	connect(cp, SIGNAL(clearPoints()), fld, SLOT(clearPoints()));
	connect(cp, SIGNAL(toggleLMS(bool)), fld, SLOT(toggleLMS(bool)));
	connect(cp, SIGNAL(toggleLagrange(bool)), fld, SLOT(toggleLagrange(bool)));
	resize(800,600);

}

