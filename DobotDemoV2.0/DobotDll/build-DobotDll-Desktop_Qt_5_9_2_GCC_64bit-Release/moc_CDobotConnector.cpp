/****************************************************************************
** Meta object code from reading C++ file 'CDobotConnector.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../SourceCode/src/CDobotConnector.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'CDobotConnector.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_CDobotConnector_t {
    QByteArrayData data[24];
    char stringdata0[271];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CDobotConnector_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CDobotConnector_t qt_meta_stringdata_CDobotConnector = {
    {
QT_MOC_LITERAL(0, 0, 15), // "CDobotConnector"
QT_MOC_LITERAL(1, 16, 16), // "newConnectStatus"
QT_MOC_LITERAL(2, 33, 0), // ""
QT_MOC_LITERAL(3, 34, 9), // "connected"
QT_MOC_LITERAL(4, 44, 12), // "bytesWritten"
QT_MOC_LITERAL(5, 57, 10), // "bytesReady"
QT_MOC_LITERAL(6, 68, 5), // "array"
QT_MOC_LITERAL(7, 74, 14), // "onBytesToWrite"
QT_MOC_LITERAL(8, 89, 11), // "const char*"
QT_MOC_LITERAL(9, 101, 4), // "data"
QT_MOC_LITERAL(10, 106, 7), // "maxSize"
QT_MOC_LITERAL(11, 114, 12), // "onBytesReady"
QT_MOC_LITERAL(12, 127, 6), // "onInit"
QT_MOC_LITERAL(13, 134, 11), // "searchDobot"
QT_MOC_LITERAL(14, 146, 14), // "isFinishedAddr"
QT_MOC_LITERAL(15, 161, 10), // "resultAddr"
QT_MOC_LITERAL(16, 172, 17), // "dobotNameListAddr"
QT_MOC_LITERAL(17, 190, 6), // "maxLen"
QT_MOC_LITERAL(18, 197, 12), // "connectDobot"
QT_MOC_LITERAL(19, 210, 12), // "portNameAddr"
QT_MOC_LITERAL(20, 223, 8), // "baudrate"
QT_MOC_LITERAL(21, 232, 10), // "fwTypeAddr"
QT_MOC_LITERAL(22, 243, 11), // "versionAddr"
QT_MOC_LITERAL(23, 255, 15) // "disconnectDobot"

    },
    "CDobotConnector\0newConnectStatus\0\0"
    "connected\0bytesWritten\0bytesReady\0"
    "array\0onBytesToWrite\0const char*\0data\0"
    "maxSize\0onBytesReady\0onInit\0searchDobot\0"
    "isFinishedAddr\0resultAddr\0dobotNameListAddr\0"
    "maxLen\0connectDobot\0portNameAddr\0"
    "baudrate\0fwTypeAddr\0versionAddr\0"
    "disconnectDobot"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CDobotConnector[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   59,    2, 0x06 /* Public */,
       4,    0,   62,    2, 0x06 /* Public */,
       5,    1,   63,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    2,   66,    2, 0x0a /* Public */,
      11,    0,   71,    2, 0x0a /* Public */,

 // methods: name, argc, parameters, tag, flags
      12,    0,   72,    2, 0x02 /* Public */,
      13,    4,   73,    2, 0x00 /* Private */,
      18,    6,   82,    2, 0x00 /* Private */,
      23,    2,   95,    2, 0x00 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QByteArray,    6,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 8, QMetaType::LongLong,    9,   10,
    QMetaType::Void,

 // methods: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::VoidStar, QMetaType::VoidStar, QMetaType::VoidStar, QMetaType::UInt,   14,   15,   16,   17,
    QMetaType::Void, QMetaType::VoidStar, QMetaType::VoidStar, QMetaType::VoidStar, QMetaType::UInt, QMetaType::VoidStar, QMetaType::VoidStar,   14,   15,   19,   20,   21,   22,
    QMetaType::Void, QMetaType::VoidStar, QMetaType::VoidStar,   14,   15,

       0        // eod
};

void CDobotConnector::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CDobotConnector *_t = static_cast<CDobotConnector *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->newConnectStatus((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->bytesWritten(); break;
        case 2: _t->bytesReady((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 3: _t->onBytesToWrite((*reinterpret_cast< const char*(*)>(_a[1])),(*reinterpret_cast< qint64(*)>(_a[2]))); break;
        case 4: _t->onBytesReady(); break;
        case 5: _t->onInit(); break;
        case 6: _t->searchDobot((*reinterpret_cast< void*(*)>(_a[1])),(*reinterpret_cast< void*(*)>(_a[2])),(*reinterpret_cast< void*(*)>(_a[3])),(*reinterpret_cast< uint(*)>(_a[4]))); break;
        case 7: _t->connectDobot((*reinterpret_cast< void*(*)>(_a[1])),(*reinterpret_cast< void*(*)>(_a[2])),(*reinterpret_cast< void*(*)>(_a[3])),(*reinterpret_cast< uint(*)>(_a[4])),(*reinterpret_cast< void*(*)>(_a[5])),(*reinterpret_cast< void*(*)>(_a[6]))); break;
        case 8: _t->disconnectDobot((*reinterpret_cast< void*(*)>(_a[1])),(*reinterpret_cast< void*(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (CDobotConnector::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CDobotConnector::newConnectStatus)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (CDobotConnector::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CDobotConnector::bytesWritten)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (CDobotConnector::*_t)(QByteArray );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CDobotConnector::bytesReady)) {
                *result = 2;
                return;
            }
        }
    }
}

const QMetaObject CDobotConnector::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_CDobotConnector.data,
      qt_meta_data_CDobotConnector,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *CDobotConnector::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CDobotConnector::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CDobotConnector.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int CDobotConnector::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void CDobotConnector::newConnectStatus(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void CDobotConnector::bytesWritten()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void CDobotConnector::bytesReady(QByteArray _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
