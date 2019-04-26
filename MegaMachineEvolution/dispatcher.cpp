#include "dispatcher.h"
#include "Galgo.hpp"

Dispatcher::Dispatcher(QObject *parent) : QObject(parent)
{
    //TODO: Receive all the configs necessary to the statemachines and the genetical algorithm
}

void Dispatcher::run() {

    //Test with hardcoded params
    galgo::Parameter<double,64> par1({0.0,300.0});
    galgo::Parameter<double,64> par2({0.0,300.0});
    galgo::Parameter<double,64> par3({0.0,300.0});
    galgo::Parameter<double,64> par4({0.0,300.0});
    galgo::Parameter<double,64> par5({0.0,300.0});
    galgo::Parameter<double,64> par6({0.0,300.0});
    galgo::Parameter<double,64> par7({0.0,300.0});
    galgo::Parameter<double,64> par8({0.0,300.0});

    // initiliazing genetic algorithm
    galgo::GeneticAlgorithm<double> ga(Dispatcher::objective<double>,2,500,true,par1,par2,par3,par4,par5,par6,par7,par8);

    // running genetic algorithm
    ga.run();
    emit finished();
}

template <typename T>
std::vector<T> Dispatcher::objective(const std::vector<T>& x){
    T obj = x[0] + x[1] + x[2] + x[3] + x[4] + x[5] + x[6] + x[7];
    return {obj};
}
