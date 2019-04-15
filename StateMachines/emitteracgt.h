#ifndef EMITTERACGT_H
#define EMITTERACGT_H

#include <QObject>

class emitterACGT : public QObject
{
    Q_OBJECT
public:
    explicit emitterACGT(const std::string &sequence, QObject *parent = nullptr);
    void beginAnalysis();
private:
    std::string sequence;
signals:
    void readA();
    void readC();
    void readG();
    void readT();
    void readX();
public slots:
};

#endif // EMITTERACGT_H
