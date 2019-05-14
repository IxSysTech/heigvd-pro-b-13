/****************************************************************************
** Meta object code from reading C++ file 'megamachinemanager.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../MegaMachineEvolution/StateMachines/megamachinemanager.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'megamachinemanager.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MegaMachineManager_t {
    QByteArrayData data[9];
    char stringdata0[87];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MegaMachineManager_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MegaMachineManager_t qt_meta_stringdata_MegaMachineManager = {
    {
QT_MOC_LITERAL(0, 0, 18), // "MegaMachineManager"
QT_MOC_LITERAL(1, 19, 8), // "finished"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 11), // "runMachines"
QT_MOC_LITERAL(4, 41, 4), // "stop"
QT_MOC_LITERAL(5, 46, 14), // "stoppedMachine"
QT_MOC_LITERAL(6, 61, 6), // "ctrYes"
QT_MOC_LITERAL(7, 68, 5), // "ctrNo"
QT_MOC_LITERAL(8, 74, 12) // "nextSequence"

    },
    "MegaMachineManager\0finished\0\0runMachines\0"
    "stop\0stoppedMachine\0ctrYes\0ctrNo\0"
    "nextSequence"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MegaMachineManager[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   34,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    0,   35,    2, 0x0a /* Public */,
       4,    3,   36,    2, 0x0a /* Public */,
       8,    0,   43,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int,    5,    6,    7,
    QMetaType::Void,

       0        // eod
};

void MegaMachineManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MegaMachineManager *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->finished(); break;
        case 1: _t->runMachines(); break;
        case 2: _t->stop((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 3: _t->nextSequence(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (MegaMachineManager::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MegaMachineManager::finished)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MegaMachineManager::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_MegaMachineManager.data,
    qt_meta_data_MegaMachineManager,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MegaMachineManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MegaMachineManager::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MegaMachineManager.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int MegaMachineManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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

// SIGNAL 0
void MegaMachineManager::finished()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
