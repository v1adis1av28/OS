/****************************************************************************
** Meta object code from reading C++ file 'stockcars.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../StockCarsBase/stockcars.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'stockcars.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_StockCars_t {
    QByteArrayData data[12];
    char stringdata0[143];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_StockCars_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_StockCars_t qt_meta_stringdata_StockCars = {
    {
QT_MOC_LITERAL(0, 0, 9), // "StockCars"
QT_MOC_LITERAL(1, 10, 11), // "sl_HideInfo"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 7), // "sl_Save"
QT_MOC_LITERAL(4, 31, 11), // "sl_LoadFile"
QT_MOC_LITERAL(5, 43, 9), // "sl_Delete"
QT_MOC_LITERAL(6, 53, 13), // "sl_SwitchDate"
QT_MOC_LITERAL(7, 67, 9), // "sl_AddCar"
QT_MOC_LITERAL(8, 77, 15), // "sl_SwitchRecord"
QT_MOC_LITERAL(9, 93, 12), // "sl_EditTools"
QT_MOC_LITERAL(10, 106, 18), // "sl_CanselNewRecord"
QT_MOC_LITERAL(11, 125, 17) // "sl_CreateDataBase"

    },
    "StockCars\0sl_HideInfo\0\0sl_Save\0"
    "sl_LoadFile\0sl_Delete\0sl_SwitchDate\0"
    "sl_AddCar\0sl_SwitchRecord\0sl_EditTools\0"
    "sl_CanselNewRecord\0sl_CreateDataBase"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_StockCars[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   64,    2, 0x08 /* Private */,
       3,    0,   65,    2, 0x08 /* Private */,
       4,    0,   66,    2, 0x08 /* Private */,
       5,    0,   67,    2, 0x08 /* Private */,
       6,    0,   68,    2, 0x08 /* Private */,
       7,    0,   69,    2, 0x08 /* Private */,
       8,    0,   70,    2, 0x08 /* Private */,
       9,    0,   71,    2, 0x08 /* Private */,
      10,    0,   72,    2, 0x08 /* Private */,
      11,    0,   73,    2, 0x08 /* Private */,

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

       0        // eod
};

void StockCars::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<StockCars *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sl_HideInfo(); break;
        case 1: _t->sl_Save(); break;
        case 2: _t->sl_LoadFile(); break;
        case 3: _t->sl_Delete(); break;
        case 4: _t->sl_SwitchDate(); break;
        case 5: _t->sl_AddCar(); break;
        case 6: _t->sl_SwitchRecord(); break;
        case 7: _t->sl_EditTools(); break;
        case 8: _t->sl_CanselNewRecord(); break;
        case 9: _t->sl_CreateDataBase(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject StockCars::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_StockCars.data,
    qt_meta_data_StockCars,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *StockCars::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *StockCars::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_StockCars.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int StockCars::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 10;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
