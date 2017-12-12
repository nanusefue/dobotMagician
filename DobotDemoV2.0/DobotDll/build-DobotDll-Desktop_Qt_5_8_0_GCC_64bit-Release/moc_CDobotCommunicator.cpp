/****************************************************************************
** Meta object code from reading C++ file 'CDobotCommunicator.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../SourceCode/src/CDobotCommunicator.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'CDobotCommunicator.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_CDobotCommunicator_t {
    QByteArrayData data[16];
    char stringdata0[188];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CDobotCommunicator_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CDobotCommunicator_t qt_meta_stringdata_CDobotCommunicator = {
    {
QT_MOC_LITERAL(0, 0, 18), // "CDobotCommunicator"
QT_MOC_LITERAL(1, 19, 13), // "messageToSend"
QT_MOC_LITERAL(2, 33, 0), // ""
QT_MOC_LITERAL(3, 34, 7), // "Message"
QT_MOC_LITERAL(4, 42, 7), // "message"
QT_MOC_LITERAL(5, 50, 18), // "onNewConnectStatus"
QT_MOC_LITERAL(6, 69, 9), // "connected"
QT_MOC_LITERAL(7, 79, 14), // "onMessageReady"
QT_MOC_LITERAL(8, 94, 12), // "stateMachine"
QT_MOC_LITERAL(9, 107, 6), // "onInit"
QT_MOC_LITERAL(10, 114, 13), // "setCmdTimeout"
QT_MOC_LITERAL(11, 128, 14), // "isFinishedAddr"
QT_MOC_LITERAL(12, 143, 10), // "resultAddr"
QT_MOC_LITERAL(13, 154, 7), // "timeout"
QT_MOC_LITERAL(14, 162, 13), // "insertMessage"
QT_MOC_LITERAL(15, 176, 11) // "messageAddr"

    },
    "CDobotCommunicator\0messageToSend\0\0"
    "Message\0message\0onNewConnectStatus\0"
    "connected\0onMessageReady\0stateMachine\0"
    "onInit\0setCmdTimeout\0isFinishedAddr\0"
    "resultAddr\0timeout\0insertMessage\0"
    "messageAddr"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CDobotCommunicator[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   49,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    1,   52,    2, 0x0a /* Public */,
       7,    1,   55,    2, 0x0a /* Public */,
       8,    0,   58,    2, 0x08 /* Private */,

 // methods: name, argc, parameters, tag, flags
       9,    0,   59,    2, 0x02 /* Public */,
      10,    3,   60,    2, 0x00 /* Private */,
      14,    3,   67,    2, 0x00 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,

 // slots: parameters
    QMetaType::Void, QMetaType::Bool,    6,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void,

 // methods: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::VoidStar, QMetaType::VoidStar, QMetaType::UInt,   11,   12,   13,
    QMetaType::Void, QMetaType::VoidStar, QMetaType::VoidStar, QMetaType::VoidStar,   11,   12,   15,

       0        // eod
};

void CDobotCommunicator::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CDobotCommunicator *_t = static_cast<CDobotCommunicator *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->messageToSend((*reinterpret_cast< const Message(*)>(_a[1]))); break;
        case 1: _t->onNewConnectStatus((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->onMessageReady((*reinterpret_cast< const Message(*)>(_a[1]))); break;
        case 3: _t->stateMachine(); break;
        case 4: _t->onInit(); break;
        case 5: _t->setCmdTimeout((*reinterpret_cast< void*(*)>(_a[1])),(*reinterpret_cast< void*(*)>(_a[2])),(*reinterpret_cast< uint(*)>(_a[3]))); break;
        case 6: _t->insertMessage((*reinterpret_cast< void*(*)>(_a[1])),(*reinterpret_cast< void*(*)>(_a[2])),(*reinterpret_cast< void*(*)>(_a[3]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (CDobotCommunicator::*_t)(const Message & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CDobotCommunicator::messageToSend)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject CDobotCommunicator::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_CDobotCommunicator.data,
      qt_meta_data_CDobotCommunicator,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *CDobotCommunicator::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CDobotCommunicator::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_CDobotCommunicator.stringdata0))
        return static_cast<void*>(const_cast< CDobotCommunicator*>(this));
    return QObject::qt_metacast(_clname);
}

int CDobotCommunicator::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void CDobotCommunicator::messageToSend(const Message & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
