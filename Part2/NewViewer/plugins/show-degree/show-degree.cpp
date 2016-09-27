#include "show-degree.h"
#include "glwidget.h"
using namespace std;

void ShowDegree::drawRect()
{
    static bool created = false;
    static GLuint VAO_rect;

    // 1. Create VBO Buffers
    if (!created)
    {
        created = true;

        // Create & bind empty VAO
        glGenVertexArrays(1, &VAO_rect);
        glBindVertexArray(VAO_rect);

        float z = -0.99999;
        // Create VBO with (x,y,z) coordinates
        float coords[] = { -1, -1, z,
                            1, -1, z,
                           -1,  1, z,
                            1,  1, z};

        GLuint VBO_coords;
        glGenBuffers(1, &VBO_coords);
        glBindBuffer(GL_ARRAY_BUFFER, VBO_coords);
        glBufferData(GL_ARRAY_BUFFER, sizeof(coords), coords, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
        glEnableVertexAttribArray(0);
        glBindVertexArray(0);
    }

    // 2. Draw
    glBindVertexArray (VAO_rect);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glBindVertexArray(0);
}

void ShowDegree::getModelDegree()
{
    Scene* scn = scene();
    if (!scn->objects().size()) return;
    const Object &obj = scn->objects()[0];
    const vector<Face> &faces = obj.faces();
    int npol = faces.size();
    GLfloat total = 0.0;
    for (int i = 0; i < npol; ++i) {
        total += faces[i].numVertices();
    }
    degree = total / obj.vertices().size();
}


void ShowDegree::onPluginLoad()
{
    // Carregar shader, compile & link
    vs = new QGLShader(QGLShader::Vertex, this);
    vs->compileSourceFile("show-degree.vert");

    fs = new QGLShader(QGLShader::Fragment, this);
    fs->compileSourceFile("show-degree.frag");

    program = new QGLShaderProgram(this);
    program->addShader(vs);
    program->addShader(fs);
    program->link();

    degree = 0;
    glwidget()->clearScene();
}

void ShowDegree::onObjectAdd()
{
    getModelDegree();
}

void ShowDegree::postFrame()
{
    const int SIZE = 1024;
    // 1. Create image with text
    QImage image(SIZE,SIZE,QImage::Format_RGB32);
    image.fill(Qt::white);
    QPainter painter(&image);
    QFont font;
    font.setPixelSize(32);
    painter.setFont(font);
    painter.setPen(QColor(50,50,50));
    int x = 15;
    int y = 50;
    QString degree_str = QString::number(degree);
    painter.drawText(x, y, QString("Degree: " + degree_str));
    painter.end();

    // 2. Create texture
    const int textureUnit = 5;
    glActiveTexture(GL_TEXTURE0+textureUnit);
    QImage im0 = QGLWidget::convertToGLFormat(image);
    glGenTextures( 1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, im0.width(), im0.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, im0.bits());
    glGenerateMipmap(GL_TEXTURE_2D);
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );

    // Pass 2. Draw quad using texture
    program->bind();
    program->setUniformValue("colorMap", textureUnit);
    program->setUniformValue("WIDTH", float(glwidget()->width()));
    program->setUniformValue("HEIGHT", float(glwidget()->height()));

    // quad covering viewport
    drawRect();
    program->release();
    glBindTexture(GL_TEXTURE_2D, 0);

    glDeleteTextures(1, &textureID);

}

#if QT_VERSION < 0x050000
Q_EXPORT_PLUGIN2(show-degree, ShowDegree)   // plugin name, plugin class
#endif


