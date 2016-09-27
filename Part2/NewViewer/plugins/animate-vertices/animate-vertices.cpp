#include "animate-vertices.h"

void AnimateVertices::onPluginLoad()
{
    // Carregar shader, compile & link
    vs = new QGLShader(QGLShader::Vertex, this);
    vs->compileSourceFile("animate-vertices.vert");

    fs = new QGLShader(QGLShader::Fragment, this);
    fs->compileSourceFile("animate-vertices.frag");

    program = new QGLShaderProgram(this);
    program->addShader(vs);
    program->addShader(fs);
    program->link();
    cout << "Link log:" << program->log().toStdString() << endl;

    time.start();
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), glwidget(), SLOT(updateGL()));
    timer->start();
}

void AnimateVertices::preFrame() 
{
    // bind shader and define uniforms
    program->bind();

    QMatrix4x4 MV = camera()->modelviewMatrix();
    program->setUniformValue("modelViewMatrix", MV);

    QMatrix4x4 P = camera()->projectionMatrix();
    program->setUniformValue("projectionMatrix", P);

    QMatrix3x3 N = camera()->modelviewMatrix().normalMatrix();
    program->setUniformValue("normalMatrix", N);

    program->setUniformValue("time", float(time.elapsed()/1000.0));
}

void AnimateVertices::postFrame() 
{
    // unbind shader
    program->release();
}

#if QT_VERSION < 0x050000
Q_EXPORT_PLUGIN2(animate-vertices, AnimateVertices)   // plugin name, plugin class
#endif

