/****************************************************************************
** Meta object code from reading C++ file 'ViewStock.h'
**
** Created: Sat 4. Jan 21:59:36 2014
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Tarde/ViewStock.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ViewStock.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ViewStock[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      15,   11,   10,   10, 0x09,
      39,   10,   10,   10, 0x09,
      55,   10,   10,   10, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_ViewStock[] = {
    "ViewStock\0\0row\0getRowData(QModelIndex)\0"
    "deleteProduct()\0modifyProductWindow()\0"
};

const QMetaObject ViewStock::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_ViewStock,
      qt_meta_data_ViewStock, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ViewStock::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ViewStock::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ViewStock::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ViewStock))
        return static_cast<void*>(const_cast< ViewStock*>(this));
    return QDialog::qt_metacast(_clname);
}

int ViewStock::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: getRowData((*reinterpret_cast< QModelIndex(*)>(_a[1]))); break;
        case 1: deleteProduct(); break;
        case 2: modifyProductWindow(); break;
        default: ;
        }
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
