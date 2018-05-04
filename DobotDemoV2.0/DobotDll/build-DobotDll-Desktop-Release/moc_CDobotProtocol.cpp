/****************************************************************************
** Meta object code from reading C++ file 'CDobotProtocol.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../SourceCode/src/CDobotProtocol.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'CDobotProtocol.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_CDobotProtocol_t {
    QByteArrayData data[17];
    char stringdata0[178];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CDobotProtocol_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CDobotProtocol_t qt_meta_stringdata_CDobotProtocol = {
    {
QT_MOC_LITERAL(0, 0, 14), // "CDobotProtocol"
QT_MOC_LITERAL(1, 15, 12), // "bytesToWrite"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 11), // "const char*"
QT_MOC_LITERAL(4, 41, 4), // "data"
QT_MOC_LITERAL(5, 46, 7), // "maxSize"
QT_MOC_LITERAL(6, 54, 12), // "messageReady"
QT_MOC_LITERAL(7, 67, 7), // "Message"
QT_MOC_LITERAL(8, 75, 7), // "message"
QT_MOC_LITERAL(9, 83, 18), // "onNewConnectStatus"
QT_MOC_LITERAL(10, 102, 9), // "connected"
QT_MOC_LITERAL(11, 112, 14), // "onBytesWritten"
QT_MOC_LITERAL(12, 127, 12), // "onBytesReady"
QT_MOC_LITERAL(13, 140, 5), // "array"
QT_MOC_LITERAL(14, 146, 11), // "sendMessage"
QT_MOC_LITERAL(15, 158, 12), // "periodicTask"
QT_MOC_LITERAL(16, 171, 6) // "onInit"

    },
    "CDobotProtocol\0bytesToWrite\0\0const char*\0"
    "data\0maxSize\0messageReady\0Message\0"
    "message\0onNewConnectStatus\0connected\0"
    "onBytesWritten\0onBytesReady\0array\0"
    "sendMessage\0periodicTask\0onInit"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CDobotProtocol[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   54,    2, 0x06 /* Public */,
       6,    1,   59,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       9,    1,   62,    2, 0x0a /* Public */,
      11,    0,   65,    2, 0x0a /* Public */,
      12,    1,   66,    2, 0x0a /* Public */,
      14,    1,   69,    2, 0x0a /* Public */,
      15,    0,   72,    2, 0x08 /* Private */,

 // methods: name, argc, parameters, tag, flags
      16,    0,   73,    2, 0x02 /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, QMetaType::LongLong,    4,    5,
    QMetaType::Void, 0x80000000 | 7,    8,

 // slots: parameters
    QMetaType::Void, QMetaType::Bool,   10,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QByteArray,   13,
    QMetaType::Void, 0x80000000 | 7,    8,
    QMetaType::Void,

 // methods: parameters
    QMetaType::Void,

       0        // eod
};

void CDobotProtocol::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CDobotProtocol *_t = static_cast<CDobotProtocol *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->bytesToWrite((*reinterpret_cast< const char*(*)>(_a[1])),(*reinterpret_cast< qint64(*)>(_a[2]))); break;
        case 1: _t->messageReady((*reinterpret_cast< const Message(*)>(_a[1]))); break;
        case 2: _t->onNewConnectStatus((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->onBytesWritten(); break;
        case 4: _t->onBytesReady((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 5: _t->sendMessage((*reinterpret_cast< const Message(*)>(_a[1]))); break;
        case 6: _t->periodicTask(); break;
        case 7: _t->onInit(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (CDobotProtocol::*_t)(const char * , qint64 );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CDobotProtocol::bytesToWrite)) {
                *result = 0;
            }
        }
        {
            typedef void (CDobotProtocol::*_t)(const Message & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CDobotProtocol::messageReady)) {
                *result = 1;
            }
        }
    }
}

const QMetaObject CDobotProtocol::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_CDobotProtocol.data,
      qt_meta_data_CDobotProtocol,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *CDobotProtocol::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CDobotProtocol::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_CDobotProtocol.stringdata0))
        return static_cast<void*>(const_cast< CDobotProtocol*>(this));
    return QObject::qt_metacast(_clname);
}

int CDobotProtocol::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void CDobotProtocol::bytesToWrite(const char * _t1, qint64 _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void CDobotProtocol::messageReady(const Message & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
