/****************************************************************************
** Meta object code from reading C++ file 'qttelnet.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../telnet/qttelnet.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qttelnet.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_QtTelnet_t {
    QByteArrayData data[18];
    char stringdata0[175];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QtTelnet_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QtTelnet_t qt_meta_stringdata_QtTelnet = {
    {
QT_MOC_LITERAL(0, 0, 8), // "QtTelnet"
QT_MOC_LITERAL(1, 9, 13), // "loginRequired"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 11), // "loginFailed"
QT_MOC_LITERAL(4, 36, 8), // "loggedIn"
QT_MOC_LITERAL(5, 45, 9), // "loggedOut"
QT_MOC_LITERAL(6, 55, 15), // "connectionError"
QT_MOC_LITERAL(7, 71, 28), // "QAbstractSocket::SocketError"
QT_MOC_LITERAL(8, 100, 5), // "error"
QT_MOC_LITERAL(9, 106, 7), // "message"
QT_MOC_LITERAL(10, 114, 4), // "data"
QT_MOC_LITERAL(11, 119, 5), // "close"
QT_MOC_LITERAL(12, 125, 6), // "logout"
QT_MOC_LITERAL(13, 132, 11), // "sendControl"
QT_MOC_LITERAL(14, 144, 7), // "Control"
QT_MOC_LITERAL(15, 152, 4), // "ctrl"
QT_MOC_LITERAL(16, 157, 8), // "sendData"
QT_MOC_LITERAL(17, 166, 8) // "sendSync"

    },
    "QtTelnet\0loginRequired\0\0loginFailed\0"
    "loggedIn\0loggedOut\0connectionError\0"
    "QAbstractSocket::SocketError\0error\0"
    "message\0data\0close\0logout\0sendControl\0"
    "Control\0ctrl\0sendData\0sendSync"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QtTelnet[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   69,    2, 0x06 /* Public */,
       3,    0,   70,    2, 0x06 /* Public */,
       4,    0,   71,    2, 0x06 /* Public */,
       5,    0,   72,    2, 0x06 /* Public */,
       6,    1,   73,    2, 0x06 /* Public */,
       9,    1,   76,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      11,    0,   79,    2, 0x0a /* Public */,
      12,    0,   80,    2, 0x0a /* Public */,
      13,    1,   81,    2, 0x0a /* Public */,
      16,    1,   84,    2, 0x0a /* Public */,
      17,    0,   87,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 7,    8,
    QMetaType::Void, QMetaType::QString,   10,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 14,   15,
    QMetaType::Void, QMetaType::QString,   10,
    QMetaType::Void,

       0        // eod
};

void QtTelnet::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<QtTelnet *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->loginRequired(); break;
        case 1: _t->loginFailed(); break;
        case 2: _t->loggedIn(); break;
        case 3: _t->loggedOut(); break;
        case 4: _t->connectionError((*reinterpret_cast< QAbstractSocket::SocketError(*)>(_a[1]))); break;
        case 5: _t->message((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 6: _t->close(); break;
        case 7: _t->logout(); break;
        case 8: _t->sendControl((*reinterpret_cast< Control(*)>(_a[1]))); break;
        case 9: _t->sendData((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 10: _t->sendSync(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 4:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAbstractSocket::SocketError >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (QtTelnet::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QtTelnet::loginRequired)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (QtTelnet::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QtTelnet::loginFailed)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (QtTelnet::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QtTelnet::loggedIn)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (QtTelnet::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QtTelnet::loggedOut)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (QtTelnet::*)(QAbstractSocket::SocketError );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QtTelnet::connectionError)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (QtTelnet::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QtTelnet::message)) {
                *result = 5;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject QtTelnet::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_QtTelnet.data,
    qt_meta_data_QtTelnet,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *QtTelnet::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QtTelnet::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_QtTelnet.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int QtTelnet::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    }
    return _id;
}

// SIGNAL 0
void QtTelnet::loginRequired()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void QtTelnet::loginFailed()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void QtTelnet::loggedIn()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void QtTelnet::loggedOut()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void QtTelnet::connectionError(QAbstractSocket::SocketError _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void QtTelnet::message(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
