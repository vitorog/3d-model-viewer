#include "gl_widget.h"

#include "model.h"

GLWidget::GLWidget(QWidget *parent) :
    QGLWidget(parent),
    model_(NULL)
{    
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
    static GLfloat lightPosition[4] = { 0.5, 5.0, 7.0, 1.0 };
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
}

void GLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    RenderModel();
}

void GLWidget::resizeGL(int width, int height)
{
    int side = qMin(width, height);
    glViewport((width - side) / 2, (height - side) / 2, side, side);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
}

//Temporary render function for testing purposes
void GLWidget::RenderModel()
{
    if(model_ != NULL){
        if(model_->tri_faces_){
            glBegin(GL_POINTS);
        }else{
            glBegin(GL_QUADS);
        }
        for(std::vector<glm::vec3>::iterator it = model_->vertices_.begin();
            it != model_->vertices_.end();
            it++)
        {
            glm::vec3 v = (*it);
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
