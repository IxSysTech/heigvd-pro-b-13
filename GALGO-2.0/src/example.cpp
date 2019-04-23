//=================================================================================================
//                    Copyright (C) 2017 Olivier Mallet - All Rights Reserved                      
//=================================================================================================

#include "Galgo.hpp"

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
   // NB: GALGO maximize by default so we will maximize -f(x,y)
};

// constraints example:
// 1) x * y + x - y + 1.5 <= 0
// 2) 10 - x * y <= 0
/*template <typename T>
std::vector<T> MyConstraint(const std::vector<T>& x)
{
   return {x[0]*x[1]+x[0]-x[1]+1.5,10-x[0]*x[1]};
}*/
// NB: a penalty will be applied if one of the constraints is > 0 
// using the default adaptation to constraint(s) method

int main(int argc, char* [])
{
   // initializing parameters lower and upper bounds
   // an initial value can be added inside the initializer list after the upper bound

   int nbParams;
   std::cout << "Please give the number of parameters : ";
   std::cin >> nbParams;

   /*for(int i = 0 ; i < nbParams ; ++i){
      galgo::Parameter<double,64> par;
   }*/

   galgo::Parameter<double,64> par1({0.0,30.0});
   galgo::Parameter<double,64> par2({0.0,30.0});
   galgo::Parameter<double,64> par3({0.0,30.0});
   galgo::Parameter<double,64> par4({0.0,30.0});
   galgo::Parameter<double,64> par5({0.0,30.0});
   galgo::Parameter<double,64> par6({0.0,30.0});
   galgo::Parameter<double,64> par7({0.0,30.0});
   galgo::Parameter<double,64> par8({0.0,30.0});

   // here both parameter will be encoded using 16 bits the default value inside the template declaration
   // this value can be modified but has to remain between 1 and 64

   // initiliazing genetic algorithm
   galgo::GeneticAlgorithm<double> ga(MyObjective<double>::Objective,2,100,true,par1,par2,par3,par4,par5,par6,par7,par8);

   // setting constraints
   //ga.Constraint = MyConstraint;

   // running genetic algorithm
   ga.run();
}
