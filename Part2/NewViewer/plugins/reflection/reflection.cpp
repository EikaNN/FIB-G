#include "reflection.h"

const int IMAGE_WIDTH = 1024;
const int IMAGE_HEIGHT = IMAGE_WIDTH;

#define printOpenGLError() printOglError(__FILE__, __LINE__)
#define CHECK() printOglError(__FILE__, __LINE__,__FUNCTION__)
#define DEBUG() cout << __FILE__ << " " << __LINE__ << " " << __FUNCTION__ << endl;

int printOglError(const char file[], int line, const char func[]) 
{
    GLenum glErr;
    int    retCode = 0;

    glErr = glGetError();
    if (glErr != GL_NO_ERROR)
    {
        printf("glError in file %s @ line %d: %s function: %s\n", file, line, gluErrorString(glErr), func);
        retCode = 1;
    }
    return retCode;
}

void Reflection::onPluginLoad()
{
    // Resize to power-of-two viewport
    glwidget()->resize(IMAGE_WIDTH,IMAGE_HEIGHT);

    // Carregar shader, compile & link 
    QGLShader* vs = new QGLShader(QGLShader::Vertex, this);
    vs->compileSourceFile("reflection.vert");

    QGLShader* fs = new QGLShader(QGLShader::Fragment, this);
    fs->compileSourceFile("reflection.frag");

    program = new QGLShaderProgram(this);
    program->addShader(vs);
    program->addShader(fs);
    program->link();

    // Setup texture
    //glActiveTexture(GL_TEXTURE0);
    glGenTextures( 1, &textureId);
    glBindTexture(GL_TEXTURE_2D, textureId);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, IMAGE_WIDTH, IMAGE_HEIGHT, 0, GL_RGB, GL_FLOAT, NULL);
    glBindTexture(GL_TEXTURE_2D, 0);

    mirrorCreated = false;
}


void Reflection::onObjectAdd() {
    mirrorCreated = false;
}


void drawRect()
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

        // Create VBO with (x,y,z) coordinates
        float coords[] = { -1, -1, 0, 
                            1, -1, 0, 
                           -1,  1, 0, 
                            1,  1, 0};

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

void Reflection::drawMirror()
{
    static GLuint VAO_rect;
    
    // 1. Create VBO Buffers
    if (!mirrorCreated)
    {
        mirrorCreated = true;
        cout << "mirror drawn!" << endl;

        // Create & bind empty VAO
        glGenVertexArrays(1, &VAO_rect);
        glBindVertexArray(VAO_rect);

        Point min = scene()->boundingBox().min();
        Point max = scene()->boundingBox().max();

        float a = 1.5;
        float xmin = min.x()*a;
        float ymin = min.y();
        float zmin = min.z()*a;
        float xmax = max.x()*a;
        float zmax = max.z()*a;

        // Create VBO with (x,y,z) coordinates
        float coords[] = { xmin, ymin, zmin,
                           xmax, ymin, zmin,
                           xmin, ymin, zmax,
                           xmax, ymin, zmax };

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


QMatrix4x4 reflectionMatrix(QVector4D plane) {
  float a = plane.x();
  float b = plane.y();
  float c = plane.z();
  float d = plane.w();
  
  return QMatrix4x4(
       1-2*a*a, -2*b*a,   -2*c*a,   -2*d*a,
      -2*b*a,    1-2*b*b, -2*c*b,   -2*d*b,
      -2*c*a,   -2*c*b,    1-2*c*c, -2*d*c,
       0,        0,        0,        1
  );
}


bool Reflection::paintGL()
{    
    glClearColor(1,1,1,1);
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    program->bind();

    // Update clipping planes
    Box b = scene()->boundingBox();
    float r = b.radius();
    float a = 2;
    b.expand(Box(b.min()-a*QVector3D(r,r,r), b.max()+a*QVector3D(r,r,r)));
    camera()->updateClippingPlanes(b);
  
    // Step 1: draw mirrored scene in a texture 
    float d = scene()->boundingBox().min().y();
    QVector4D plane = QVector4D(0,-1,0,d);
    QMatrix4x4 MVP = camera()->projectionMatrix() * camera()->modelviewMatrix();
    program->setUniformValue("useTexture", false);
    program->setUniformValue("modelViewProjectionMatrix", MVP * reflectionMatrix(plane));
    drawPlugin()->drawScene();

    // Get texture
    glBindTexture(GL_TEXTURE_2D, textureId);
    glCopyTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 0, 0, IMAGE_WIDTH, IMAGE_HEIGHT); // copies from back buffer
    glGenerateMipmap(GL_TEXTURE_2D);
    
    // Clear framebuffer
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

    // Step 2: draw scene
    program->setUniformValue("useTexture", false);
    program->setUniformValue("modelViewProjectionMatrix", MVP);
    drawPlugin()->drawScene();
    
    // Step 3: Draw textured mirror
    program->setUniformValue("useTexture", true);
    program->setUniformValue("colorMap", 0);
    program->setUniformValue("SIZE", float(IMAGE_WIDTH));
    program->setUniformValue("modelViewProjectionMatrix", MVP);
    drawMirror();
    
    program->release();
    glBindTexture(GL_TEXTURE_2D, 0);

    return true;
}

Q_EXPORT_PLUGIN2(reflection, Reflection)   // plugin name, plugin class
