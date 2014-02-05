#ifndef GL_WIDGET_H
#define GL_WIDGET_H

#include <QGLWidget>

class Model;

class GLWidget : public QGLWidget
{
    Q_OBJECT
public:
    explicit GLWidget(QWidget *parent = 0);
    void SetModel(Model* m);
signals:

public slots:

protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);
private:
    void RenderModel();

    Model *model_;
};

#endif // GL_WIDGET_H
