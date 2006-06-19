/*
	$id$
*/


#include "control.h"

ControlPanel::ControlPanel(QWidget* parent)
	:QWidget(parent)
{
	QHBoxLayout* bl = new QHBoxLayout(this);

	QPushButton* bt_start = new QPushButton("Start", this);
	QPushButton* bt_stop = new QPushButton("Stop", this);
	QSlider* sld_value = new QSlider(Qt::Horizontal, this);
	sld_value->setMaximum(300);
//	QCheckBox* ck_lms = new QCheckBox("LMS", this);
//	QCheckBox* ck_lag = new QCheckBox("Lagrange Interpolation", this);
	
	bl->addWidget(bt_start);
	bl->addWidget(bt_stop);
	bl->addStretch();
	bl->addWidget(sld_value);
//	bl->addWidget(ck_lms);
//	bl->addWidget(ck_lag);
	
	connect(sld_value, SIGNAL(valueChanged(int)), this, SIGNAL(valueChanged(int)));
	connect(bt_start, SIGNAL(clicked()), this, SIGNAL(start()));
	connect(bt_stop, SIGNAL(clicked()), this, SIGNAL(stop()));
}

