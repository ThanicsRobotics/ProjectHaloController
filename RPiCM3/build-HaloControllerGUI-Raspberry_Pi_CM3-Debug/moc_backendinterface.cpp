/****************************************************************************
** Meta object code from reading C++ file 'backendinterface.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.10.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../HaloControllerGUI/backendinterface.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'backendinterface.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.10.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_BackendInterface_t {
    QByteArrayData data[9];
    char stringdata0[82];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_BackendInterface_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_BackendInterface_t qt_meta_stringdata_BackendInterface = {
    {
QT_MOC_LITERAL(0, 0, 16), // "BackendInterface"
QT_MOC_LITERAL(1, 17, 7), // "cleanup"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 6), // "Stream"
QT_MOC_LITERAL(4, 33, 6), // "stream"
QT_MOC_LITERAL(5, 40, 18), // "operateLandingGear"
QT_MOC_LITERAL(6, 59, 9), // "direction"
QT_MOC_LITERAL(7, 69, 7), // "takeoff"
QT_MOC_LITERAL(8, 77, 4) // "land"

    },
    "BackendInterface\0cleanup\0\0Stream\0"
    "stream\0operateLandingGear\0direction\0"
    "takeoff\0land"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_BackendInterface[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   34,    2, 0x0a /* Public */,

 // methods: name, argc, parameters, tag, flags
       5,    1,   37,    2, 0x02 /* Public */,
       7,    0,   40,    2, 0x02 /* Public */,
       8,    0,   41,    2, 0x02 /* Public */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,

 // methods: parameters
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void BackendInterface::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        BackendInterface *_t = static_cast<BackendInterface *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->cleanup((*reinterpret_cast< Stream(*)>(_a[1]))); break;
        case 1: _t->operateLandingGear((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->takeoff(); break;
        case 3: _t->land(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject BackendInterface::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_BackendInterface.data,
      qt_meta_data_BackendInterface,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *BackendInterface::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *BackendInterface::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_BackendInterface.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int BackendInterface::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
