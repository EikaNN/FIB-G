#ifndef _FRAMERATE_H
#define _FRAMERATE_H

#include "basicplugin.h"
#include <QElapsedTimer>

class Framerate : public QObject, public BasicPlugin
{

  	Q_OBJECT
#if QT_VERSION >= 0x050000
  	Q_PLUGIN_METADATA(IID "BasicPlugin")   
#endif
  	Q_INTERFACES(BasicPlugin)


public:
    void onPluginLoad();
    void postFrame();

private:
    void drawRect();

    QGLShaderProgram* program;
    QGLShader* vs;
    QGLShader* fs;

    int fps, frames;
    GLuint textureID;

private slots:
    void updateFPS();

};

#endif

