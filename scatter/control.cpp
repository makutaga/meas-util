/*
	$id$
*/


#include "control.h"

ControlPanel::ControlPanel(QWidget* parent)
	:QWidget(parent)
{
	QHBoxLayout* bl = new QHBoxLayout(this);

	QPushButton* bt_clear = new QPushButton("Clear", this);
	QCheckBox* ck_lms = new QCheckBox("LMS", this);
	QCheckBox* ck_lag = new QCheckBox("Lagrange Interpolation", this);
	
	bl->addWidget(bt_clear);
	bl->addStretch();
	bl->addWidget(ck_lms);
	bl->addWidget(ck_lag);
	
	connect(bt_clear, SIGNAL(clicked()), this, SLOT(clearPointsClicked()));
	connect(ck_lms, SIGNAL(toggled(bool)), this, SIGNAL(toggleLMS(bool)));
	connect(ck_lag, SIGNAL(toggled(bool)), this, SIGNAL(toggleLagrange(bool)));
}

void
ControlPanel::clearPointsClicked()
{
	emit(clearPoints());
}
