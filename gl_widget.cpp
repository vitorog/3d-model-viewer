#include "gl_widget.h"

#include <QMouseEvent>

#include "model.h"

#include <GL/glu.h>

GLWidget::GLWidget(QWidget *parent) :
    QGLWidget(parent),
    model_(NULL)
{    
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
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_MULTISAMPLE);
    static GLfloat lightPosition[4] = { 0.0, 0.0, 1.0, 1.0 };
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
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
    if(model_ != NULL){
        if(model_->tri_faces_){
            glBegin(GL_TRIANGLES);
        }else{
            glBegin(GL_QUADS);
        }
        for(std::vector<int>::iterator it = model_->vertices_index_.begin();
            it != model_->vertices_index_.end();
            it++)
        {
            glm::vec3 v = model_->vertices_.at((*it) - 1);
            glVertex3f(v.x,v.y,v.z);
        }

        glEnd();
    }else{
        glBegin(GL_TRIANGLES);
        glVertex3f(0.0f,0.0f,0.0f);
        glVertex3f(1.0f,0.0f,0.0f);
        glVertex3f(1.0f,1.0f,0.0f);
        glEnd();
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
