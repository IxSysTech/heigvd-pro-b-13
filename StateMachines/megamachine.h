#ifndef MEGAMACHINE_H
#define MEGAMACHINE_H
#include <QScxmlStateMachine>
#include <QIODevice>
#include <QTextStream>

class MegaMachine : public QObject
{
    Q_OBJECT
public:
    explicit MegaMachine(const QString *filename, QObject *parent = nullptr);
    QScxmlStateMachine *machine;
};

#endif // MEGAMACHINE_H
