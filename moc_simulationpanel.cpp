/****************************************************************************
** Meta object code from reading C++ file 'simulationpanel.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.13)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "Widgets/simulationpanel.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'simulationpanel.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.13. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_SimulationPanel_t {
    QByteArrayData data[10];
    char stringdata0[149];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SimulationPanel_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SimulationPanel_t qt_meta_stringdata_SimulationPanel = {
    {
QT_MOC_LITERAL(0, 0, 15), // "SimulationPanel"
QT_MOC_LITERAL(1, 16, 17), // "simulationStarted"
QT_MOC_LITERAL(2, 34, 0), // ""
QT_MOC_LITERAL(3, 35, 16), // "simulationPaused"
QT_MOC_LITERAL(4, 52, 15), // "simulationReset"
QT_MOC_LITERAL(5, 68, 18), // "simulationFinished"
QT_MOC_LITERAL(6, 87, 14), // "onStartClicked"
QT_MOC_LITERAL(7, 102, 14), // "onPauseClicked"
QT_MOC_LITERAL(8, 117, 14), // "onResetClicked"
QT_MOC_LITERAL(9, 132, 16) // "onStepSimulation"

    },
    "SimulationPanel\0simulationStarted\0\0"
    "simulationPaused\0simulationReset\0"
    "simulationFinished\0onStartClicked\0"
    "onPauseClicked\0onResetClicked\0"
    "onStepSimulation"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SimulationPanel[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   54,    2, 0x06 /* Public */,
       3,    0,   55,    2, 0x06 /* Public */,
       4,    0,   56,    2, 0x06 /* Public */,
       5,    0,   57,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    0,   58,    2, 0x0a /* Public */,
       7,    0,   59,    2, 0x0a /* Public */,
       8,    0,   60,    2, 0x0a /* Public */,
       9,    0,   61,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void SimulationPanel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<SimulationPanel *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->simulationStarted(); break;
        case 1: _t->simulationPaused(); break;
        case 2: _t->simulationReset(); break;
        case 3: _t->simulationFinished(); break;
        case 4: _t->onStartClicked(); break;
        case 5: _t->onPauseClicked(); break;
        case 6: _t->onResetClicked(); break;
        case 7: _t->onStepSimulation(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (SimulationPanel::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SimulationPanel::simulationStarted)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (SimulationPanel::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SimulationPanel::simulationPaused)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (SimulationPanel::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SimulationPanel::simulationReset)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (SimulationPanel::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SimulationPanel::simulationFinished)) {
                *result = 3;
                return;
            }
        }
    }
    (void)_a;
}

QT_INIT_METAOBJECT const QMetaObject SimulationPanel::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_SimulationPanel.data,
    qt_meta_data_SimulationPanel,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *SimulationPanel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SimulationPanel::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_SimulationPanel.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int SimulationPanel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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
void SimulationPanel::simulationStarted()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void SimulationPanel::simulationPaused()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void SimulationPanel::simulationReset()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void SimulationPanel::simulationFinished()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
