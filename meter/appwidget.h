/*
 $Id: appwidget.h,v 1.1 2006/06/19 07:51:42 cvs Exp $
 */

#ifndef _APPLICATION_H_

#include <QtGui>
#include "meterpanel.h"

class AppWidget : public QWidget
{
	Q_OBJECT
public:
	AppWidget(QWidget *parent=0);
protected slots:
	void valueChange(int v);
	void start();
	void stop();
	void repaintMeter();
private:
	MeterPanel* meter;
	QTime start_time;
	QTimer* timer;
};

#endif

