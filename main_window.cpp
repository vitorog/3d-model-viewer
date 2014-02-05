#include "main_window.h"
#include "ui_main_window.h"

#include "model.h"
#include "gl_widget.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    gl_widget_ = new GLWidget();
    ui->horizontalLayout->addWidget(gl_widget_);
    Model* m = new Model();
    if(m->Load("test_model/capsule.obj") == 0){
        gl_widget_->SetModel(m);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
