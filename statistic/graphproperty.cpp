/*
	Imprementation of
	Generic Graph Property Class
	$Id: graphproperty.cpp,v 1.1 2006/06/16 02:45:38 cvs Exp $
*/

#include "graphproperty.h"
#define DEFAULT_DISPLAY_DPI 75
#define MM_PER_INCH 25.4

GraphProperty::GraphProperty()
{
	visible = true;
	clipping = false;
	display_dpmm = DEFAULT_DISPLAY_DPI / MM_PER_INCH;
	outer_rect.setRect(0, 0, 100, 100);
	setMargin(0, 0, 0, 0);
	QRect geom = QRect(0, 0, 100, 100);
	setGeometry(geom);
	setColor(Qt::black);
	setGraphRange(0.0, 0.0, 1.0, 1.0);
	setInputChannel(0);
}

