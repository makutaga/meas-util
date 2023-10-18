/*
 * Implementation of Draw Area Widget
 * $Id: drawarea.cpp,v 1.1 2006/06/16 02:45:38 cvs Exp $
 */


#include <QPainter>
#include <qstring.h>
#include <qpen.h>
#include <qcolor.h>
//Added by qt3to4:
#include <QPaintEvent>
#include <math.h>

#include "drawarea.h"

DrawArea::DrawArea(QWidget* parent)
	: SimpleGraph(parent)
{
	setPalette(QPalette(QColor(250,250,250)));

	dat_x = NULL;
	dat_y = NULL;

	plot_type = PLOT_INDEPENDENT;

	sd = 1;
	prefer_range = 5;
	changeNumber(1);

	fontsize_rho = 24;
	font_rho = QFont("Courier", fontsize_rho, QFont::Bold);

	pointsize = 4;
}

void
DrawArea::drawGraph(QPainter&p)
{
//	qWarning("Pass");
	QPen pen(Qt::red);
	QString rstr;
	QPointF pt;

//	relayout();
	clearPlot(p);
	drawAxis(p);
	pen.setWidth(pointsize);
	p.setPen(pen);
	for (int i=0; i < nsamples; i ++) {
		pt = QPointF(pixX(dat_x[i]), pixY(dat_y[i]));
		p.drawPoint(pt);
	}

	rstr.sprintf("rho = %8.5f", rho());
	p.setFont(font_rho);
	p.drawText(10, fontsize_rho, rstr);
}

void
DrawArea::generateData()
{
	if (dat_x != NULL) {
		delete [] dat_x;
	}
	dat_x = new double [nsamples];
	
	if (dat_y != NULL) {
		delete [] dat_y;
	}
	dat_y = new double [nsamples];
	
	if (plot_type == PLOT_POSITIVE) {
		double xx, yy;
		for (int i=0; i < nsamples; i ++) {
			xx = randn() * 1;
			yy = xx;
			dat_x[i] = xx + randn() * sd;
			dat_y[i] = yy + randn() * sd;
		}
		
	}
	else if (plot_type == PLOT_NEGATIVE) {
		double xx, yy;
		for (int i=0; i < nsamples; i ++) {
			xx = randn() * 1;
			yy = -xx;
			dat_x[i] = xx + randn() * sd;
			dat_y[i] = yy + randn() * sd;
		}

	}
	else if (plot_type == PLOT_ALT) {
		double xx, yy;
		for (int i=0; i < nsamples; i ++) {
			xx = randn() * 1;
			yy = 0.3 * xx * (xx-2) * (xx+1);
			dat_x[i] = xx + randn() * sd;
			dat_y[i] = yy + randn() * sd;
		}

	}
	else {
		for (int i=0; i < nsamples; i ++) {
			dat_x[i] = randn() * sd;
			dat_y[i] = randn() * sd;
		}
	}
}

void
DrawArea::changeNumber(int n)
{
	nsamples = n;
	generateData();
	repaint();
}

void
DrawArea::changeSD(double valsd)
{
	sd = valsd;
	generateData();
	repaint();
}

void
DrawArea::paintEvent(QPaintEvent *)
{
	QPainter p(this);
	p.setRenderHint(QPainter::Antialiasing);
	drawGraph(p);
}

void
DrawArea::resizeEvent(QResizeEvent*)
{
	QRect geom(0, 0, width(), height());
	relayout();
	QRect grect=getAxisRect();
	
	double xrange = 2.0 * double(grect.width()) / double(grect.width() + grect.height()) * prefer_range;
	double yrange = 2.0 * double(grect.height()) / double(grect.width() + grect.height()) * prefer_range;
	setPlotRange(-xrange, -yrange, xrange, yrange);
	
}

double
DrawArea::randn()
{	// By Box-muller transform
	double a=double(rand()) / RAND_MAX;
	double b=double(rand()) / RAND_MAX;

	double r1 = sqrt(-2.0 * log(a)) * sin(2 * M_PI * b);
//	double r2 = sqrt(-2.0 * log(a)) * cos(2 * M_PI * b);

	return r1;
}

double
DrawArea::rho()
{
	double ave_x = average(nsamples, dat_x);
	double ave_y = average(nsamples, dat_y);
	
	double a1=0, a2=0, a3=0;

	for (int i = 0; i < nsamples; i ++) {
		a1 += (dat_x[i] - ave_x) * (dat_y[i] - ave_y);
		a2 += (dat_x[i] - ave_x) * (dat_x[i] - ave_x);
		a3 += (dat_y[i] - ave_y) * (dat_y[i] - ave_y);
	}

	return a1 / (sqrt(a2) * sqrt(a3));
}

double
DrawArea::average(int n, double *dat)
{
	double sum=0.0;

	for (int i=0; i < n; i ++) {
		sum += dat[i];
	}
	return sum / n;
}

