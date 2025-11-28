/****************************************************************************
** Meta object code from reading C++ file 'petrinetscene.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.13)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "Scene/petrinetscene.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'petrinetscene.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.13. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_PetriNetScene_t {
    QByteArrayData data[13];
    char stringdata0[129];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PetriNetScene_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PetriNetScene_t qt_meta_stringdata_PetriNetScene = {
    {
QT_MOC_LITERAL(0, 0, 13), // "PetriNetScene"
QT_MOC_LITERAL(1, 14, 15), // "transitionAdded"
QT_MOC_LITERAL(2, 30, 0), // ""
QT_MOC_LITERAL(3, 31, 16), // "PetriTransition*"
QT_MOC_LITERAL(4, 48, 10), // "transition"
QT_MOC_LITERAL(5, 59, 8), // "arcAdded"
QT_MOC_LITERAL(6, 68, 9), // "PetriArc*"
QT_MOC_LITERAL(7, 78, 3), // "arc"
QT_MOC_LITERAL(8, 82, 10), // "placeAdded"
QT_MOC_LITERAL(9, 93, 11), // "PetriPlace*"
QT_MOC_LITERAL(10, 105, 5), // "place"
QT_MOC_LITERAL(11, 111, 12), // "onTokensEdit"
QT_MOC_LITERAL(12, 124, 4) // "item"

    },
    "PetriNetScene\0transitionAdded\0\0"
    "PetriTransition*\0transition\0arcAdded\0"
    "PetriArc*\0arc\0placeAdded\0PetriPlace*\0"
    "place\0onTokensEdit\0item"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PetriNetScene[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   34,    2, 0x06 /* Public */,
       5,    1,   37,    2, 0x06 /* Public */,
       8,    1,   40,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      11,    1,   43,    2, 0x09 /* Protected */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void, 0x80000000 | 9,   10,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 9,   12,

       0        // eod
};

void PetriNetScene::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<PetriNetScene *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->transitionAdded((*reinterpret_cast< PetriTransition*(*)>(_a[1]))); break;
        case 1: _t->arcAdded((*reinterpret_cast< PetriArc*(*)>(_a[1]))); break;
        case 2: _t->placeAdded((*reinterpret_cast< PetriPlace*(*)>(_a[1]))); break;
        case 3: _t->onTokensEdit((*reinterpret_cast< PetriPlace*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< PetriTransition* >(); break;
            }
            break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< PetriArc* >(); break;
            }
            break;
        case 2:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< PetriPlace* >(); break;
            }
            break;
        case 3:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< PetriPlace* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (PetriNetScene::*)(PetriTransition * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PetriNetScene::transitionAdded)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (PetriNetScene::*)(PetriArc * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PetriNetScene::arcAdded)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (PetriNetScene::*)(PetriPlace * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PetriNetScene::placeAdded)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject PetriNetScene::staticMetaObject = { {
    QMetaObject::SuperData::link<QGraphicsScene::staticMetaObject>(),
    qt_meta_stringdata_PetriNetScene.data,
    qt_meta_data_PetriNetScene,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *PetriNetScene::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PetriNetScene::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_PetriNetScene.stringdata0))
        return static_cast<void*>(this);
    return QGraphicsScene::qt_metacast(_clname);
}

int PetriNetScene::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGraphicsScene::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void PetriNetScene::transitionAdded(PetriTransition * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void PetriNetScene::arcAdded(PetriArc * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void PetriNetScene::placeAdded(PetriPlace * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
