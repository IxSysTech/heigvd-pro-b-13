#include "task.h"
#include <QTextStream>

Task::Task(QObject * parent) : QObject(parent)
{
    buildStateMachine();
}

void Task::buildStateMachine()
{
    QState *s1 = new QState(&machine);
    QState *s2 = new QState(&machine);
    QState *s3 = new QState(&machine);

    s1->addTransition(this, SIGNAL(A()), s2);
    s1->addTransition(this, SIGNAL(C()), s1);
    s1->addTransition(this, SIGNAL(G()), s3);
    s1->addTransition(this, SIGNAL(T()), s2);

    s2->addTransition(this, SIGNAL(A()), s1);
    s2->addTransition(this, SIGNAL(C()), s3);
    s2->addTransition(this, SIGNAL(G()), s2);
    s2->addTransition(this, SIGNAL(T()), s3);

    s3->addTransition(this, SIGNAL(A()), s2);
    s3->addTransition(this, SIGNAL(C()), s3);
    s3->addTransition(this, SIGNAL(G()), s1);
    s3->addTransition(this, SIGNAL(T()), s2);

    connect(s1, &QState::entered, this, &Task::runS1);
    connect(s2, &QState::entered, this, &Task::runS2);
    connect(s3, &QState::entered, this, &Task::runS3);

    machine.setInitialState(s1);

    machine.start();
}


void Task::run()
{
       QTextStream qin(stdin);
       QTextStream out(stdout);

       std::cout << "line: ";
       QString line = qin.readLine();

       if (line == "A")
       {
           std::cout << "emit A signal" << std::endl;
           emit A();
       }
       else if(line == "C"){
           std::cout << "emit C signal" << std::endl;
           emit C();
       }
       else if(line == "G"){
           std::cout << "emit G signal" << std::endl;
           emit G();
       }
       else if(line == "T"){
           std::cout << "emit T signal" << std::endl;
           emit T();
       }
       else if (line == "q")
       {
           emit finished();
       }
       else
       {
           run();
       }
}

void Task::runS1()
{
    std::cout << "entered state S1" << std::endl;
    run();
}

void Task::runS2()
{
    std::cout << "entered state S2" << std::endl;
    run();
}

void Task::runS3()
{
    std::cout << "entered state S3" << std::endl;
    run();
}

void Task::debugSlot()
{
    std::cout << "debug slot was triggered!" << std::endl;
    run();
}
