/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[16];
    char stringdata0[438];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 21), // "on_pushButton_clicked"
QT_MOC_LITERAL(2, 33, 0), // ""
QT_MOC_LITERAL(3, 34, 30), // "on_verticalSlider_valueChanged"
QT_MOC_LITERAL(4, 65, 5), // "value"
QT_MOC_LITERAL(5, 71, 32), // "on_verticalSlider_2_valueChanged"
QT_MOC_LITERAL(6, 104, 32), // "on_verticalSlider_3_valueChanged"
QT_MOC_LITERAL(7, 137, 31), // "on_verticalSlider_sliderPressed"
QT_MOC_LITERAL(8, 169, 33), // "on_verticalSlider_2_sliderPre..."
QT_MOC_LITERAL(9, 203, 33), // "on_verticalSlider_3_sliderPre..."
QT_MOC_LITERAL(10, 237, 32), // "on_verticalSlider_4_valueChanged"
QT_MOC_LITERAL(11, 270, 33), // "on_verticalSlider_4_sliderPre..."
QT_MOC_LITERAL(12, 304, 32), // "on_verticalSlider_6_valueChanged"
QT_MOC_LITERAL(13, 337, 33), // "on_verticalSlider_6_sliderPre..."
QT_MOC_LITERAL(14, 371, 32), // "on_verticalSlider_5_valueChanged"
QT_MOC_LITERAL(15, 404, 33) // "on_verticalSlider_5_sliderPre..."

    },
    "MainWindow\0on_pushButton_clicked\0\0"
    "on_verticalSlider_valueChanged\0value\0"
    "on_verticalSlider_2_valueChanged\0"
    "on_verticalSlider_3_valueChanged\0"
    "on_verticalSlider_sliderPressed\0"
    "on_verticalSlider_2_sliderPressed\0"
    "on_verticalSlider_3_sliderPressed\0"
    "on_verticalSlider_4_valueChanged\0"
    "on_verticalSlider_4_sliderPressed\0"
    "on_verticalSlider_6_valueChanged\0"
    "on_verticalSlider_6_sliderPressed\0"
    "on_verticalSlider_5_valueChanged\0"
    "on_verticalSlider_5_sliderPressed"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   79,    2, 0x08 /* Private */,
       3,    1,   80,    2, 0x08 /* Private */,
       5,    1,   83,    2, 0x08 /* Private */,
       6,    1,   86,    2, 0x08 /* Private */,
       7,    0,   89,    2, 0x08 /* Private */,
       8,    0,   90,    2, 0x08 /* Private */,
       9,    0,   91,    2, 0x08 /* Private */,
      10,    1,   92,    2, 0x08 /* Private */,
      11,    0,   95,    2, 0x08 /* Private */,
      12,    1,   96,    2, 0x08 /* Private */,
      13,    0,   99,    2, 0x08 /* Private */,
      14,    1,  100,    2, 0x08 /* Private */,
      15,    0,  103,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    4,
    QMetaType::Void, QMetaType::Int,    4,
    QMetaType::Void, QMetaType::Int,    4,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    4,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    4,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    4,
    QMetaType::Void,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_pushButton_clicked(); break;
        case 1: _t->on_verticalSlider_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->on_verticalSlider_2_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->on_verticalSlider_3_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->on_verticalSlider_sliderPressed(); break;
        case 5: _t->on_verticalSlider_2_sliderPressed(); break;
        case 6: _t->on_verticalSlider_3_sliderPressed(); break;
        case 7: _t->on_verticalSlider_4_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->on_verticalSlider_4_sliderPressed(); break;
        case 9: _t->on_verticalSlider_6_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: _t->on_verticalSlider_6_sliderPressed(); break;
        case 11: _t->on_verticalSlider_5_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 12: _t->on_verticalSlider_5_sliderPressed(); break;
        default: ;
        }
    }
}

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow.data,
      qt_meta_data_MainWindow,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 13;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
