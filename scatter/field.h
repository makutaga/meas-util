/*
 * $Id: field.h,v 1.1 2006/06/16 02:45:38 cvs Exp $
 */

#ifndef _FIELD_H_
#define _FIELD_H_
//#include <QtGui>

#include <QWidget>

#include "graphproperty.h"

class Field : public QWidget
{
	Q_OBJECT
public:
	Field(QWidget* parent=0);
protected:
	void paintEvent(QPaintEvent*ev);
	void resizeEvent(QResizeEvent*ev);
	void mousePressEvent(QMouseEvent*ev);
public slots:
	void clearPoints();
	void toggleLMS(bool);
	void toggleLagrange(bool);
private:
	void drawAxis(QPainter&p);
	void drawPoints(QPainter&p);
	
	QList<QPointF> ptlist;
	GraphProperty gprop;
	double prefer_range;
	
	/* LMS stuff */
	bool enable_lms;
	double lms_a;
	double lms_b;
	void calcLMS();
	void drawLMS(QPainter&p);

	/* Lagrange Interpolation stuff */
	bool enable_lagrange;
	QPointF *pt_lag;
	void calcLagrange();
	void drawLagrange(QPainter&p);
	
	
};

#endif
