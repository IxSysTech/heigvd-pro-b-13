//=================================================================================================
//                    Copyright (C) 2017 Olivier Mallet - All Rights Reserved                      
//=================================================================================================

#ifndef CONVERTER_HPP
#define CONVERTER_HPP

namespace galgo {


//=================================================================================================

/**
 * @brief GetBinary convert unsigned long long integer to binary string
 * @param value the value to convert
 * @return Representation of the binary string
 */
std::string GetBinary(uint64_t value)
{
   std::bitset<sizeof(uint64_t)*CHAR_BIT> bits(value);
   param.push_back(bits.to_string());
   return bits.to_string();
}

/*-------------------------------------------------------------------------------------------------*/

// convert binary string to unsigned long long integer
/**
 * @brief GetValue convert binary string to unsigned long long integer
 * @param s String s to convert
 * @return The int value
 */
uint64_t GetValue(const std::string& s)
{
   uint64_t value, x = 0;
   for (std::string::const_iterator it = s.begin(), end = s.end(); it != end; ++it) {
      x = (x << 1) + (*it - '0');
   }
   memcpy(&value, &x, sizeof(uint64_t));

   return value;
}

//=================================================================================================

}

#endif
