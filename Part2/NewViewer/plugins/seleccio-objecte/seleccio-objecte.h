#ifndef _SELECCIOOBJECTE_H
#define _SELECCIOOBJECTE_H

#include "basicplugin.h"
#include <QGLShader>
#include <QGLShaderProgram>


class SeleccioObjecte : public QObject, public BasicPlugin
{
    Q_OBJECT
    Q_INTERFACES(BasicPlugin)

public:
   void onPluginLoad();
   void postFrame();
   void onObjectAdd();

private:
   QGLShaderProgram* program;
   QGLShader *fs, *vs;

   GLuint cubeVAO;
   GLuint verticesVBO;
   GLuint colorVBO;
   GLuint indicesVBO;

   void createBuffers();
   void generate_vbo_GLfloat(GLuint &vbo_id,
                     GLsizeiptr size,
                     const GLfloat *data,
                     GLuint attribute_id,
                     GLint attribute_size);
   void generate_vbo_GLuint(GLuint &vbo_id,
                     GLsizeiptr size,
                     const GLuint *data,
                     GLuint attribute_id,
                     GLint attribute_size);
   void drawBox(int seleccionat);
};

#endif
