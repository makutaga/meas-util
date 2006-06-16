/*
 * $Id: hist.cpp,v 1.1 2006/06/16 02:45:38 cvs Exp $
 */

#include "hist.h"
#include <math.h>
#include <stdlib.h>

Histgram::Histgram(QWidget*parent)
	: QFrame(parent)
{
	data_num = 0;
	value = NULL;
	standard_d = 1.0;
	hist_count = NULL;
	
	setHistProperty(-5.0, 5.0, 21);
	setHistMax(20.0);
	setNumber(200);
	setSD(1.0);
	bbar = QBrush(QColor(255, 0, 0, 128));
}

Histgram::~Histgram()
{
	if (value != NULL) {
		delete [] value;
	}
	if (hist_count != NULL) {
		delete [] hist_count;
	}
}

void
Histgram::paintEvent(QPaintEvent*)
{
	QPainter p(this);
	p.setRenderHint(QPainter::Antialiasing);

	drawGraph(p);
	drawAxis(p);

}

void
Histgram::drawAxis(QPainter&p)
{
	p.setPen(Qt::black);
	QRect rect = gprop.getGraphRect();
	QLineF xaxis(
		double(rect.left()), gprop.y(0.0),
		double(rect.right()), gprop.y(0.0)	);
	QLineF yaxis(
		gprop.x(0.0), double(rect.top()),
		gprop.x(0.0), double(rect.bottom())	);

	p.drawLine(xaxis);
	p.drawLine(yaxis);
	
	QString save = QString("ave. = %1").arg(s_ave);
	QString ssd  = QString("sd.  = %1").arg(s_sd);
	QString smax  = QString("%1").arg(hist_max_freq);
	p.drawText(0, 12, save);
	p.drawText(0, 24, ssd);
	p.drawText(int(gprop.x(0.0)), 12, smax);
}

void
Histgram::drawGraph(QPainter&p)
{
	QRect wr = rect();

	p.setPen(Qt::red);
	double bin_width = (hist_max - hist_min) / hist_bins;
	QRectF box;
	for (int b = 0; b < hist_bins; b ++) {
		box.setLeft(gprop.x(b * bin_width + hist_min));
		box.setBottom(gprop.y(0.0));
		box.setRight(gprop.x((b+1) * bin_width + hist_min));
		box.setTop(gprop.y(double(hist_count[b])));
		
		p.fillRect(box, bbar);
		p.drawRect(box);
	}
}

void
Histgram::resizeEvent(QResizeEvent*)
{
	QRect geom(0, 0, width(), height());

	gprop.setGeometry(geom);
	gprop.setGraphRangeY(0.0, hist_max_freq);
	gprop.setGraphRangeX(hist_min, hist_max);
}

void
Histgram::regenerate()
{
	generateData();
	repaint();
}

void
Histgram::setNumber(int n)
{
	data_num = n;
	if (value != NULL) {
		delete [] value;
	}
	value = new double [data_num];
	
	generateData();
	repaint();
}

void
Histgram::setSD(double sd)
{
	standard_d = sd;
	generateData();
	repaint();
}

void
Histgram::generateData()
{
	double sum = 0.0;
	double sum2 = 0.0;
	for (int i=0; i < getNumber(); i ++) {
		value[i] = randn() * getSD();
		sum += value[i];
		sum2 += value[i] * value[i];
	}
	s_ave = sum / getNumber();
	s_sd = sqrt((sum2 - getNumber() * s_ave * s_ave) / (getNumber() - 1));
	
	calcHist();
}

double
Histgram::randn()
{	// By Box-muller transform
	double a=double(rand()) / RAND_MAX;
	double b=double(rand()) / RAND_MAX;

	double r1 = sqrt(-2.0 * log(a)) * sin(2 * M_PI * b);
//	double r2 = sqrt(-2.0 * log(a)) * cos(2 * M_PI * b);

	return r1;
}

void
Histgram::setHistProperty(double hmin, double hmax, int bs)
{
	hist_min = hmin;
	hist_max = hmax;
	hist_bins = bs;

	if (hist_count != NULL) {
		delete [] hist_count;
	}
	hist_count = new int [hist_bins];
	calcHist();
	
//	gprop.setGraphRangeY(0.0, getHistMax());
	gprop.setGraphRangeY(0.0, hist_max_freq);
	gprop.setGraphRangeX(hist_min, hist_max);
}

void
Histgram::calcHist()
{
	double bin_width = (hist_max - hist_min) / hist_bins;
	for (int b = 0; b < hist_bins; b ++) {
		hist_count[b] = 0;
	}

	int bin;
	for (int i = 0; i < getNumber(); i ++) {
		bin = int(floor((value[i] - hist_min) / bin_width));
		if (bin >= 0 && bin < hist_bins) {
			hist_count[bin] ++;
		}
	}
}

int
Histgram::getHistMax()
{
	int m = 0;
	for (int b = 0; b < hist_bins; b ++) {
		if (m < hist_count[b]) {
			m = hist_count[b];
		}
	}
	return m;
}

