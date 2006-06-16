/*
 * $Id: simplegraph.h,v 1.1 2006/06/16 02:45:38 cvs Exp $
 */

#ifndef _SIMPLE_GRAPH_H_

#include <qwidget.h>
#include <qrect.h>
#include <qpen.h>
#include <qpainter.h>


class SimpleGraph : public QWidget
{
	Q_OBJECT
public:
	SimpleGraph(QWidget* parent=0, const char* name=0);
	virtual void setPlotRange(double xx1, double yy1, double xx2, double yy2);
	virtual int pixX(double vx) {
		return axis.left() + int((vx - x1) * ppvx);
	}
	virtual int pixY(double vy) {
		return axis.bottom() - int((vy - y1) * ppvy);
	}
	virtual void drawAxis(QPainter &p);
	virtual void clearPlot(QPainter &p);
	virtual QRect getAxisRect() {
		return axis;
	}
public slots:
	void relayout(void);

signals:

private:
	QRect axis;		// Axis geometry
	double x1;
	double y1;
	double x2;
	double y2;
	double ppvx;	// Pixel Per Value (X axis)
	double ppvy;	// Pixel Per Value (Y axis)
	int margin_top;
	int margin_right;
	int margin_bottom;
	int margin_left;

	QPen pen_axis;	// Pen for Axis
	QPen pen_grid;	// Pen for gird
};

#define SIMPLE_GRAPH_DEFAULT_MARGIN 50

#define _SIMPLE_GRAPH_H_
#endif /* _SIMPLE_GRAPH_H_ */

