/*
	$Id: control.h,v 1.1 2006/06/19 07:51:43 cvs Exp $
 */


#ifndef _CONTROL_H_
#define _CONTROL_H_
#include <QtGui>

class ControlPanel : public QWidget
{
	Q_OBJECT
public:
	ControlPanel(QWidget* parent=0);
signals:
	void valueChanged(int);
	void start();
	void stop();
protected slots:
private:
};
#endif
