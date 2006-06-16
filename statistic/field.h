/*
 * $Id: field.h,v 1.1 2006/06/16 02:45:38 cvs Exp $
 */

#ifndef _FIELD_H_
#define _FIELD_H_
#include <QtGui>
#include "hist.h"

class Field : public QWidget
{
	Q_OBJECT
public:
	Field(QWidget* parent=0);
	
	void setHistProperty(double min, double max, int bins);
	void adjustHists();
public slots:
	void replot();
	void setNumber(int n);
	void setSD(double sd);
private:
	int nhists;
	Histgram *hist;
};

#endif
