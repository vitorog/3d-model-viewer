#include "gl_widget.h"

#include <QMouseEvent>
#include <QImage>

#include "model.h"

#include <GL/glu.h>

GLWidget::GLWidget(QWidget *parent) :
    QGLWidget(parent),
    model_(NULL)
{    
    xRot = 0;
    yRot = 0;
    zRot = 0;
}

static void qNormalizeAngle(int &angle)
{
    while (angle < 0)
        angle += 360 * 16;
    while (angle > 360 * 16)
        angle -= 360 * 16;
}

void GLWidget::setXRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != xRot) {
        xRot = angle;
        emit xRotationChanged(angle);
        updateGL();
    }
}

void GLWidget::setYRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != yRot) {
        yRot = angle;
        emit yRotationChanged(angle);
        updateGL();
    }
}

void GLWidget::setZRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != zRot) {
        zRot = angle;
        emit zRotationChanged(angle);
        updateGL();
    }
}

void GLWidget::SetModel(Model *m)
{
    model_ = m;

}

//TODO: Create a GLSL renderer...
void GLWidget::initializeGL()
{
    glClearColor(0.3f,0.3f,0.3f,1.0f);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_MULTISAMPLE);
    static GLfloat lightPosition[4] = { 0.0, 0.0, 1.0, 1.0 };
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

    LoadModelTexture();
}

void GLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(0.0f,0.0f,0.0f,0.0f,0.0f,-1.0f,0.0f,1.0f,0.0f);
    glTranslatef(0.0f,0.0f,-5.0f);
    //    glTranslatef(model_->center_.x,model_->center_.y,model_->center_.z);
    glRotatef(xRot / 16.0, 1.0, 0.0, 0.0);
    glRotatef(yRot / 16.0, 0.0, 1.0, 0.0);
    glRotatef(zRot / 16.0, 0.0, 0.0, 1.0);
    //    glTranslatef(-model_->center_.x,-model_->center_.y,-model_->center_.z);
    RenderModel();
}

void GLWidget::resizeGL(int width, int height)
{
    int side = qMin(width, height);
    glViewport((width - side) / 2, (height - side) / 2, side, side);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f,double(width)/double(height),1.0f,20.0f);
    glMatrixMode(GL_MODELVIEW);
    gluLookAt(0.0f,0.0f,0.0f,0.0f,0.0f,-1.0f,0.0f,1.0f,0.0f);
}

//Temporary render function for testing purposes
void GLWidget::RenderModel()
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture( GL_TEXTURE_2D, texture_ids_[0] );
    if(model_ != NULL){

        if(model_->tri_faces_){
            glBegin(GL_TRIANGLES);
        }else{
            glBegin(GL_QUADS);
        }
        std::vector<int>::iterator text_coord_it = model_->text_coords_index_.begin();
        for(std::vector<int>::iterator vert_it = model_->vertices_index_.begin();
            vert_it != model_->vertices_index_.end();
            vert_it++, text_coord_it++)
        {
            glm::vec2 text_coords = model_->text_coords_.at((*text_coord_it) - 1);
            glTexCoord2f(text_coords.x,text_coords.y);
            glm::vec3 v = model_->vertices_.at((*vert_it) - 1);
            glVertex3f(v.x,v.y,v.z);
        }

        glEnd();
    }else{
        glBegin(GL_QUADS);
        glTexCoord2f(0.0f,0.0f);
        glVertex3f(0.0f,0.0f,0.0f);
        glTexCoord2f(1.0f,0.0f);
        glVertex3f(1.0f,0.0f,0.0f);
        glTexCoord2f(1.0f,1.0f);
        glVertex3f(1.0f,1.0f,0.0f);
        glTexCoord2f(0.0f,1.0f);
        glVertex3f(0.0f,1.0f,0.0f);
        glEnd();
    }
}

void GLWidget::LoadModelTexture()
{
    if(model_ != NULL){
        for(std::vector<Material>::iterator it = model_->materials_.begin();
            it != model_->materials_.end();
            it++){

            QString texture_path = QString::fromStdString(model_->model_dir_) + QString::fromStdString((*it).map_kd_);
            QImage texture = QGLWidget::convertToGLFormat(QImage(texture_path));

            GLuint texture_id;
            glGenTextures(1,&texture_id);
            glBindTexture( GL_TEXTURE_2D, texture_id );
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture.width(), texture.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, texture.bits());
            glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
            glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

            texture_ids_.push_back(texture_id);
        }
    }
}

void GLWidget::mousePressEvent(QMouseEvent *event)
{
    lastPos = event->pos();
}

void GLWidget::mouseMoveEvent(QMouseEvent *event)
{
    int dx = event->x() - lastPos.x();
    int dy = event->y() - lastPos.y();

    if (event->buttons() & Qt::LeftButton) {
        setXRotation(xRot + 8 * dy);
        setYRotation(yRot + 8 * dx);
    } else if (event->buttons() & Qt::RightButton) {
        setXRotation(xRot + 8 * dy);
        setZRotation(zRot + 8 * dx);
    }
    lastPos = event->pos();
}
