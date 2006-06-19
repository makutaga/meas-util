/*
	$Id: meterpanel.cpp,v 1.1 2006/06/19 07:51:43 cvs Exp $
*/

#include <math.h>
#include "meterpanel.h"

MeterPanel::MeterPanel(QWidget* parent)
	: QFrame(parent)
{
	meter_range = 1.0;
	pointer_value = 0.0;
	scale_range = 90.0;

}

void
MeterPanel::paintEvent(QPaintEvent*)
{
	QPainter p(this);
	p.setRenderHint(QPainter::Antialiasing);

	p.fillRect(panel_rect, Qt::white);
	drawScale(p);
	drawPointer(p);
	
}

void
MeterPanel::resizeEvent(QResizeEvent*)
{
	QRect geom(0, 0, width(), height());
	double geom_ratio = double(width()) / double(height());
	double prefer_ratio = (0.1 + 2.0 + 0.1) / (0.1 + 1.0 + 0.3);
//qDebug("resizeEvent: %f %f", geom_ratio, prefer_ratio);
	double base_length;
	if (geom_ratio > prefer_ratio) {
		base_length = double(height()) / (0.1 + 1.0 + 0.3);
	}
	else {
		base_length = double(width()) / (0.1 + 2.0 + 0.1);
	}

	panel_rect = QRectF(0, 0, base_length * 2.0, base_length);
//qDebug("resizeEvent: %f  %f %f", base_length, panel_rect.width(), panel_rect.height());

	panel_rect.moveTo(
			(width() - panel_rect.width()) / 2.0,
			base_length * 0.1);
	pointer_origin = QPointF(
		panel_rect.x() + panel_rect.width() / 2,
		(panel_rect.y() + panel_rect.height()) * 1.5);

}

void
MeterPanel::drawScale(QPainter&p)
{
	double angle_begin = -scale_range / 2;
	int major_nsteps = 10;
	int minor_nsteps = 100;
	double major_step = scale_range / double(major_nsteps);
	double minor_step = scale_range / double(minor_nsteps);
	
	QPointF p1 = QPointF(0, - panel_rect.height() * 1.2);
	QPointF p2 = QPointF(0, - panel_rect.height() * 1.25);
	QPointF p3 = QPointF(0, - panel_rect.height() * 1.3);
	QPointF p4 = QPointF(0, - panel_rect.height() * 1.32);
	
	p.translate(pointer_origin);
	p.rotate(angle_begin);
	for (int j = 0; j <= minor_nsteps; j ++) {
		p.drawLine(p1, p2);
		p.rotate(minor_step);
	}

	p.resetMatrix();
	p.translate(pointer_origin);
	p.rotate(angle_begin);
	for (int i = 0; i <= major_nsteps; i ++) {
		p.drawLine(p1, p3);
		QString str = QString("%1").arg(double(i) / major_nsteps * meter_range);
		p.drawText(p4, str);
		p.rotate(major_step);
	}
	p.resetMatrix();
}

void
MeterPanel::drawPointer(QPainter&p)
{
	p.setClipRect(panel_rect);

	double a = pointer_value / meter_range * scale_range;
	p.translate(pointer_origin);
	p.rotate(-scale_range / 2 + a);
	QPointF p1 = QPointF(0, - panel_rect.height() * 1.4);
	p.drawLine(QPointF(0.0, 0.0), p1);
}

void
MeterPanel::setRange(double r)
{
	meter_range = r;
	repaint();
}

void
MeterPanel::setValue(double v)
{
	pointer_value = v;
	repaint();
}
