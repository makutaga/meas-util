/*
	Generic Graph Property Class
	$Id: graphproperty.h,v 1.1 2006/06/16 02:45:38 cvs Exp $
*/

#ifndef _GRAPHPROPERTY_H_
#define _GRAPHPROPERTY_H_

#include <QtCore>
#include <QColor>

class GraphProperty {
public:
	GraphProperty();
	~GraphProperty()	{};
	void setVisible(bool f)	{
		visible = f;
	}
	bool getVisible() {
		return visible;
	}
	void setLabel(QString &str) {
		label = str;
	}
	QString &getLabel() {
		return label;
	}
	void setClippingFlag(bool f) {
		clipping = f;
	}
	bool getClippingFlag() {
		return clipping;
	}
	void setGeometry(QRect& rect) {
		outer_rect = rect;
		graph_rect.setRect(
			outer_rect.x() + margin_left, 
			outer_rect.y() + margin_top,
			outer_rect.width() - margin_left - margin_right,
			outer_rect.height() - margin_top - margin_bottom);
//qDebug("setGeometry: %d", graph_rect.height());
	}
	void setMargin(int t, int r, int b, int l) {
		margin_top = t;
		margin_right = r;
		margin_bottom = b;
		margin_left = l;
		graph_rect.setRect(
			outer_rect.x() + margin_left, 
			outer_rect.y() + margin_top,
			outer_rect.width() - margin_left - margin_right,
			outer_rect.height() - margin_top - margin_bottom);
	}
	double x(double val) {		// Get window coordinate
		return graph_rect.left() + (val - ax.offset) * ax.ppv;
	}
	double rx(double pix) {		// reverse X (obtain value from window coordinate)
		return (pix - graph_rect.left()) / ax.ppv + ax.offset;
	}
	double y(double val) {		// Get window coordinate
//qDebug("GraphProperty::y offset:%f ppv:%f", ay.offset, ay.ppv);
		return graph_rect.bottom() - (val - ay.offset) * ay.ppv;
	}
	double ry(double pix) {
		return (graph_rect.bottom() - pix) / ay.ppv + ay.offset;
	}
	void setPixelPerValue(double vx, double vy) {
		ax.ppv = vx;
		ay.ppv = vy;
	}
	void setPixelPerValueX(double vx) {
		ax.ppv = vx;
	}
	void setPixelPerValueY(double vy) {
		ay.ppv = vy;
	}
	double getPixelPerValueX() {
		return ax.ppv;
	}
	double getPixelPerValueY() {
		return ay.ppv;
	}
	void setGraphRange(double xmin, double ymin, double xmax, double ymax) {
		setGraphRangeX(xmin, xmax);
		setGraphRangeY(ymin, ymax);
	}
	void setGraphRangeX(double min, double max) {
		ax.offset = min;
		ax.ppv = double(graph_rect.width()) / (max - min);
	}
	void setGraphRangeY(double min, double max) {
		ay.offset = min;
		ay.ppv = double(graph_rect.height()) / (max - min);
//qDebug("GraphProperty::setGraphRangeY h:%d min:%f max:%f ppv:%f", graph_rect.height(), min, max, ay.ppv);
	}
	double getMinX() {
		return ax.offset;
	}
	double getMaxX() {
		return ax.offset + graph_rect.width() / ax.ppv;
	}
	double getMinY() {
		return ay.offset;
	}
	double getMaxY() {
		return ay.offset + graph_rect.height() / ay.ppv;
	}
	
	void setColor(QColor col) {
		line_color = col;
	}
	QColor getColor() {
		return line_color;
	}
	QRect getGraphRect() {
		return graph_rect;
	}
	QRect getFrameRect() {
		return outer_rect;
	}
	void setInputChannel(int ch) {
		input_channel = ch;
	}
	int getInputChannel() {
		return input_channel;
	}
private:
	class AxisProp {
	public:
		AxisProp() {
			ppv = 1.0;
			log = false;
			offset = 0.0;
		}
		double ppv;		// pixels per value
		bool log;		// log scale flag
		QString unit;	// unit description
		double offset;	// offset value
	private:
	};
	bool visible;		// visible flag
	QString label;		// label of this graph
	bool clipping;		// clipping flag
	AxisProp ax;
	AxisProp ay;
	double display_dpmm;
	QColor line_color;
	QRect outer_rect;
	QRect graph_rect;
	int margin_top;
	int margin_right;
	int margin_bottom;
	int margin_left;
	int input_channel;
};

#endif
