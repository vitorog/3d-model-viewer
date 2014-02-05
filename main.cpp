#include "main_window.h"
#include <QApplication>

#include "model.h"

int main(int argc, char *argv[])
{
    Model m;
    int ret = m.Load("test_model/capsule.obj");
    return ret;
//    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();

//    return a.exec();
}
