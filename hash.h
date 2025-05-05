#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>

typedef std::size_t HASH_INDEX_T;

struct MyStringHash {
    HASH_INDEX_T rValues[5] { 983132572, 1468777056, 552714139, 984953261, 261934300 };
    MyStringHash(bool debug = true)
    {
        if(false == debug){
            generateRValues();
        }
    }
    // hash function entry point (i.e. this is h(k))
    HASH_INDEX_T operator()(const std::string& k) const
    {
      unsigned long long w[5];
      for (int i = 0; i < 5; i++)
      {
        w[i] = 0;
      }
      
      size_t index = 0;
      while (index*6 < k.length())
      {
        unsigned long long currSum = 0;
        for (int i = 0; i < 6; i++)
        {
          currSum *= 36;
          if (k.length() >= (index+1)*6 - i)
          {
            currSum += charToNumber(k[k.length() - (index+1)*6 + i]);
          }
        }
        w[4-index] = currSum;
        index++;
      }

      HASH_INDEX_T total = 0;
      for (int i = 0; i < 5; i++)
      {
        //std::cout << "w[" << i << "] = " << w[i] << std::endl;
        total += w[i] * rValues[i];
      }
      return total;
    }

    // A likely helper function is to convert a-z,0-9 to an integer value 0-35
    HASH_INDEX_T charToNumber(char letter) const
    {
        if (letter < 65)
          return (26 + letter-'0');
        else if (letter < 97)
          return letter-'A';
        else
          return letter-'a';
    }

    // Code to generate the random R values
    void generateRValues()
    {
        // obtain a seed from the system clock:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator (seed);  // mt19937 is a standard random number generator

        // Simply call generator() [it has an operator()] to get another random number
        for(int i{ 0 }; i < 5; ++i)
        {
            rValues[i] = generator();
        }
    }
};

#endif
