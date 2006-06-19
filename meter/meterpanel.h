/*
 * $Id: meterpanel.h,v 1.1 2006/06/19 07:51:43 cvs Exp $
 */

#ifndef _METERPANEL_H_
#define _METERPANEL_H_
#include <QtGui>

class MeterPanel : public QFrame
{
	Q_OBJECT
public:
	MeterPanel(QWidget* parent=0);
	void setRange(double r);
	void setValue(double v);
protected:
	void paintEvent(QPaintEvent*ev);
	void resizeEvent(QResizeEvent*ev);
public slots:
private:
	QRectF panel_rect;
	double meter_range;
	double scale_range;
	double pointer_value;
	QPointF pointer_origin;
	
	void drawScale(QPainter&p);
	void drawPointer(QPainter&p);
	
};

#endif
