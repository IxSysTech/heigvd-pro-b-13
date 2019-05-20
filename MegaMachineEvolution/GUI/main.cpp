#include "mainwindow.h"
#include "parameterwindow.h"
#include <QApplication>
#include <QStandardPaths>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    QDir(QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation)).mkpath(".");

    return a.exec();
}
