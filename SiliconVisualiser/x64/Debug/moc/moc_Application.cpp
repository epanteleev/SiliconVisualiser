/****************************************************************************
** Meta object code from reading C++ file 'Application.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Application.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Application.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Application_t {
    QByteArrayData data[9];
    char stringdata0[98];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Application_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Application_t qt_meta_stringdata_Application = {
    {
QT_MOC_LITERAL(0, 0, 11), // "Application"
QT_MOC_LITERAL(1, 12, 12), // "createDialog"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 20), // "AbstractDialogFabric"
QT_MOC_LITERAL(4, 47, 6), // "fabric"
QT_MOC_LITERAL(5, 54, 8), // "Settings"
QT_MOC_LITERAL(6, 63, 3), // "set"
QT_MOC_LITERAL(7, 67, 15), // "triggerRotation"
QT_MOC_LITERAL(8, 83, 14) // "toggleRotation"

    },
    "Application\0createDialog\0\0"
    "AbstractDialogFabric\0fabric\0Settings\0"
    "set\0triggerRotation\0toggleRotation"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Application[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    2,   29,    2, 0x0a /* Public */,
       7,    0,   34,    2, 0x08 /* Private */,
       8,    0,   35,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 5,    4,    6,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Application::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Application *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->createDialog((*reinterpret_cast< const AbstractDialogFabric(*)>(_a[1])),(*reinterpret_cast< const Settings(*)>(_a[2]))); break;
        case 1: _t->triggerRotation(); break;
        case 2: _t->toggleRotation(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Application::staticMetaObject = { {
    &QMainWindow::staticMetaObject,
    qt_meta_stringdata_Application.data,
    qt_meta_data_Application,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Application::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Application::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Application.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int Application::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
