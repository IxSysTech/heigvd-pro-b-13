#include "emitteracgt.h"

emitterACGT::emitterACGT(QString sequence, QObject *parent) : sequence(sequence),QObject(parent)
{

}

void emitterACGT::beginAnalysis(){
    for(QChar c : this->sequence){
        char temp = (char) c.toLatin1();
        switch(temp){
        case 'A':
            emit readA();
            break;
        case 'C':
            emit readC();
            break;
        case 'G':
            emit readG();
            break;
        case 'T':
            emit readT();
            break;
        }
    }
}
