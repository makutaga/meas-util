/*
	$Id: control.cpp,v 1.1 2006/06/16 02:45:38 cvs Exp $
*/

#include <QApplication>
#include <QPushButton>
#include <QSlider>
#include <QLabel>
#include <QHBoxLayout>
#include "control.h"

//#include <qapplication.h>
//#include <qpushbutton.h>
//#include <qslider.h>
//#include <qlabel.h>
//#include <QHBoxLayout>
//#include "control.h"

Control::Control(QWidget* parent)
{
	// Buttons
//	QPushButton* quit = new QPushButton("&Quit", this);
//	connect(quit, SIGNAL(clicked()), qApp, SLOT(quit()));

//	QPushButton* run = new QPushButton("Plot", this);
//	connect(run, SIGNAL(clicked()), this, SIGNAL(runEvent()));

	QPushButton* posi = new QPushButton("Positive", this);
	connect(posi, SIGNAL(clicked()), this, SIGNAL(posiEvent()));

	QPushButton* nega = new QPushButton("Negative", this);
	connect(nega, SIGNAL(clicked()), this, SIGNAL(negaEvent()));

	QPushButton* ind = new QPushButton("Ind.", this);
	connect(ind, SIGNAL(clicked()), this, SIGNAL(indEvent()));

	QPushButton* alt = new QPushButton("Alt.", this);
	connect(alt, SIGNAL(clicked()), this, SIGNAL(altEvent()));

	// Sliders
	QSlider* slider = new QSlider(Qt::Horizontal, this);
	slider->setRange(10, 400);
	lbl = new QLabel("00", this);

	connect(slider, SIGNAL(valueChanged(int)), this, SLOT(change_num(int)));
//	connect(slider, SIGNAL(valueChanged(int)), lbl, SLOT(setNum(int)));

	QSlider* slider_d = new QSlider(Qt::Horizontal, this);
	slider_d->setRange(0, 300);

	lbl_d = new QLabel("00", this);
	connect(slider_d, SIGNAL(valueChanged(int)), this, SLOT(change_SD(int)));

	change_SD(0);

	QHBoxLayout* l = new QHBoxLayout(this);
	l->setSpacing(0);
	// l->setMargin(0);
	l->setContentsMargins(0, 0, 0, 0);
//	l->addWidget(quit);
//	l->addWidget(run);
	l->addWidget(posi);
	l->addWidget(nega);
	l->addWidget(ind);
	l->addWidget(alt);
	l->addWidget(slider, 1);
	l->addWidget(lbl);
	l->addWidget(slider_d, 1);
	l->addWidget(lbl_d);
}

