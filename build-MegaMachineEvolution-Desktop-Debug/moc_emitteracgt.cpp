/****************************************************************************
** Meta object code from reading C++ file 'emitteracgt.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../MegaMachineEvolution/StateMachines/emitteracgt.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'emitteracgt.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_emitterACGT_t {
    QByteArrayData data[10];
    char stringdata0[82];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_emitterACGT_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_emitterACGT_t qt_meta_stringdata_emitterACGT = {
    {
QT_MOC_LITERAL(0, 0, 11), // "emitterACGT"
QT_MOC_LITERAL(1, 12, 5), // "readA"
QT_MOC_LITERAL(2, 18, 0), // ""
QT_MOC_LITERAL(3, 19, 5), // "readC"
QT_MOC_LITERAL(4, 25, 5), // "readG"
QT_MOC_LITERAL(5, 31, 5), // "readT"
QT_MOC_LITERAL(6, 37, 5), // "readX"
QT_MOC_LITERAL(7, 43, 12), // "nextSequence"
QT_MOC_LITERAL(8, 56, 16), // "finishedSequence"
QT_MOC_LITERAL(9, 73, 8) // "finished"

    },
    "emitterACGT\0readA\0\0readC\0readG\0readT\0"
    "readX\0nextSequence\0finishedSequence\0"
    "finished"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_emitterACGT[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       8,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   54,    2, 0x06 /* Public */,
       3,    0,   55,    2, 0x06 /* Public */,
       4,    0,   56,    2, 0x06 /* Public */,
       5,    0,   57,    2, 0x06 /* Public */,
       6,    0,   58,    2, 0x06 /* Public */,
       7,    0,   59,    2, 0x06 /* Public */,
       8,    0,   60,    2, 0x06 /* Public */,
       9,    0,   61,    2, 0x06 /* Public */,

 // signals: parameters
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

void emitterACGT::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<emitterACGT *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->readA(); break;
        case 1: _t->readC(); break;
        case 2: _t->readG(); break;
        case 3: _t->readT(); break;
        case 4: _t->readX(); break;
        case 5: _t->nextSequence(); break;
        case 6: _t->finishedSequence(); break;
        case 7: _t->finished(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (emitterACGT::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&emitterACGT::readA)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (emitterACGT::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&emitterACGT::readC)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (emitterACGT::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&emitterACGT::readG)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (emitterACGT::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&emitterACGT::readT)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (emitterACGT::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&emitterACGT::readX)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (emitterACGT::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&emitterACGT::nextSequence)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (emitterACGT::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&emitterACGT::finishedSequence)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (emitterACGT::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&emitterACGT::finished)) {
                *result = 7;
                return;
            }
        }
    }
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject emitterACGT::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_emitterACGT.data,
    qt_meta_data_emitterACGT,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *emitterACGT::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *emitterACGT::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_emitterACGT.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int emitterACGT::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void emitterACGT::readA()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void emitterACGT::readC()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void emitterACGT::readG()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void emitterACGT::readT()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void emitterACGT::readX()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void emitterACGT::nextSequence()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void emitterACGT::finishedSequence()
{
    QMetaObject::activate(this, &staticMetaObject, 6, nullptr);
}

// SIGNAL 7
void emitterACGT::finished()
{
    QMetaObject::activate(this, &staticMetaObject, 7, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
