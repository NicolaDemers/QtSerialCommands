/****************************************************************************
** Meta object code from reading C++ file 'QSerialDevice.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../QSerialDevice.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QList>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'QSerialDevice.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_QSerialDevice_t {
    QByteArrayData data[15];
    char stringdata0[198];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QSerialDevice_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QSerialDevice_t qt_meta_stringdata_QSerialDevice = {
    {
QT_MOC_LITERAL(0, 0, 13), // "QSerialDevice"
QT_MOC_LITERAL(1, 14, 14), // "commandTimeout"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 4), // "port"
QT_MOC_LITERAL(4, 35, 22), // "handleMatchingResponse"
QT_MOC_LITERAL(5, 58, 8), // "response"
QT_MOC_LITERAL(6, 67, 13), // "SerialCommand"
QT_MOC_LITERAL(7, 81, 7), // "command"
QT_MOC_LITERAL(8, 89, 21), // "handleMessageReceived"
QT_MOC_LITERAL(9, 111, 7), // "message"
QT_MOC_LITERAL(10, 119, 23), // "handleConnectionUpdated"
QT_MOC_LITERAL(11, 143, 9), // "connected"
QT_MOC_LITERAL(12, 153, 16), // "connectionFailed"
QT_MOC_LITERAL(13, 170, 20), // "handleCommandTimeout"
QT_MOC_LITERAL(14, 191, 6) // "params"

    },
    "QSerialDevice\0commandTimeout\0\0port\0"
    "handleMatchingResponse\0response\0"
    "SerialCommand\0command\0handleMessageReceived\0"
    "message\0handleConnectionUpdated\0"
    "connected\0connectionFailed\0"
    "handleCommandTimeout\0params"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QSerialDevice[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   44,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    2,   47,    2, 0x09 /* Protected */,
       8,    1,   52,    2, 0x09 /* Protected */,
      10,    2,   55,    2, 0x09 /* Protected */,
      10,    1,   60,    2, 0x29 /* Protected | MethodCloned */,
      13,    3,   63,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,

 // slots: parameters
    QMetaType::Void, QMetaType::QByteArray, 0x80000000 | 6,    5,    7,
    QMetaType::Void, QMetaType::QString,    9,
    QMetaType::Void, QMetaType::Bool, QMetaType::Bool,   11,   12,
    QMetaType::Void, QMetaType::Bool,   11,
    QMetaType::Void, 0x80000000 | 6, QMetaType::QVariantList, QMetaType::Int,    7,   14,    3,

       0        // eod
};

void QSerialDevice::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        QSerialDevice *_t = static_cast<QSerialDevice *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->commandTimeout((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->handleMatchingResponse((*reinterpret_cast< const QByteArray(*)>(_a[1])),(*reinterpret_cast< const SerialCommand(*)>(_a[2]))); break;
        case 2: _t->handleMessageReceived((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: _t->handleConnectionUpdated((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 4: _t->handleConnectionUpdated((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 5: _t->handleCommandTimeout((*reinterpret_cast< SerialCommand(*)>(_a[1])),(*reinterpret_cast< QList<QVariant>(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (QSerialDevice::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QSerialDevice::commandTimeout)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject QSerialDevice::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_QSerialDevice.data,
      qt_meta_data_QSerialDevice,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *QSerialDevice::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QSerialDevice::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_QSerialDevice.stringdata0))
        return static_cast<void*>(const_cast< QSerialDevice*>(this));
    return QObject::qt_metacast(_clname);
}

int QSerialDevice::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void QSerialDevice::commandTimeout(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
