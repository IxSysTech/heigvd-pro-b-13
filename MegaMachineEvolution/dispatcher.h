#ifndef DISPATCHER_H
#define DISPATCHER_H

#include <QObject>

union converter {
    double value;
    uint64_t converted;
};

class Dispatcher : public QObject
{
    Q_OBJECT
public:
    explicit Dispatcher(QObject *parent = nullptr);
    void run();
    template <typename T>
    static std::vector<T> objective(const std::vector<T>& x);
signals:
    void finished();
public slots:
};

#endif // DISPATCHER_H
