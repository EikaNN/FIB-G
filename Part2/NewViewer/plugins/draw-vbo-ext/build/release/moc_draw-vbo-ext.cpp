/****************************************************************************
** Meta object code from reading C++ file 'draw-vbo-ext.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../draw-vbo-ext.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'draw-vbo-ext.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_DrawVBO[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

static const char qt_meta_stringdata_DrawVBO[] = {
    "DrawVBO\0"
};

void DrawVBO::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObjectExtraData DrawVBO::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject DrawVBO::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_DrawVBO,
      qt_meta_data_DrawVBO, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &DrawVBO::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *DrawVBO::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *DrawVBO::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_DrawVBO))
        return static_cast<void*>(const_cast< DrawVBO*>(this));
    if (!strcmp(_clname, "BasicPlugin"))
        return static_cast< BasicPlugin*>(const_cast< DrawVBO*>(this));
    if (!strcmp(_clname, "edu.upc.fib.graug.BasicPlugin/1.0"))
        return static_cast< BasicPlugin*>(const_cast< DrawVBO*>(this));
    return QObject::qt_metacast(_clname);
}

int DrawVBO::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
QT_END_MOC_NAMESPACE
