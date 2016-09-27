#include "plantilla.h"

void Plantilla::onPluginLoad()
{
    // Carregar shader, compile & link
    vs = new QGLShader(QGLShader::Vertex, this);
    vs->compileSourceFile("plantilla.vert");

    fs = new QGLShader(QGLShader::Fragment, this);
    fs->compileSourceFile("plantilla.frag");

    program = new QGLShaderProgram(this);
    program->addShader(vs);
    program->addShader(fs);
    program->link();
    cout << "Link log:" << program->log().toStdString() << endl;
}

void Plantilla::preFrame()
{
    // bind shader and define uniforms
    program->bind();

    QMatrix4x4 MV = camera()->modelviewMatrix();
    program->setUniformValue("modelViewMatrix", MV);

    QMatrix4x4 MVP = camera()->projectionMatrix()*MV;
    program->setUniformValue("modelViewProjectionMatrix", MVP);

    QMatrix3x3 N = camera()->modelviewMatrix().normalMatrix();
    program->setUniformValue("normalMatrix", N);

    program->setUniformValue("lightAmbient", QVector4D(Vector(0.1,0.1,0.1),1));
    program->setUniformValue("lightDiffuse", QVector4D(Vector(1,1,1),1));
    program->setUniformValue("lightSpecular", QVector4D(Vector(1,1,1),1));
    program->setUniformValue("lightPosition", QVector4D(0,0,0,1));

    program->setUniformValue("matAmbient", QVector4D(Vector(0.8, 0.8, 0.6),1));
    program->setUniformValue("matDiffuse", QVector4D(Vector(0.8, 0.8, 0.6),1));
    program->setUniformValue("matSpecular", QVector4D(Vector(1.0, 1.0, 1.0),1));
    program->setUniformValue("matShininess", GLfloat(64.0));
}

void Plantilla::postFrame()
{
    // unbind shader
    program->release();
}

#if QT_VERSION < 0x050000
Q_EXPORT_PLUGIN2(plantilla, Plantilla)   // plugin name, plugin class
#endif
