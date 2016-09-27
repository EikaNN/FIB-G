#ifndef _SELECCIOMOUSE_H
#define _SELECCIOMOUSE_H

#include "basicplugin.h"
#include <QGLShader>
#include <QGLShaderProgram>


class SeleccioMouse : public QObject, public BasicPlugin
 {
     Q_OBJECT
     Q_INTERFACES(BasicPlugin)

 public:
    void onPluginLoad();
    void postFrame();

    void mouseReleaseEvent(QMouseEvent * e);
    
 private:
    QGLShaderProgram* program;
    QGLShader *fs, *vs;

    GLuint cubeVAO;
    GLuint verticesVBO;
    GLuint colorVBO;
    GLuint indicesVBO;

    void drawColorScene();
    void drawBox();
    void createBuffers();

    void encodeID(int index, GLubyte *color);
    int decodeID(GLubyte *color);
    void setSelectedObject(int selected);

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
 };
 
 #endif
