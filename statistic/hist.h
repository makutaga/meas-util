/*
 * $Id: hist.h,v 1.1 2006/06/16 02:45:38 cvs Exp $
 */

#ifndef _HIST_H_
#define _HIST_H_

//#include <QtGui>
#include "graphproperty.h"
#include <QFrame>

class Histgram : public QFrame
{
	Q_OBJECT
public:
	Histgram(QWidget* parent=0);
	~Histgram();
	void setNumber(int n);
	int getNumber() {
		return data_num;
	}
	void setSD(double sd);
	double getSD() {
		return standard_d;
	}
	double randn();
	void generateData();
	void setHistProperty(double hmin, double hmax, int bs);
	int getHistMax();
	void setHistMax(double max) {
		hist_max_freq = max;
		gprop.setGraphRangeY(0.0, hist_max_freq);
	}
	void regenerate();
protected:
	void paintEvent(QPaintEvent*);
	void resizeEvent(QResizeEvent*);
	
private:
	void drawGraph(QPainter&p);
	void drawAxis(QPainter&p);
	void calcHist();
	
	int data_num;
	double* value;
	double standard_d;
	GraphProperty gprop;
	
	double hist_min;
	double hist_max;
	double hist_max_freq;
	int hist_bins;
	int *hist_count;
	
	double s_ave;
	double s_sd;
	
	QBrush bbar;
};

#endif
