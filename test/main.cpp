#include <QCoreApplication>
#include <iostream>
#include "statetest.h"
#include "emitteracgt.h"

using namespace std;

int main(int argc, char *argv[])
{
    /* if(argc < 2){
        cout << "Not enough args\n" << endl;
    }*/
    char* testSeq = "ACTGACTACGTACTG";
    EmitterACGT *theEmitter = new EmitterACGT(testSeq);
    StateTest *theMachines = new StateTest(1, 5, theEmitter);
    theMachines->runMachines();
    theEmitter->beginAnalysis();
}
