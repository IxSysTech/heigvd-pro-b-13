#include "emitteracgt.h"

EmitterACGT::EmitterACGT(char* text, QObject *parent) : QObject(parent)
{
    this->seq = text;
    int count = 0;
    while(seq[count]){
        ++count;
    }
    this->seqLength = count;
}

void EmitterACGT::beginAnalysis(){
    for(int i = 0; i < this->seqLength; ++i){
        switch(this->seq[i]){
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
            std::cout << "Erreur de lecture" << std::endl;
        }
    }
}
