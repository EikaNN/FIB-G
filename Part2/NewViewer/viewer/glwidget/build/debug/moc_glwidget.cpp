/****************************************************************************
** Meta object code from reading C++ file 'glwidget.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../include/glwidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'glwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_GLWidget[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      32,   31,   31,    9, 0x0a,
      53,   44,   31,    9, 0x0a,
      80,   31,   31,    9, 0x0a,
      93,   31,   31,    9, 0x0a,
     107,   31,   31,    9, 0x0a,
     128,  118,   31,    9, 0x0a,
     168,   31,  164,    9, 0x0a,
     195,   31,   31,    9, 0x0a,
     213,  208,   31,    9, 0x0a,
     246,  238,   31,    9, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_GLWidget[] = {
    "GLWidget\0PLUGINGLWIDGET_EXPORT\0\0"
    "addObject()\0filename\0addObjectFromFile(QString)\0"
    "clearScene()\0resetCamera()\0drawAxes()\0"
    "pos,r,g,b\0drawPoint(Vector,float,float,float)\0"
    "Box\0boundingBoxIncludingAxes()\0"
    "loadPlugin()\0list\0loadPlugins(QStringList)\0"
    "plugins\0loadDefaultPlugins(QString&)\0"
};

void GLWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        GLWidget *_t = static_cast<GLWidget *>(_o);
        switch (_id) {
        case 0: _t->addObject(); break;
        case 1: _t->addObjectFromFile((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->clearScene(); break;
        case 3: _t->resetCamera(); break;
        case 4: _t->drawAxes(); break;
        case 5: _t->drawPoint((*reinterpret_cast< const Vector(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2])),(*reinterpret_cast< float(*)>(_a[3])),(*reinterpret_cast< float(*)>(_a[4]))); break;
        case 6: { Box _r = _t->boundingBoxIncludingAxes();
            if (_a[0]) *reinterpret_cast< Box*>(_a[0]) = _r; }  break;
        case 7: _t->loadPlugin(); break;
        case 8: _t->loadPlugins((*reinterpret_cast< const QStringList(*)>(_a[1]))); break;
        case 9: _t->loadDefaultPlugins((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData GLWidget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject GLWidget::staticMetaObject = {
    { &QGLWidget::staticMetaObject, qt_meta_stringdata_GLWidget,
      qt_meta_data_GLWidget, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &GLWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *GLWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *GLWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_GLWidget))
        return static_cast<void*>(const_cast< GLWidget*>(this));
    return QGLWidget::qt_metacast(_clname);
}

int GLWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGLWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
