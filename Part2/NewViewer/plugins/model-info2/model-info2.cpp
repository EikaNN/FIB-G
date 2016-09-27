#include "model-info2.h"
#include "glwidget.h"
#include <iostream>
using namespace std;

void ModelInfo2::updateModelInfo()
{
	Scene* scn = scene();
    const vector<Object> &objects = scn->objects();
	nobj = objects.size();
    npol = nver = ntri = 0;
	for (int i = 0; i < nobj; ++i)
	{
        const Object &obj = objects[i];
        nver += obj.vertices().size();
        const vector<Face> &faces = obj.faces();
		npol += faces.size();
		for (int j = 0; j < npol; ++j)
		{
			if (faces[j].numVertices() == 3) ++ntri;
		}
	}
}

void ModelInfo2::drawRect()
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

void ModelInfo2::onPluginLoad()
{
    nobj_str = "Objectes: \t%1";
    npol_str = "Poligons: \t\t%1";
    nver_str = "Vertices: \t\t%1";
    ntri_str = "%Triangles: \t%1%";
    updateModelInfo();
    // Carregar shader, compile & link
    vs = new QGLShader(QGLShader::Vertex, this);
    vs->compileSourceFile("model-info2.vert");

    fs = new QGLShader(QGLShader::Fragment, this);
    fs->compileSourceFile("model-info2.frag");

    program = new QGLShaderProgram(this);
    program->addShader(vs);
    program->addShader(fs);
    program->link();
}

void ModelInfo2::onObjectAdd()
{
    updateModelInfo();
}

void ModelInfo2::postFrame()
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
    painter.drawText(x, y, nobj_str.arg(nobj));
    painter.drawText(x, y+40, npol_str.arg(npol));
    painter.drawText(x, y+80, nver_str.arg(nver));
    painter.drawText(x, y+120, ntri_str.arg(ntri/double(npol)*100));
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
Q_EXPORT_PLUGIN2(model-info2, ModelInfo2)   // plugin name, plugin class
#endif
