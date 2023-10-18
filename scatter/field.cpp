/*
	$Id: field.cpp,v 1.1 2006/06/16 02:45:38 cvs Exp $
*/

#include <math.h>
#include "field.h"
#include <QPainter>
#include <QMouseEvent>

Field::Field(QWidget* parent)
	: QWidget(parent)
{
	prefer_range = 4.0;
	enable_lms = false;
	enable_lagrange = false;
	pt_lag = NULL;
}

void
Field::paintEvent(QPaintEvent*)
{
	QPainter p(this);
	p.setRenderHint(QPainter::Antialiasing);
	drawAxis(p);
	drawLMS(p);
	drawLagrange(p);
	drawPoints(p);
}

void
Field::resizeEvent(QResizeEvent*)
{
	QRect geom(0, 0, width(), height());
	gprop.setGeometry(geom);
	
	QRect grect = gprop.getGraphRect();
	double xrange = 2.0 * double(grect.width()) / double(grect.width() + grect.height()) * prefer_range;
	double yrange = 2.0 * double(grect.height()) / double(grect.width() + grect.height()) * prefer_range;
	gprop.setGraphRange(-xrange, -yrange, xrange, yrange);
}

void
Field::mousePressEvent(QMouseEvent* ev)
{
	double val_mx = gprop.rx(ev->x());
	double val_my = gprop.ry(ev->y());
	
	QPointF pt = QPointF(val_mx, val_my);
	ptlist << pt;
	calcLMS();
	calcLagrange();
	repaint();
}


void
Field::drawAxis(QPainter&p)
{
	p.setPen(QColor(128, 128, 128));
	QRect rect = gprop.getGraphRect();
	int xmin = int(ceil(gprop.getMinX()));
	int xmax = int(ceil(gprop.getMaxX()));
	int ymin = int(floor(gprop.getMinY()));
	int ymax = int(floor(gprop.getMaxY()));
	
	QLineF grid;
	for (int x = xmin; x <= xmax; x ++) {
		grid = QLineF(
			gprop.x(double(x)), double(rect.top()),
			gprop.x(double(x)), double(rect.bottom()));
		p.drawLine(grid);
	}
	for (int y = ymin; y <= ymax; y ++) {
		grid = QLineF(
			double(rect.left()), gprop.y(double(y)),
			double(rect.right()), gprop.y(double(y)));
		p.drawLine(grid);
	}
	
	p.setPen(Qt::black);
	QLineF xaxis(
		double(rect.left()), gprop.y(0.0),
		double(rect.right()), gprop.y(0.0)	);
	QLineF yaxis(
		gprop.x(0.0), double(rect.top()),
		gprop.x(0.0), double(rect.bottom())	);

	p.drawLine(xaxis);
	p.drawLine(yaxis);
}

void
Field::drawPoints(QPainter&p)
{
	
	QListIterator<QPointF> i(ptlist);

	QPen pen(Qt::red);
	pen.setWidth(7);
	p.setPen(pen);
	
	QPointF val_pt, pt;
	while (i.hasNext()) {
		val_pt = i.next();
		pt = QPointF(gprop.x(val_pt.x()), gprop.y(val_pt.y()));
		p.drawPoint(pt);
	}
}

void
Field::clearPoints()
{
	while (!ptlist.isEmpty()) {
		ptlist.removeFirst();
	}
	repaint();
}

/**** LMS (Least Mean Square) Section ******/
void
Field::toggleLMS(bool flag)
{
	enable_lms = flag;
	repaint();
}

void
Field::calcLMS()
{
	if (ptlist.count() < 2) {
		return;
	}
	double x_sum = 0.0;
	double y_sum = 0.0;
	double xy_sum = 0.0;
	double x2_sum = 0.0;
	
	QListIterator<QPointF> i(ptlist);
	QPointF val_pt;
	while (i.hasNext()) {
		val_pt = i.next();
		x_sum += val_pt.x();
		y_sum += val_pt.y();
		xy_sum += val_pt.x() * val_pt.y();
		x2_sum += val_pt.x() * val_pt.x();
	}
	int n = ptlist.count();
	double x_ave = x_sum / n;
	double y_ave = y_sum / n;
	lms_a = (xy_sum - n * x_ave * y_ave) / (x2_sum - n * x_ave * x_ave);
	lms_b = y_ave - lms_a * x_ave;
}

void
Field::drawLMS(QPainter &p)
{
	if (ptlist.count() < 2 || enable_lms == false) {
		return;
	}
	QPen pen(Qt::blue);
	pen.setWidth(3);
	p.setPen(pen);
	QLineF l(
		gprop.x(gprop.getMinX()), gprop.y(gprop.getMinX() * lms_a + lms_b),
		gprop.x(gprop.getMaxX()), gprop.y(gprop.getMaxX() * lms_a + lms_b));
	p.drawLine(l);
}



/**** Lagrange Interpolation Section ******/
void
Field::toggleLagrange(bool flag)
{
	enable_lagrange = flag;
	repaint();
}

void
Field::calcLagrange()
{
	if (ptlist.count() < 2) {
		return;
	}
}

void
Field::drawLagrange(QPainter&p)
{
	if (ptlist.count() < 2 || enable_lagrange == false) {
		return;
	}
	// QPen pen(Qt::green);
	QPen pen(QColor(92, 128, 0));
	pen.setWidth(3);
	p.setPen(pen);
	
	double x, y;
	double xmin = gprop.getMinX();
	double xmax = gprop.getMaxX();
	double xstep = 5 / gprop.getPixelPerValueX();
	int npts = int((xmax - xmin) / xstep);
	pt_lag = new QPointF [npts];
	int npts_val = ptlist.count();
	double sum_l = 0.0;
	double lk;
	
	for (int ix = 0; ix < npts; ix ++) {
		x = xmin + ix * xstep;
		sum_l = 0.0;
		for (int k = 0; k < npts_val; k ++) {
			lk = 1.0;
			for (int j = 0; j < npts_val; j ++) {
				if (j == k)	continue;
				lk = lk * (x - ptlist[j].x()) / (ptlist[k].x() - ptlist[j].x());
			}
			sum_l += lk * ptlist[k].y();
		}
		
		y = sum_l;
		
		pt_lag[ix] = QPointF(gprop.x(x), gprop.y(y));
	}
	p.drawPolyline(pt_lag, npts);
	
	delete [] pt_lag;
}

