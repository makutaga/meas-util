/*
 * Random dot 
 * $Id: main.cpp,v 1.1 2006/06/16 02:45:38 cvs Exp $
 */

#include <qapplication.h>
#include <qlayout.h>
#include <qpushbutton.h>
#include <qfont.h>
#include <qslider.h>
//Added by qt3to4:
#include <QVBoxLayout>

#include "control.h"
#include "drawarea.h"

#define VBOX_MARGIN 5

class MyWidget : public QWidget
{
public:
	MyWidget(QWidget* parent=0, const char* name=0);

};

MyWidget::MyWidget(QWidget* parent, const char* name)
	: QWidget(parent, name)
{
	QVBoxLayout* topLayout = new QVBoxLayout(this);
	topLayout->setMargin(0);
	topLayout->setSpacing(0);
	setMinimumSize(640, 480);
	setMaximumSize(1280, 1000);

	// first row
	Control* cnt = new Control(this);
	topLayout->addWidget(cnt);

	// second row
	DrawArea* darea = new DrawArea(this, "drawarea");
	topLayout->addWidget(darea, 1);
	darea->changeNumber(100);
	darea->changeSD(0.5);

//	connect(cnt, SIGNAL(runEvent()), darea, SLOT(repaint()));
	connect(cnt, SIGNAL(changeNumber(int)), darea, SLOT(changeNumber(int)));
	connect(cnt, SIGNAL(changeSD(double)), darea, SLOT(changeSD(double)));

	connect(cnt, SIGNAL(posiEvent()), darea, SLOT(setPositive()));
	connect(cnt, SIGNAL(negaEvent()), darea, SLOT(setNegative()));
	connect(cnt, SIGNAL(indEvent()), darea, SLOT(setIndependent()));
	connect(cnt, SIGNAL(altEvent()), darea, SLOT(setAlt()));

}


int
main(int argc, char* argv[])
{
	QApplication a(argc, argv);

	MyWidget w;
	w.setGeometry(100, 100, 640, 480);
	w.setCaption("graph");
	a.setMainWidget(&w);
	w.show();
	return a.exec();


}

