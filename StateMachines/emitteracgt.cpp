#include "emitteracgt.h"

emitterACGT::emitterACGT(const std::string &sequence, QObject *parent) : QObject(parent), sequence(sequence){}

void emitterACGT::beginAnalysis(){
    size_t lengthStr = this->sequence.length();
    for(size_t i = 0; i < lengthStr; ++i){
        switch(sequence[i]){
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
        default:
            emit readX();
        }
    }
}
