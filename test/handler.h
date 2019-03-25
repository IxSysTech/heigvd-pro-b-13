#ifndef HANDLER_H
#define HANDLER_H
#include <qglobal.h>
#include <QObject>
#include <iostream>

class handler
{
public:
    handler();
public slots:
    void getStates(int state);
};

#endif // HANDLER_H
