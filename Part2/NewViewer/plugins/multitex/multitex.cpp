#include "multitex.h"
#include <QFileDialog>
 
void Multitex::onPluginLoad()
{
    // VS
    vs = new QGLShader(QGLShader::Vertex, this);
    vs->compileSourceFile("multitex.vert");

    // FS
    fs = new QGLShader(QGLShader::Fragment, this);
    fs->compileSourceFile("multitex.frag");

	// Program  
  	program = new QGLShaderProgram(this);
    program->addShader(vs);
	program->addShader(fs);
	program->link();
    cout << "Link log:" << program->log().toStdString() << endl;

	// Load Texture 1
	glActiveTexture(GL_TEXTURE0);
	QString filename = QFileDialog::getOpenFileName(0, "Open Image", "/assig/grau-g/Textures", "Image file (*.png *.jpg)");	
	QImage img0(filename);	
	QImage im0 = QGLWidget::convertToGLFormat(img0);
    glGenTextures(1, &textureId0);
	glBindTexture(GL_TEXTURE_2D, textureId0);
	glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, im0.width(), im0.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, im0.bits());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	glBindTexture(GL_TEXTURE_2D, 0);

	// Load Texture 2
	glActiveTexture(GL_TEXTURE1);
	QString filename2 = QFileDialog::getOpenFileName(0, "Open Image 2", "/assig/grau-g/Textures", "Image file (*.png *.jpg)");	
	QImage img1(filename2);	
	QImage im1 = QGLWidget::convertToGLFormat(img1);
    glGenTextures(1, &textureId1);
	glBindTexture(GL_TEXTURE_2D, textureId1);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, im1.width(), im1.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, im1.bits());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Multitex::preFrame() 
{
    // bind shader and define uniforms
    program->bind();
    program->setUniformValue("sampler0", 0);  // texture unit del primer sampler 
    program->setUniformValue("sampler1", 1);  // texture unit del segon  sampler
    program->setUniformValue("radius", float(scene()->boundingBox().radius()));  // radi d'una esfera que engloba l'escena
    QMatrix4x4 MVP = camera()->projectionMatrix() * camera()->modelviewMatrix();
    program->setUniformValue("modelViewProjectionMatrix", MVP); 

    // bind textures
	glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureId0);
	glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, textureId1);
}

void Multitex::postFrame() 
{
    // unbind shader
    program->release();
   	// unbind textures
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, 0);
	glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, 0);
}

Q_EXPORT_PLUGIN2(multitex, Multitex)   // plugin name, plugin class
