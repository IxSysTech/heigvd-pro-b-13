#include "mainwindow.h"
#include "parameterwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    /*MainWindow w;
    w.show();*/

    ParameterWindow p;
    p.show();

    return a.exec();
}
