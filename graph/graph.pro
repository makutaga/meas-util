# $Id: graph.pro,v 1.1 2006/06/16 02:45:38 cvs Exp $

TEMPLATE = app
INCLUDEPATH += .

# Input
HEADERS += control.h drawarea.h simplegraph.h
SOURCES += control.cpp drawarea.cpp main.cpp simplegraph.cpp
#The following line was inserted by qt3to4
#QT +=  qt3support 
QT += widgets
