/*
	$Id: control.cpp,v 1.1 2006/06/16 02:45:38 cvs Exp $
*/


#include "control.h"

#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>

ControlPanel::ControlPanel(QWidget* parent)
	:QWidget(parent)
{
	QHBoxLayout* bl = new QHBoxLayout(this);

	QPushButton* bt_replot = new QPushButton("Replot", this);
	
	QLabel*lbl_num = new QLabel("Number of samples");
	le_num = new QLineEdit(this);

	QLabel*lbl_sd = new QLabel("S.D.");
	
	le_sd = new QLineEdit(this);

	bl->addWidget(bt_replot);
	bl->addWidget(lbl_num);
	bl->addWidget(le_num, 1);
	bl->addWidget(lbl_sd);
	bl->addWidget(le_sd, 1);

	connect(bt_replot, SIGNAL(clicked()), this, SIGNAL(replot()));
	connect(le_num, SIGNAL(returnPressed()), this, SLOT(clickedNumber()));
	connect(le_sd, SIGNAL(returnPressed()), this, SLOT(clickedSD()));
}

void
ControlPanel::clickedNumber()
{
	QString str = le_num->text();
	int num = str.toInt();
	emit(setNumber(num));
}

void
ControlPanel::clickedSD()
{
	QString str = le_sd->text();
	double sd = str.toDouble();
	emit(setSD(sd));

}
