#ifndef GL_WIDGET_H
#define GL_WIDGET_H

#include <QGLWidget>


class SceneLoader;

class GLWidget : public QGLWidget
{
    Q_OBJECT
public:
    explicit GLWidget(QWidget *parent = 0);
    void SetScene(SceneLoader* m);
    void Reload();
signals:
    void xRotationChanged(int angle);
    void yRotationChanged(int angle);
    void zRotationChanged(int angle);

public slots:
    void setXRotation(int angle);
    void setYRotation(int angle);
    void setZRotation(int angle);

protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);

    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
private:
    void RenderScene();
    void LoadSceneTextures();

    SceneLoader *scene_;
    int xRot;
    int yRot;
    int zRot;
    QPoint lastPos;

    std::vector<GLuint> texture_ids_;
};

#endif // GL_WIDGET_H
