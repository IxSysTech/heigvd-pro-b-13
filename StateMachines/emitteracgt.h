#ifndef EMITTERACGT_H
#define EMITTERACGT_H

#include <QObject>

class emitterACGT : public QObject
{
    Q_OBJECT
public:
    explicit emitterACGT(QString sequence, QObject *parent = nullptr);
    void beginAnalysis();
private:
    QString sequence;
signals:
    void readA();
    void readC();
    void readG();
    void readT();
public slots:
};

#endif // EMITTERACGT_H
