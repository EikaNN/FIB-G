#ifndef _SHOWDEGREE_H
#define _SHOWDEGREE_H

#include "basicplugin.h"
#include <QGLShader>
#include <QGLShaderProgram>


class ShowDegree : public QObject, public BasicPlugin
 {
     Q_OBJECT
     Q_INTERFACES(BasicPlugin)

 public:
    void onPluginLoad();
    void postFrame();
    void onObjectAdd();
    
 private:
    void drawRect();
    void getModelDegree();

    QGLShaderProgram* program;
    QGLShader *fs, *vs;
    GLuint textureID;
    GLfloat degree;

 };
 
 #endif
