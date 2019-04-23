#include "emitteracgt.h"

emitterACGT::emitterACGT(const std::map<std::string, bool> &sequences, QObject *parent) : QObject(parent), sequences(sequences){}

void emitterACGT::beginAnalysis(){
    for(const std::pair<std::string, bool> sequence : sequences) {
        currentResult = sequence.second;
        size_t lengthStr = sequence.first.length();
        for(size_t i = 0; i < lengthStr; ++i){
            switch(sequence.first.at(i)){
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
        emit finishedSequence();
        emit nextSequence();
    }
    // emit finished();
}

bool emitterACGT::getCurrentResult(){
    return this->currentResult;
}
