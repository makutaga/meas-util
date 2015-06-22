/*
	$Id: simplegraph.cpp,v 1.1 2006/06/16 02:45:38 cvs Exp $
*/

#include <qbrush.h>
#include <qcolor.h>
#include "simplegraph.h"
#include <math.h>


SimpleGraph::SimpleGraph(QWidget* parent)
	: QWidget(parent)
{
	axis = parent->rect();

	margin_top = SIMPLE_GRAPH_DEFAULT_MARGIN;
	margin_right = SIMPLE_GRAPH_DEFAULT_MARGIN;
	margin_bottom = SIMPLE_GRAPH_DEFAULT_MARGIN;
	margin_left = SIMPLE_GRAPH_DEFAULT_MARGIN;

	axis.setTop(axis.top() + margin_top);
	axis.setRight(axis.right() - margin_right);
	axis.setBottom(axis.bottom() - margin_bottom);
	axis.setLeft(axis.left() + margin_left);

	setPlotRange(-1.0, -1.0, 1.0, 1.0);

	pen_axis.setWidth(2);
	pen_axis.setColor(QColor(0, 0, 0));

	pen_grid.setWidth(1);
	pen_grid.setColor(QColor(128, 128, 128));
}


void SimpleGraph::setPlotRange(double xx1, double yy1, double xx2, double yy2)
{
	x1 = xx1;
	y1 = yy1;
	x2 = xx2;
	y2 = yy2;

	ppvx = axis.width() / (x2 - x1);
	ppvy = axis.height() / (y2 - y1);
}

void SimpleGraph::drawAxis(QPainter &p)
{
	p.setPen(pen_grid);
	
	for (int ix = int(ceil(x1)); ix <= int(floor(x2)); ix ++) {
		p.drawLine(pixX(double(ix)), axis.top(), pixX(double(ix)), axis.bottom());
	}
	for (int iy = int(ceil(y1)); iy <= int(floor(y2)); iy ++) {
		p.drawLine(axis.left(), pixY(double(iy)), axis.right(), pixY(double(iy)));
	}

	// X axis
	if (axis.top() < pixY(0.0) && axis.bottom() > pixY(0.0)) {
		p.setPen(pen_axis);
		p.drawLine(axis.left(), pixY(0.0), axis.right(), pixY(0.0));
	}
	// Y axis
	if (axis.left() < pixX(0.0) && axis.right() > pixX(0.0)) {
		p.setPen(pen_axis);
		p.drawLine(pixX(0.0), axis.top(), pixX(0.0), axis.bottom());
	}


}

void SimpleGraph::relayout(void)
{
	axis.setTop(rect().top() + margin_top);
	axis.setRight(rect().right() - margin_right);
	axis.setBottom(rect().bottom() - margin_bottom);
	axis.setLeft(rect().left() + margin_left);
	
	setPlotRange(x1, y1, x2, y2);
}

void SimpleGraph::clearPlot(QPainter &p)
{
	QBrush br(QColor(255, 255, 255));

	p.fillRect(rect(), br);
	
}

