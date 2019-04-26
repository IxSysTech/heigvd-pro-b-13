#include "GUI/mainwindow.h"
#include "dispatcher.h"
#include <QApplication>
#include <QTimer>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    /*
    MainWindow w;
    w.show();
    */

    // Task parented to the application so that it
    // will be deleted by the application.
    //Task *task = new Task(&a);
    Dispatcher *DISPATCHER = new Dispatcher(&a);

    // This will cause the application to exit when
    // the task signals finished.
     //QObject::connect(task, SIGNAL(finished()), &a, SLOT(quit()));
     QObject::connect(DISPATCHER, SIGNAL(finished()), &a, SLOT(quit()));

    // This will run the task from the application event loop.
    //QTimer::singleShot(0, task, SLOT(run()));

    //QObject::connect(task, &Task::finished, &a, &QCoreApplication::quit, Qt::QueuedConnection);
    //QTimer::singleShot(0, task, &Task::run);
    QTimer::singleShot(0, DISPATCHER, &Dispatcher::run);

    return a.exec();
}
