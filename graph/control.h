/*
	$Id: control.h,v 1.1 2006/06/16 02:45:38 cvs Exp $
*/

#ifndef _CONTROL_H_

#include <QWidget>
#include <QString>
#include <QLabel>
#include <math.h>

class Control : public QWidget
{
	Q_OBJECT
public:
	Control(QWidget* parent=0);

public slots:
	void change_SD(int n) {
		sd = double(n) / 100.0;
		QString l = QString::asprintf("%5.3f", sd);
		lbl_d->setText(l);
		emit changeSD(sd);
	}
	void change_num(int n) {
		num = int(pow(10, double(n) / 100));
		QString l = QString::asprintf("%5d", num);
		lbl->setText(l);
		emit changeNumber(num);
	}
signals:
	void runEvent(void);
	void posiEvent(void);
	void negaEvent(void);
	void indEvent(void);
	void altEvent(void);

	void changeNumber(int n);
	void changeSD(double val);

private:
	double sd;
	int num;
	QLabel* lbl;
	QLabel* lbl_d;
};

#define _CONTROL_H_
#endif /* _CONTROL_H_ */

