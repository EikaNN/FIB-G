#ifndef _PLANTILLA_H
#define _PLANTILLA_H

#include "basicplugin.h"
#include <QGLShader>
#include <QGLShaderProgram>


class Plantilla : public QObject, public BasicPlugin
 {
     Q_OBJECT
     Q_INTERFACES(BasicPlugin)

 public:
    void onPluginLoad();
    void preFrame();
    void postFrame();
    
 private:
    QGLShaderProgram* program;
    QGLShader *fs, *vs;
 };
 
 #endif
