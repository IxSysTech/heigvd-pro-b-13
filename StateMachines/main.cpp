#include <QCoreApplication>
#include <QTimer>
// #include "task.h"
#include "megamachinemanager.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    // Task parented to the application so that it
    // will be deleted by the application.
    //Task *task = new Task(&a);
    MegaMachineManager *manager = new MegaMachineManager(&a);

    // This will cause the application to exit when
    // the task signals finished.
     //QObject::connect(task, SIGNAL(finished()), &a, SLOT(quit()));
     QObject::connect(manager, SIGNAL(finished()), &a, SLOT(quit()));

    // This will run the task from the application event loop.
    //QTimer::singleShot(0, task, SLOT(run()));

    //QObject::connect(task, &Task::finished, &a, &QCoreApplication::quit, Qt::QueuedConnection);
    //QTimer::singleShot(0, task, &Task::run);
    QTimer::singleShot(0, manager, &MegaMachineManager::runMachines);

    return a.exec();
}
