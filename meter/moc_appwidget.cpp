/****************************************************************************
** Meta object code from reading C++ file 'appwidget.h'
**
** Created: Mon Jun 19 16:27:37 2006
**      by: The Qt Meta Object Compiler version 59 (Qt 4.1.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "appwidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'appwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.1.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

static const uint qt_meta_data_AppWidget[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      10,   27,   29,   29, 0x09,
      30,   29,   29,   29, 0x09,
      38,   29,   29,   29, 0x09,
      45,   29,   29,   29, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_AppWidget[] = {
    "AppWidget\0valueChange(int)\0v\0\0start()\0stop()\0repaintMeter()\0"
};

const QMetaObject AppWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_AppWidget,
      qt_meta_data_AppWidget, 0 }
};

const QMetaObject *AppWidget::metaObject() const
{
    return &staticMetaObject;
}

void *AppWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_AppWidget))
	return static_cast<void*>(const_cast<AppWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int AppWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: valueChange((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: start(); break;
        case 2: stop(); break;
        case 3: repaintMeter(); break;
        }
        _id -= 4;
    }
    return _id;
}
