//=================================================================================================
//                    Copyright (C) 2017 Olivier Mallet - All Rights Reserved                      
//=================================================================================================

#include "Galgo.hpp"
#include "Chromosome.hpp"

// objective class example
template <typename T>
class MyObjective
{
public:
   //The objective is to have the greatest result from f(x)
   static std::vector<T> Objective(const std::vector<T>& x)
   {
      T obj = x[0]+x[1]+x[2]+x[3]+x[4]+x[5]+x[6]+x[7];
      return {obj};
   }

};


int main(int argc, char* [])
{
   //Test with hardcoded param
   galgo::Parameter<double,64> par1({0.0,3000000000.0});
   galgo::Parameter<double,64> par2({0.0,3000000000.0});
   galgo::Parameter<double,64> par3({0.0,3000000000.0});
   galgo::Parameter<double,64> par4({0.0,3000000000.0});
   galgo::Parameter<double,64> par5({0.0,3000000000.0});
   galgo::Parameter<double,64> par6({0.0,3000000000.0});
   galgo::Parameter<double,64> par7({0.0,3000000000.0});
   galgo::Parameter<double,64> par8({0.0,3000000000.0});

   // initiliazing genetic algorithm
   galgo::GeneticAlgorithm<double> ga(MyObjective<double>::Objective,2,10000,true,par1,par2,par3,par4,par5,par6,par7,par8);

   // running genetic algorithm
   ga.run();
}
