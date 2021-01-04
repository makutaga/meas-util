/*
 $Id: control.h,v 1.1 2006/06/16 02:45:38 cvs Exp $
 */


#ifndef _CONTROL_H_
#define _CONTROL_H_
//#include <QtGui>
#include <QLineEdit>

class ControlPanel : public QWidget
{
	Q_OBJECT
public:
	ControlPanel(QWidget* parent=0);
signals:
	void replot();
	void setNumber(int);
	void setSD(double);
protected slots:
	void clickedNumber();
	void clickedSD();
private:
	QLineEdit* le_num;
	QLineEdit* le_sd;
};
#endif
