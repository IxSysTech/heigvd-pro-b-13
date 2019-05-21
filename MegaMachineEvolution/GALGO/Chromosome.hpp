//=================================================================================================
//                    Copyright (C) 2017 Olivier Mallet - All Rights Reserved                      
//=================================================================================================

#ifndef CHROMOSOME_HPP
#define CHROMOSOME_HPP

namespace galgo {

//=================================================================================================

template <typename T>
class Chromosome
{
   static_assert(std::is_same<float,T>::value || std::is_same<double,T>::value, "variable type can only be float or double, please amend.");

public:
   // constructor
   Chromosome(const GeneticAlgorithm<T>& ga);
   // copy constructor
   Chromosome(const Chromosome<T>& rhs);
   // create new chromosome 
   void create();
   // initialize chromosome
   void initialize();
   // evaluate chromosome 
   void evaluate(); 
   // reset chromosome
   void reset();
   // set or replace kth gene by a new one
   void setGene(int k);
   // initialize or replace kth gene by a know value
   void initGene(int k, T value);
   // add bit to chromosome
   void addBit(char bit);
   // initialize or replace an existing chromosome bit   
   void setBit(char bit, int pos);
   // flip an existing chromosome bit
   void flipBit(int pos);
   // get chromosome bit
   char getBit(int pos) const;
   // initialize or replace a portion of bits with a portion of another chromosome
   void setPortion(const Chromosome<T>& x, int start, int end);
   // initialize or replace a portion of bits with a portion of another chromosome
   void setPortion(const Chromosome<T>& x, int start);
   // get parameter value(s) from chromosome
   const std::vector<T>& getParam() const;
   // get objective function result
   const std::vector<T>& getResult() const;
   // get the total sum of all objective function(s) result
   T getTotal() const;
   // get constraint value(s)
   const std::vector<T> getConstraint() const;
   // return chromosome size in number of bits
   int size() const;
   // return number of chromosome bits to mutate
   T mutrate() const;
   // return number of genes in chromosome
   int nbgene() const;
   // return numero of generation this chromosome belongs to
   int nogen() const;
   // return lower bound(s)
   const std::vector<T>& lowerBound() const;
   // return upper bound(s)
   const std::vector<T>& upperBound() const;

private:
   std::vector<T> param;                     // estimated parameter(s)
   std::vector<T> result;                    // chromosome objective function(s) result
   std::string chr;                          // string of bits representing chromosome
   const GeneticAlgorithm<T>* ptr = nullptr; // pointer to genetic algorithm
public:
   T fitness;                                // chromosome fitness, objective function(s) result that can be modified (adapted to constraint(s), set to positive values, etc...)
private:
   T total;                                  // total sum of objective function(s) result
   int chrsize;                              // chromosome size (in number of bits)
   int numgen;                               // numero of generation
};

/*-------------------------------------------------------------------------------------------------*/

/**
 * @brief Constructor of Chromosome
 * @param ga instance of current GeneticAlgorithm
 */
template <typename T>
Chromosome<T>::Chromosome(const GeneticAlgorithm<T>& ga) 
{
   param.resize(ga.nbparam);
   ptr = &ga;
   chrsize = ga.nbbit;
   numgen = ga.nogen;
}

/*-------------------------------------------------------------------------------------------------*/

/**
 * @brief Constructor of copy
 * @param rhs chromosome to copy
 */
template <typename T>
Chromosome<T>::Chromosome(const Chromosome<T>& rhs) 
{
   param = rhs.param;
   result = rhs.result;
   chr = rhs.chr;
   ptr = rhs.ptr;
   // re-initializing fitness to its original value
   fitness = rhs.total;
   total = rhs.total;
   chrsize = rhs.chrsize;
   numgen = rhs.numgen;
}

/*-------------------------------------------------------------------------------------------------*/

/**
 * @brief Method which create a chromosome
 */
template <typename T>
inline void Chromosome<T>::create()
{
   chr.clear();
   for (const auto& x : ptr->param) {
      // encoding parameter random value

      std::string str = x->encode();
      chr.append(str);
   }

}

/*-------------------------------------------------------------------------------------------------*/

/**
 * @brief Initialize chromosome from known parameter values
 */
template <typename T>
inline void Chromosome<T>::initialize()
{
   chr.clear();

   int i(0);
   for (const auto& x : ptr->param) {
      // encoding parameter initial value
      std::string str = x->encode(ptr->initialSet[i++]);
      chr.append(str);
   }      
}

/*-------------------------------------------------------------------------------------------------*/

/**
 * @brief Evaluate chromosome fitness
 */
template <typename T>
inline void Chromosome<T>::evaluate() 
{
   int i(0);
   for (const auto& x : ptr->param) {
      // decoding chromosome: converting chromosome string into a real value
      param[i] = x->decode(chr.substr(ptr->idx[i], x->size()));
      i++;
   } 
   // computing objective result(s) 
   result = ptr->Objective(param);
   // computing sum of all results (in case there is not only one objective functions)
   total = std::accumulate(result.begin(), result.end(), 0.0);
   // initializing fitness to this total
   fitness = total;
}

/*-------------------------------------------------------------------------------------------------*/

/**
 * @brief set chromosome's value at 0 (result,total,fitness)
 */
template <typename T>
inline void Chromosome<T>::reset()
{
   chr.clear();
   result = 0.0;
   total = 0.0;
   fitness = 0.0;
}

/*-------------------------------------------------------------------------------------------------*/

/**
 * @brief Set or replace kth gene by a new one
 * @param k Kth position to set or replace
 */
template <typename T>
inline void Chromosome<T>::setGene(int k)
{
   #ifndef NDEBUG
   if (k < 0 || k >= ptr->nbparam) {
      throw std::invalid_argument("Error: in galgo::Chromosome<T>::setGene(int), argument cannot be outside interval [0,nbparam-1], please amend.");
   }
   #endif

   // generating a new gene
   std::string s = ptr->param[k]->encode();
   // adding or replacing gene in chromosome
   chr.replace(ptr->idx[k], s.size(), s, 0, s.size());
}

/*-------------------------------------------------------------------------------------------------*/

/**
 * @brief Initialize or replace kth gene by a know value
 * @param k Kth position to initialize or replace
 * @tparam x Value to encode
 */
template <typename T>
inline void Chromosome<T>::initGene(int k, T x)
{
   #ifndef NDEBUG
   if (k < 0 || k >= ptr->nbparam) {
      throw std::invalid_argument("Error: in galgo::Chromosome<T>::initGene(int), first argument cannot be outside interval [0,nbparam-1], please amend.");
   }
   #endif

   // encoding gene
   std::string s = ptr->param[k]->encode(x);
   // adding or replacing gene in chromosome
   chr.replace(ptr->idx[k], s.size(), s, 0, s.size());
}

/*-------------------------------------------------------------------------------------------------*/

/**
 * @brief Add chromosome bit to chromosome when we constructe a new one
 * @param bit New bit to add
 */
template <typename T>
inline void Chromosome<T>::addBit(char bit)
{
   chr.push_back(bit);

   #ifndef NDEBUG
   if (chr.size() > chrsize) {
      throw std::out_of_range("Error: in galgo::Chromosome<T>::setBit(char), exceeding chromosome size.");
   }
   #endif
}

/*-------------------------------------------------------------------------------------------------*/

/**
 * @brief Initialize or replace an existing chromosome bit
 * @param bit New bit to add
 * @param pos Position of the bit to replace
 */
template <typename T>
inline void Chromosome<T>::setBit(char bit, int pos)
{  
   #ifndef NDEBUG
   if (pos >= chrsize) {
      throw std::out_of_range("Error: in galgo::Chromosome<T>::replaceBit(char, int), second argument cannot be equal or greater than chromosome size.");
   }
   #endif

   std::stringstream ss;
   std::string str;
   ss << bit;
   ss >> str;
   chr.replace(pos, 1, str);
   std::cout << chr << "\n";
}

/*-------------------------------------------------------------------------------------------------*/

/**
 * @brief Flip an existing chromosome bit, change 0 by 1 and 1 by 0
 * @param pos Bit position to flip
 */
template <typename T>
inline void Chromosome<T>::flipBit(int pos)
{
   #ifndef NDEBUG
   if (pos >= chrsize) {
      throw std::out_of_range("Error: in galgo::Chromosome<T>::flipBit(int), argument cannot be equal or greater than chromosome size.");
   }
   #endif

   if (chr[pos] == '0') {
      chr.replace(pos, 1, "1");
   } else {
      chr.replace(pos, 1, "0");
   }
}

/*-------------------------------------------------------------------------------------------------*/

/**
 * @brief Get a chromosome bit
 * @param pos Pos of the wanted bit
 */
template <typename T>
inline char Chromosome<T>::getBit(int pos) const
{
   #ifndef NDEBUG
   if (pos >= chrsize) {
      throw std::out_of_range("Error: in galgo::Chromosome<T>::getBit(int), argument cannot be equal or greater than chromosome size.");
   }
   #endif

   return chr[pos];
}

/*-------------------------------------------------------------------------------------------------*/

/**
 * @brief Initialize or replace a portion of bits with a portion of another chromosome
 * @param x const reference to a chromosome
 * @param start Start position to copy in chr
 * @param end end position to copy in chr
 */
template <typename T>
inline void Chromosome<T>::setPortion(const Chromosome<T>& x, int start, int end)
{
   #ifndef NDEBUG
   if (start > chrsize) {
      throw std::out_of_range("Error: in galgo::Chromosome<T>::setPortion(const Chromosome<T>&, int, int), second argument cannot be greater than chromosome size.");
   }
   #endif

   chr.replace(start, end - start + 1, x.chr, start, end - start + 1);
}

/*-------------------------------------------------------------------------------------------------*/

/**
 * @brief Initialize or replace a portion of bits with a portions of another chromosome
 * @param x Const reference to a Chromosome
 * @param start Copy from start to end
 */
template <typename T>
inline void Chromosome<T>::setPortion(const Chromosome<T>& x, int start)
{
   #ifndef NDEBUG
   if (start > chrsize) {
      throw std::out_of_range("Error: in galgo::Chromosome<T>::setPortion(const Chromosome<T>&, int), second argument cannot be greater than chromosome size.");
   }
   #endif

   chr.replace(start, chrsize, x.chr, start, x.chrsize);
}

/*-------------------------------------------------------------------------------------------------*/

/**
 * @brief Get parameter values from chromosome, const method
 * @return a reference to a vector
 */
template <typename T>
inline const std::vector<T>& Chromosome<T>::getParam() const
{
   return param;
}

/*-------------------------------------------------------------------------------------------------*/

/**
 * @brief Get objective function result, const method
 * @return a reference to a vector
 */
template <typename T>
inline const std::vector<T>& Chromosome<T>::getResult() const
{
   return result;
}

/*-------------------------------------------------------------------------------------------------*/

/**
 * @brief Get the total sum of all objective function(s) result , const method
 * @return double or float total
 */
template <typename T>
inline T Chromosome<T>::getTotal() const
{
   return total;
}

/*-------------------------------------------------------------------------------------------------*/

/**
 * @brief Get constraint values for this chromosome , const method
 * @return the constraint stored in GeneticAlgorithm
 */
template <typename T>
inline const std::vector<T> Chromosome<T>::getConstraint() const
{
   return ptr->Constraint(param);
}

/*-------------------------------------------------------------------------------------------------*/

/**
 * @brief return chromosome size in number of bits
 * @return the chromosome size
 */
template <typename T>
inline int Chromosome<T>::size() const
{
   return chrsize;
}

/*-------------------------------------------------------------------------------------------------*/

/**
 * @brief return mutation rate
 * @return mutrate stored in GeneticAlgorithm
 */
template <typename T>
inline T Chromosome<T>::mutrate() const
{
   return ptr->mutrate;
}

/*-------------------------------------------------------------------------------------------------*/

/**
 * @brief return number of genes in chromosome
 * @return nbparam stored in GeneticAlgorithm
 */
template <typename T>
inline int Chromosome<T>::nbgene() const
{
   return ptr->nbparam;
}

/*-------------------------------------------------------------------------------------------------*/

/**
 * @brief return the index value of this chromosome
 * @return int value of index
 */
template <typename T>
inline int Chromosome<T>::nogen() const
{
   return numgen;
}

/*-------------------------------------------------------------------------------------------------*/

/**
 * @brief return lower bound
 * @return lowerBound stored in GeneticAlgorithm
 */
template <typename T>
inline const std::vector<T>& Chromosome<T>::lowerBound() const
{
   return ptr->lowerBound;
}

/*-------------------------------------------------------------------------------------------------*/


/**
 * @brief return uper bound
 * @return upperBound stored in GeneticAlgorithm
 */template <typename T>
inline const std::vector<T>& Chromosome<T>::upperBound() const
{
   return ptr->upperBound;
}

//=================================================================================================

}

#endif
