#ifndef MEGAMACHINE_H
#define MEGAMACHINE_H
#include <QScxmlStateMachine>

class MegaMachine : public QObject
{
    Q_OBJECT
public:
    explicit MegaMachine(QString filename, QObject *parent = nullptr);

signals:

public slots:
};

#endif // MEGAMACHINE_H
