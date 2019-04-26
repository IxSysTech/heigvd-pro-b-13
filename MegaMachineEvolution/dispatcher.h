#ifndef DISPATCHER_H
#define DISPATCHER_H

#include <QObject>
#include "GALGO/Galgo.hpp"

class Dispatcher : public QObject
{
    Q_OBJECT
public:
    explicit Dispatcher(QObject *parent = nullptr);
    int main();
    template <typename T>
    static std::vector<T> objective(const std::vector<T>& x);
signals:

public slots:
};

#endif // DISPATCHER_H
