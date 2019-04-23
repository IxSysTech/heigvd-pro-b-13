#ifndef EMITTERACGT_H
#define EMITTERACGT_H

#include <QObject>

class emitterACGT : public QObject
{
    Q_OBJECT
public:
    explicit emitterACGT(const std::map<std::string, bool> &sequences, QObject *parent = nullptr);
    void beginAnalysis();
    bool getCurrentResult();
private:
    const std::map<std::string, bool> &sequences;
    bool currentResult;
signals:
    void readA();
    void readC();
    void readG();
    void readT();
    void readX();
    void nextSequence();
    void finishedSequence();
    void finished();
public slots:
};

#endif // EMITTERACGT_H
