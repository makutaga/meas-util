/*
	$Id: control.h,v 1.1 2006/06/16 02:45:38 cvs Exp $
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
	void clearPoints();
	void toggleLMS(bool);
	void toggleLagrange(bool);
protected slots:
	void clearPointsClicked();
private:
};
#endif
