/*
	$Id: field.cpp,v 1.1 2006/06/16 02:45:38 cvs Exp $
*/


#include "field.h"
#include "hist.h"

Field::Field(QWidget* parent)
	: QWidget(parent)
{
	int nrows = 3;
	int ncols = 3;
	nhists = nrows * ncols;
	nhists = 9;
	hist = new Histgram[nhists];

	QGridLayout* gl = new QGridLayout;
	for (int r = 0; r < nrows; r ++) {
		for (int c = 0; c < ncols; c ++) {
			gl->addWidget(&hist[r * ncols + c], r, c);
		}
	}

	setLayout(gl);
	setNumber(100);
	setSD(1.0);
}


void
Field::setHistProperty(double min, double max, int bins)
{
	for (int h = 0; h < nhists; h ++) {
		hist[h].setHistProperty(min, max, bins);
	}
}

void
Field::setNumber(int n)
{
	for (int h = 0; h < nhists; h ++) {
		hist[h].setNumber(n);
	}
	adjustHists();
}
void
Field::setSD(double sd)
{
	for (int h = 0; h < nhists; h ++) {
		hist[h].setSD(sd);
	}
	adjustHists();
}


void
Field::adjustHists()
{
	int hmax = 0;
	
	for (int h = 0; h < nhists; h ++) {
		int hm = hist[h].getHistMax();
		if (hm > hmax) {
			hmax = hm;
		}
	}
	for (int h = 0; h < nhists; h ++) {
		hist[h].setHistMax(double(hmax)+1);
	}
}

void
Field::replot()
{
	for (int h = 0; h < nhists; h ++) {
		hist[h].regenerate();
	}
	adjustHists();
}

