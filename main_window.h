#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>

class GLWidget;
class SceneLoader;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
public slots:
    void OpenFile();
    void Exit();
private:
    Ui::MainWindow *ui;
    GLWidget *gl_widget_;
    SceneLoader* current_model_;
};

#endif // MAIN_WINDOW_H
