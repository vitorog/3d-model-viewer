#include "main_window.h"
#include <QApplication>

#include "../shade-framework/scene_loader.h"

#include <iostream>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    setlocale(LC_ALL,"C"); //Qt was changing the locale which caused the atof function to expect commas instead of points...
    MainWindow w;
    w.show();
    return a.exec();
}
