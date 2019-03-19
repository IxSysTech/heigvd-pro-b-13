#ifndef EMITTERACGT_H
#define EMITTERACGT_H

#include <QObject>
#include <iostream>

class EmitterACGT : public QObject
{
    Q_OBJECT
public:
    explicit EmitterACGT(char* text, QObject *parent = nullptr);
    void beginAnalysis();
private:
    int seqLength;
    char* seq;
signals:
    void readA();
    void readC();
    void readG();
    void readT();
public slots:
};

#endif // EMITTERACGT_H
