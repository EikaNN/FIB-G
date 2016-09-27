/****************************************************************************
** Meta object code from reading C++ file 'shaderLoader.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../shaderLoader.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'shaderLoader.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ShaderLoader[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      42,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      14,   13,   13,   13, 0x0a,
      41,   13,   13,   13, 0x0a,
      70,   13,   13,   13, 0x0a,
      97,   13,   13,   13, 0x0a,
     118,  113,   13,   13, 0x0a,
     141,   13,   13,   13, 0x0a,
     165,   13,   13,   13, 0x0a,
     182,   13,   13,   13, 0x0a,
     199,   13,   13,   13, 0x0a,
     216,   13,   13,   13, 0x0a,
     240,   13,   13,   13, 0x0a,
     263,   13,   13,   13, 0x0a,
     287,   13,   13,   13, 0x0a,
     301,   13,   13,   13, 0x0a,
     317,   13,   13,   13, 0x0a,
     333,   13,   13,   13, 0x0a,
     349,   13,   13,   13, 0x0a,
     365,   13,   13,   13, 0x0a,
     381,   13,   13,   13, 0x0a,
     399,  394,   13,   13, 0x0a,
     419,   13,   13,   13, 0x0a,
     443,   13,   13,   13, 0x0a,
     458,   13,   13,   13, 0x0a,
     473,   13,   13,   13, 0x0a,
     488,   13,   13,   13, 0x0a,
     503,   13,   13,   13, 0x0a,
     518,   13,   13,   13, 0x0a,
     530,   13,   13,   13, 0x0a,
     548,   13,   13,   13, 0x0a,
     566,   13,   13,   13, 0x0a,
     585,   13,   13,   13, 0x0a,
     609,   13,   13,   13, 0x0a,
     631,   13,   13,   13, 0x0a,
     652,   13,   13,   13, 0x0a,
     672,   13,   13,   13, 0x0a,
     687,   13,   13,   13, 0x0a,
     708,   13,   13,   13, 0x0a,
     729,   13,   13,   13, 0x0a,
     754,  751,   13,   13, 0x0a,
     774,  771,   13,   13, 0x0a,
     800,   13,  792,   13, 0x0a,
     814,   13,   13,   13, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_ShaderLoader[] = {
    "ShaderLoader\0\0createDefaultShadersVSFS()\0"
    "createDefaultShadersVSGSFS()\0"
    "createShaderFromTemplate()\0attachShaders()\0"
    "name\0attachShaders(QString)\0"
    "openFilesInTextEditor()\0switchStatusVS()\0"
    "switchStatusGS()\0switchStatusFS()\0"
    "switchStatusWireframe()\0switchStatusShowAxes()\0"
    "switchStatusShowLight()\0resetCamera()\0"
    "cameraPreset1()\0cameraPreset2()\0"
    "cameraPreset3()\0cameraPreset4()\0"
    "cameraPreset5()\0loadObject()\0file\0"
    "loadObject(QString)\0changeBackgroundColor()\0"
    "loadTexture0()\0loadTexture1()\0"
    "loadTexture2()\0loadTexture3()\0"
    "showTextures()\0setLights()\0setLightAmbient()\0"
    "setLightDiffuse()\0setLightSpecular()\0"
    "setLightPositionWorld()\0setLightPositionEye()\0"
    "resetLightPosition()\0switchLightRotate()\0"
    "setMaterials()\0setMaterialAmbient()\0"
    "setMaterialDiffuse()\0setMaterialSpecular()\0"
    "id\0editUniform(int)\0up\0uniformMult(bool)\0"
    "QString\0executeTest()\0compareTest()\0"
};

void ShaderLoader::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ShaderLoader *_t = static_cast<ShaderLoader *>(_o);
        switch (_id) {
        case 0: _t->createDefaultShadersVSFS(); break;
        case 1: _t->createDefaultShadersVSGSFS(); break;
        case 2: _t->createShaderFromTemplate(); break;
        case 3: _t->attachShaders(); break;
        case 4: _t->attachShaders((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 5: _t->openFilesInTextEditor(); break;
        case 6: _t->switchStatusVS(); break;
        case 7: _t->switchStatusGS(); break;
        case 8: _t->switchStatusFS(); break;
        case 9: _t->switchStatusWireframe(); break;
        case 10: _t->switchStatusShowAxes(); break;
        case 11: _t->switchStatusShowLight(); break;
        case 12: _t->resetCamera(); break;
        case 13: _t->cameraPreset1(); break;
        case 14: _t->cameraPreset2(); break;
        case 15: _t->cameraPreset3(); break;
        case 16: _t->cameraPreset4(); break;
        case 17: _t->cameraPreset5(); break;
        case 18: _t->loadObject(); break;
        case 19: _t->loadObject((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 20: _t->changeBackgroundColor(); break;
        case 21: _t->loadTexture0(); break;
        case 22: _t->loadTexture1(); break;
        case 23: _t->loadTexture2(); break;
        case 24: _t->loadTexture3(); break;
        case 25: _t->showTextures(); break;
        case 26: _t->setLights(); break;
        case 27: _t->setLightAmbient(); break;
        case 28: _t->setLightDiffuse(); break;
        case 29: _t->setLightSpecular(); break;
        case 30: _t->setLightPositionWorld(); break;
        case 31: _t->setLightPositionEye(); break;
        case 32: _t->resetLightPosition(); break;
        case 33: _t->switchLightRotate(); break;
        case 34: _t->setMaterials(); break;
        case 35: _t->setMaterialAmbient(); break;
        case 36: _t->setMaterialDiffuse(); break;
        case 37: _t->setMaterialSpecular(); break;
        case 38: _t->editUniform((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 39: _t->uniformMult((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 40: { QString _r = _t->executeTest();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 41: _t->compareTest(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData ShaderLoader::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ShaderLoader::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_ShaderLoader,
      qt_meta_data_ShaderLoader, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ShaderLoader::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ShaderLoader::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ShaderLoader::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ShaderLoader))
        return static_cast<void*>(const_cast< ShaderLoader*>(this));
    if (!strcmp(_clname, "BasicPlugin"))
        return static_cast< BasicPlugin*>(const_cast< ShaderLoader*>(this));
    if (!strcmp(_clname, "edu.upc.fib.graug.BasicPlugin/1.0"))
        return static_cast< BasicPlugin*>(const_cast< ShaderLoader*>(this));
    return QObject::qt_metacast(_clname);
}

int ShaderLoader::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 42)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 42;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
