#include "dispatcher.h"

Dispatcher::Dispatcher(QObject *parent) : QObject(parent)
{
    //TODO: Receive all the configs necessary to the statemachines and the genetical algorithm
}

int Dispatcher::main() {
    //Test with hardcoded params
    galgo::Parameter<double,64> par1({0.0,3000000000.0});
    galgo::Parameter<double,64> par2({0.0,3000000000.0});
    galgo::Parameter<double,64> par3({0.0,3000000000.0});
    galgo::Parameter<double,64> par4({0.0,3000000000.0});
    galgo::Parameter<double,64> par5({0.0,3000000000.0});
    galgo::Parameter<double,64> par6({0.0,3000000000.0});
    galgo::Parameter<double,64> par7({0.0,3000000000.0});
    galgo::Parameter<double,64> par8({0.0,3000000000.0});

    // initiliazing genetic algorithm
    galgo::GeneticAlgorithm<double> ga(Dispatcher::objective<double>,2,10000,true,par1,par2,par3,par4,par5,par6,par7,par8);

    // running genetic algorithm
    ga.run();
    return EXIT_FAILURE;
}

template <typename T>
std::vector<T> Dispatcher::objective(const std::vector<T>& x){
    T obj = 0;
    for (T curr : x){
        obj += curr;
    }
    return {obj};
}
