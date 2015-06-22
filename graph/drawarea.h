/*
 * Draw Area
 * $Id: drawarea.h,v 1.1 2006/06/16 02:45:38 cvs Exp $
 */

#ifndef _DRAW_AREA_

#include <qwidget.h>
//Added by qt3to4:
#include <QPaintEvent>
#include "simplegraph.h"

typedef enum {
	PLOT_NEGATIVE, PLOT_POSITIVE, PLOT_INDEPENDENT, PLOT_ALT
} PlotType;

class DrawArea : public SimpleGraph
{
	Q_OBJECT
public:
	DrawArea(QWidget* parent=0);

public slots:
	void drawGraph(QPainter&p);
	void changeNumber(int n);
	void changeSD(double valsd);
	void generateData(void);
	void setNegative() {
		plot_type = PLOT_NEGATIVE;
		generateData();
		repaint();
	}
	void setPositive() {
		plot_type = PLOT_POSITIVE;
		generateData();
		repaint();
	}
	void setAlt() {
		plot_type = PLOT_ALT;
		generateData();
		repaint();
	}
	void setIndependent() {
		plot_type = PLOT_INDEPENDENT;
		generateData();
		repaint();
	}

protected:
	void paintEvent(QPaintEvent *);
	void resizeEvent(QResizeEvent*);

private:
	int nsamples;
	double sd;
	double *dat_x;
	double *dat_y;
	double prefer_range;
	double randn();
	PlotType plot_type;
	double rho();
	double average(int n, double *dat);
};

#define _DRAW_AREA_
#endif /* _DRAW_AREA_ */
