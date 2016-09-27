#include "seleccio-mouse.h"
#include "glwidget.h"

void SeleccioMouse::onPluginLoad()
{
    // Carregar shader, compile & link
    vs = new QGLShader(QGLShader::Vertex, this);
    vs->compileSourceFile("seleccio-mouse.vert");

    fs = new QGLShader(QGLShader::Fragment, this);
    fs->compileSourceFile("seleccio-mouse.frag");

    program = new QGLShaderProgram(this);
    program->addShader(vs);
    program->addShader(fs);
    program->link();
    cout << "Link log:" << program->log().toStdString() << endl;

    createBuffers();

    scene()->setSelectedObject(-1);
    glwidget()->clearScene();
}

void SeleccioMouse::setSelectedObject(int selected) {
    if (selected < 0 || selected >= (int)scene()->objects().size()) selected=-1;
    scene()->setSelectedObject(selected);
}

void SeleccioMouse::encodeID(int index, GLubyte *color) {
    color[0] = index;
}

int SeleccioMouse::decodeID(GLubyte *color) {
    if (color[0] == 255) return -1;
    return color[0];
}

void SeleccioMouse::drawColorScene()
{
    // establir modelViewProjection
    QMatrix4x4 MVP=camera()->projectionMatrix()*camera()->modelviewMatrix();
    program->setUniformValue("modelViewProjectionMatrix", MVP);

    Scene* scn = scene();
    const vector<Object> &obj = scn->objects();

    for (int i = 0; i < (int)obj.size(); ++i)
    {
        GLubyte color[4];
        encodeID(i,color);
        program->setUniformValue("color", QVector4D(color[0]/255., 0, 0, 1.0));
        drawPlugin()->drawObject(i);
    }
}

void SeleccioMouse::mouseReleaseEvent(QMouseEvent * e)
{
    if ( !(e->button() & Qt::RightButton)) return;
    if ( e->modifiers() & Qt::ShiftModifier) return;
    if ( !(e->modifiers() & Qt::ControlModifier)) return;

    // esborrar els buffers amb un color de fons únic (blanc)
    glClearColor(1, 1, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    // activar (bind) el shader program amb el VS+FS
    program->bind();
    drawColorScene();
    program->release();

    // llegir color del buffer de color sota la posicio del cursor
    int x = e->x();
    int y = glwidget()->height()-e->y();
    GLubyte read[4];
    glReadPixels(x, y, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, read);

    int seleccio = decodeID(&read[0]);
    setSelectedObject(seleccio);

    cout << "Selected object " << seleccio << endl;

    glwidget()->updateGL();
}

// rellena un vbo con los datos proporcionados:
// vbo_id = identificador del vbo
// size = número de elementos del array de datos
// data = array de datos
// attribute_id = identificador del atributo correspondiente del shader
// attribute_size = número de elementos que componen el atributo (ie. 3 para vértices)
// Se asume que los datos del array serán de tipo float
void SeleccioMouse::generate_vbo_GLfloat(GLuint &vbo_id, GLsizeiptr size, const GLfloat *data, GLuint attribute_id, GLint attribute_size) {
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
void SeleccioMouse::generate_vbo_GLuint(GLuint &vbo_id, GLsizeiptr size, const GLuint *data, GLuint attribute_id, GLint attribute_size) {
      glGenBuffers(1, &vbo_id);
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo_id);
      glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)*size, data, GL_STATIC_DRAW);
      glVertexAttribPointer(attribute_id, attribute_size, GL_UNSIGNED_INT, GL_FALSE, 0, 0);
      glEnableVertexAttribArray(attribute_id);
}

void SeleccioMouse::createBuffers() {
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

void SeleccioMouse::drawBox() {

    Scene* scn = scene();
    int i = scn->selectedObject();
    const vector<Object> &obj = scn->objects();

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
    program->setUniformValue("color", QVector4D(1.0, 1.0, 1.0, 1.0));
    // pintar la capsa contenidora de tots els objectes de l'escena
    glBindVertexArray(cubeVAO);
    int size;
    glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);
    glDrawElements(GL_TRIANGLES, size/sizeof(GLuint), GL_UNSIGNED_INT, (GLvoid*) 0);
    glBindVertexArray(0);
}

void SeleccioMouse::postFrame() {
    program->bind();
    GLint polygonMode;
    glGetIntegerv(GL_POLYGON_MODE, &polygonMode);     // get current polygon mode
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);        // paint using wireframe mode
    drawBox();                                        // draw box
    glPolygonMode(GL_FRONT_AND_BACK, polygonMode);    // restore previous polygon mode
    program->release();
}

#if QT_VERSION < 0x050000
Q_EXPORT_PLUGIN2(seleccio-mouse, SeleccioMouse)   // plugin name, plugin class
#endif
