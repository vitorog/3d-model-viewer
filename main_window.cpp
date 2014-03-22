#include "main_window.h"
#include "ui_main_window.h"

#include <QFileDialog>

#include "scene_loader.h"
#include "gl_widget.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    current_model_(NULL)
{
    ui->setupUi(this);
    gl_widget_ = new GLWidget();
    ui->horizontalLayout->addWidget(gl_widget_);
    QObject::connect(ui->actionOpen,SIGNAL(triggered()),this,SLOT(OpenFile()));
    QObject::connect(ui->actionExit,SIGNAL(triggered()),this,SLOT(Exit()));
    this->setWindowTitle("Wavefront viewer");
}

MainWindow::~MainWindow()
{
    if(current_model_ != NULL){
        delete current_model_;
    }
    delete ui;
}

void MainWindow::OpenFile()
{
    QString file_names = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                      "/home",
                                                      tr("Wavefront files (*.obj)"));
    if(!file_names.isEmpty()){
        if(current_model_ != NULL){
            delete current_model_;
        }
        current_model_ = new SceneLoader();
        if(current_model_->Load(file_names.toStdString()) == 0){
            gl_widget_->SetScene(current_model_);
            gl_widget_->Reload();
        }else{
            qDebug() << "Failed to load file.";
        }
    }
}

void MainWindow::Exit()
{
    QApplication::exit(0);
}
