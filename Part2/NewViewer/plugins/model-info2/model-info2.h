#ifndef _MODELINFO2_H
#define _MODELINFO2_H

#include "basicplugin.h"

class ModelInfo2 : public QObject, public BasicPlugin
{

  	Q_OBJECT
#if QT_VERSION >= 0x050000
  	Q_PLUGIN_METADATA(IID "BasicPlugin")   
#endif
  	Q_INTERFACES(BasicPlugin)


public:
	void onPluginLoad();
  	void onObjectAdd();
    void postFrame();

private:
    void updateModelInfo();
    void drawRect();

    GLuint textureID;
    QGLShaderProgram* program;
    QGLShader* vs;
    QGLShader* fs;

    int nobj, npol, nver, ntri;

    QString nobj_str;
    QString npol_str;
    QString nver_str;
    QString ntri_str;

};

#endif

