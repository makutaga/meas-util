/*
 	$Id: appwidget.cpp,v 1.1 2006/06/19 07:51:42 cvs Exp $
 */

#include "appwidget.h"
#include "control.h"
#include "meterpanel.h"
#include <math.h>

AppWidget::AppWidget(QWidget* parent)
	:QWidget(parent)
{

	QVBoxLayout* bl = new QVBoxLayout(this);

	ControlPanel* cp = new ControlPanel(this);
	meter = new MeterPanel(this);

	bl->addWidget(cp);
	bl->addWidget(meter, 1);
	
	connect(cp, SIGNAL(valueChanged(int)),this, SLOT(valueChange(int)));
	connect(cp, SIGNAL(start()), this, SLOT(start()));
	connect(cp, SIGNAL(stop()), this, SLOT(stop()));
	resize(800,600);

	timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(repaintMeter()));
}

void
AppWidget::valueChange(int v)
{
	meter->setValue(double(v)/300.0);
}


void
AppWidget::start()
{
	start_time = QTime::currentTime();
	timer->start(5);
}

void
AppWidget::stop()
{
	timer->stop();
}

void
AppWidget::repaintMeter()
{
	QTime cur = QTime::currentTime();
	int msec = start_time.msecsTo(cur);
	double t = double(msec) / 1000.0;

	double v = (-cos(t * M_PI * 2.0 / 3.0) + 1.0) / 2.0;
	meter->setValue(v);
}
