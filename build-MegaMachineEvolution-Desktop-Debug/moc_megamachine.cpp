/****************************************************************************
** Meta object code from reading C++ file 'megamachine.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../MegaMachineEvolution/StateMachines/megamachine.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'megamachine.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MegaMachine_t {
    QByteArrayData data[24];
    char stringdata0[165];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MegaMachine_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MegaMachine_t qt_meta_stringdata_MegaMachine = {
    {
QT_MOC_LITERAL(0, 0, 11), // "MegaMachine"
QT_MOC_LITERAL(1, 12, 1), // "A"
QT_MOC_LITERAL(2, 14, 0), // ""
QT_MOC_LITERAL(3, 15, 1), // "C"
QT_MOC_LITERAL(4, 17, 1), // "G"
QT_MOC_LITERAL(5, 19, 1), // "T"
QT_MOC_LITERAL(6, 21, 1), // "X"
QT_MOC_LITERAL(7, 23, 11), // "stopMachine"
QT_MOC_LITERAL(8, 35, 12), // "resetMachine"
QT_MOC_LITERAL(9, 48, 7), // "stopped"
QT_MOC_LITERAL(10, 56, 14), // "stoppedMachine"
QT_MOC_LITERAL(11, 71, 6), // "ctrYes"
QT_MOC_LITERAL(12, 78, 5), // "ctrNo"
QT_MOC_LITERAL(13, 84, 3), // "yes"
QT_MOC_LITERAL(14, 88, 2), // "no"
QT_MOC_LITERAL(15, 91, 9), // "debugSlot"
QT_MOC_LITERAL(16, 101, 5), // "readA"
QT_MOC_LITERAL(17, 107, 5), // "readC"
QT_MOC_LITERAL(18, 113, 5), // "readG"
QT_MOC_LITERAL(19, 119, 5), // "readT"
QT_MOC_LITERAL(20, 125, 5), // "readX"
QT_MOC_LITERAL(21, 131, 16), // "finishedSequence"
QT_MOC_LITERAL(22, 148, 5), // "reset"
QT_MOC_LITERAL(23, 154, 10) // "machineEnd"

    },
    "MegaMachine\0A\0\0C\0G\0T\0X\0stopMachine\0"
    "resetMachine\0stopped\0stoppedMachine\0"
    "ctrYes\0ctrNo\0yes\0no\0debugSlot\0readA\0"
    "readC\0readG\0readT\0readX\0finishedSequence\0"
    "reset\0machineEnd"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MegaMachine[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      19,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       8,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,  109,    2, 0x06 /* Public */,
       3,    0,  110,    2, 0x06 /* Public */,
       4,    0,  111,    2, 0x06 /* Public */,
       5,    0,  112,    2, 0x06 /* Public */,
       6,    0,  113,    2, 0x06 /* Public */,
       7,    0,  114,    2, 0x06 /* Public */,
       8,    0,  115,    2, 0x06 /* Public */,
       9,    3,  116,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      13,    0,  123,    2, 0x0a /* Public */,
      14,    0,  124,    2, 0x0a /* Public */,
      15,    0,  125,    2, 0x0a /* Public */,
      16,    0,  126,    2, 0x0a /* Public */,
      17,    0,  127,    2, 0x0a /* Public */,
      18,    0,  128,    2, 0x0a /* Public */,
      19,    0,  129,    2, 0x0a /* Public */,
      20,    0,  130,    2, 0x0a /* Public */,
      21,    0,  131,    2, 0x0a /* Public */,
      22,    0,  132,    2, 0x0a /* Public */,
      23,    0,  133,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int,   10,   11,   12,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MegaMachine::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MegaMachine *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->A(); break;
        case 1: _t->C(); break;
        case 2: _t->G(); break;
        case 3: _t->T(); break;
        case 4: _t->X(); break;
        case 5: _t->stopMachine(); break;
        case 6: _t->resetMachine(); break;
        case 7: _t->stopped((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 8: _t->yes(); break;
        case 9: _t->no(); break;
        case 10: _t->debugSlot(); break;
        case 11: _t->readA(); break;
        case 12: _t->readC(); break;
        case 13: _t->readG(); break;
        case 14: _t->readT(); break;
        case 15: _t->readX(); break;
        case 16: _t->finishedSequence(); break;
        case 17: _t->reset(); break;
        case 18: _t->machineEnd(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (MegaMachine::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MegaMachine::A)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (MegaMachine::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MegaMachine::C)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (MegaMachine::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MegaMachine::G)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (MegaMachine::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MegaMachine::T)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (MegaMachine::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MegaMachine::X)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (MegaMachine::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MegaMachine::stopMachine)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (MegaMachine::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MegaMachine::resetMachine)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (MegaMachine::*)(int , int , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MegaMachine::stopped)) {
                *result = 7;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MegaMachine::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_MegaMachine.data,
    qt_meta_data_MegaMachine,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MegaMachine::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MegaMachine::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MegaMachine.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int MegaMachine::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 19)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 19;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 19)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 19;
    }
    return _id;
}

// SIGNAL 0
void MegaMachine::A()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void MegaMachine::C()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void MegaMachine::G()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void MegaMachine::T()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void MegaMachine::X()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void MegaMachine::stopMachine()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void MegaMachine::resetMachine()
{
    QMetaObject::activate(this, &staticMetaObject, 6, nullptr);
}

// SIGNAL 7
void MegaMachine::stopped(int _t1, int _t2, int _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
