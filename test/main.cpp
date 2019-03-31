#include <QCoreApplication>
#include <iostream>
#include "statetest.h"
#include "emitteracgt.h"
#include "handler.h"
#include "megamachine.h"
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    /* if(argc < 2){
        cout << "Not enough args\n" << endl;
    }*/
    /*
    char* testSeq = "ACTGACTACGTACTG";
    EmitterACGT *theEmitter = new EmitterACGT(testSeq);
    handler *theHandler = new handler();
    StateTest *theMachines = new StateTest(10, 5, theEmitter, theHandler);
    theMachines->runMachines();
    theEmitter->beginAnalysis();
    */
    char* testSeq = "ACTGACTACGTACTG";
    EmitterACGT *theEmitter = new EmitterACGT(testSeq);
    QString fileName = "test.scxml";
    MegaMachine *theMachine = new MegaMachine(&fileName);
    cout << theMachine->machine->isRunning() << endl;
    theEmitter->beginAnalysis();
}
