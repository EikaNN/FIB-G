#include "draw-bounding-box.h"

void DrawBoundingBox::onPluginLoad()
{
    // Carregar shader, compile & link
    vs = new QGLShader(QGLShader::Vertex, this);
    vs->compileSourceFile("draw-bounding-box.vert");

    fs = new QGLShader(QGLShader::Fragment, this);
    fs->compileSourceFile("draw-bounding-box.frag");

    program = new QGLShaderProgram(this);
    program->addShader(vs);
    program->addShader(fs);
    program->link();
    cout << "Link log:" << program->log().toStdString() << endl;

    createBuffers();

    glwidget()->clearScene();
}

// rellena un vbo con los datos proporcionados:
// vbo_id = identificador del vbo
// size = número de elementos del array de datos
// data = array de datos
// attribute_id = identificador del atributo correspondiente del shader
// attribute_size = número de elementos que componen el atributo (ie. 3 para vértices)
// Se asume que los datos del array serán de tipo float
void DrawBoundingBox::generate_vbo_GLfloat(GLuint &vbo_id, GLsizeiptr size, const GLfloat *data, GLuint attribute_id, GLint attribute_size) {
      glGenBuffers(1, &vbo_id);
      glBindBuffer(GL_ARRAY_BUFFER, vbo_id);
      glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*size, data, GL_STATIC_DRAW);
      glVertexAttribPointer(attribute_id, attribute_size, GL_FLOAT, GL_FALSE, 0, 0);
      glEnableVertexAttribArray(attribute_id);
}

// rellena un vbo con los datos proporcionados:
// vbo_id = identificador del vbo
// size = número de elementos del array de datos
// data = array de datos
// attribute_id = identificador del atributo correspondiente del shader
// attribute_size = número de elementos que componen el atributo (ie. 3 para vértices)
// Se asume que los datos del array serán de tipo uint
void DrawBoundingBox::generate_vbo_GLuint(GLuint &vbo_id, GLsizeiptr size, const GLuint *data, GLuint attribute_id, GLint attribute_size) {
      glGenBuffers(1, &vbo_id);
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo_id);
      glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)*size, data, GL_STATIC_DRAW);
      glVertexAttribPointer(attribute_id, attribute_size, GL_UNSIGNED_INT, GL_FALSE, 0, 0);
      glEnableVertexAttribArray(attribute_id);
}

void DrawBoundingBox::createBuffers() {
    // 8 vertices defining a cube
    GLfloat cube_vertices[] = {
        0, 0, 0,
        0, 0, 1,
        0, 1, 0,
        0, 1, 1,
        1, 0, 0,
        1, 0, 1,
        1, 1, 0,
        1, 1, 1
    };

    // assign a color to each vertex
    GLfloat cube_colors[] = {
        1, 0, 0,
        1, 0, 0,
        1, 0, 0,
        1, 0, 0,
        1, 0, 0,
        1, 0, 0,
        1, 0, 0,
        1, 0, 0,
    };

    // we hardcode indices, each face is made of 2 triangles
    GLuint cube_indices[] = {
        0, 1, 5,
        4, 0, 5,    //bottom
        2, 6, 3,
        6, 7, 3,    //top
        0, 4, 2,
        4, 6, 2,    //front
        7, 5, 1,
        1, 3, 7,    //back
        0, 2, 3,
        2, 3, 1,    //left
        4, 5, 7,
        7, 6, 4     //right
    };

    // VAO Capsa
    glGenVertexArrays(1, &cubeVAO);
    glBindVertexArray(cubeVAO);
    // VBOs Capsa
    generate_vbo_GLfloat(verticesVBO, sizeof(cube_vertices), &cube_vertices[0], 0, 3);
    generate_vbo_GLfloat(colorVBO, sizeof(cube_colors), &cube_colors[0], 2, 3);
    generate_vbo_GLuint(indicesVBO, sizeof(cube_indices), &cube_indices[0], 5, 3);
}

void DrawBoundingBox::drawBoxes() {

      Scene* scn=scene();
      const vector<Object> &obj=scn->objects();

      for (int i=0; i<(int)obj.size(); ++i) {

          Box box = obj[i].boundingBox();
          Point boundingBoxMax = box.max();
          Point boundingBoxMin = box.min();

          QMatrix4x4 scale = QMatrix4x4(
                      boundingBoxMax.x()-boundingBoxMin.x(), 0, 0,0,
                      0, boundingBoxMax.y()-boundingBoxMin.y(), 0, 0,
                      0, 0, boundingBoxMax.z()-boundingBoxMin.z(), 0,
                      0, 0, 0, 1
                      );

          QMatrix4x4 translate1 = QMatrix4x4(
                      1, 0, 0, -0.5,
                      0, 1, 0, -0.5,
                      0, 0, 1, -0.5,
                      0, 0, 0, 1
                      );
          QVector4D center = QVector4D((boundingBoxMax+boundingBoxMin)/2, 0);
          QMatrix4x4 translate2 = QMatrix4x4(
                      1, 0, 0, center.x(),
                      0, 1, 0, center.y(),
                      0, 0, 1, center.z(),
                      0, 0, 0, 1
                      );

          // establir modelViewProjection
          QMatrix4x4 MVP = camera()->projectionMatrix()*camera()->modelviewMatrix();
          MVP = MVP*translate2*scale*translate1;
          program->setUniformValue("modelViewProjectionMatrix", MVP);

          // pintar la capsa contenidora de tots els objectes de l'escena
          glBindVertexArray(cubeVAO);
          int size;
          glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);
          glDrawElements(GL_TRIANGLES, size/sizeof(GLuint), GL_UNSIGNED_INT, (GLvoid*) 0);
          glBindVertexArray(0);
      }
}


void DrawBoundingBox::postFrame() {
      program->bind();
      GLint polygonMode;
      glGetIntegerv(GL_POLYGON_MODE, &polygonMode);     // get current polygon mode
      glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);        // paint using wireframe mode
      drawBoxes();                                      // draw all boxes
      glPolygonMode(GL_FRONT_AND_BACK, polygonMode);    // restore previous polygon mode
      program->release();
}

#if QT_VERSION < 0x050000
Q_EXPORT_PLUGIN2(draw-bounding-box, DrawBoundingBox)   // plugin name, plugin class
#endif
