#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>
// Can i include this?
#include<string>

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
				std::vector<int> nums;
        // Add your code here

				// changes each character in the string to a number
			    for(unsigned i = 0; i < k.size(); i++){
					int c = tolower(k[i]);
                    int j;
                    if(97 <= c && c <= 122){
                        j = c - 97;
                    }
					else if(48 <= c && c <= 57){
                        j = c - 22;
                    }
					nums.push_back(j);
				}

				// last 6 of hash vector, perform the equation
				// store that number into a new vector
                unsigned long long w[5];
				int idx = nums.size() - 1;
				for(int i = 4; i >= 0; i--){
                    unsigned long long a[6];
                    if(idx >= 0){
                            for(int j = 0; j < 6; j++){
                            if(idx >= 0) a[5 - j] = nums[idx];
                            else a[5 - j] = 0;
                            idx--;
                            //std::cout << a[5 - j] << std::endl;
                        }

                        // fix pow - maybe post on edstem
                        unsigned long long x = (pow(36,5) * a[0]) + (pow(36,4) * a[1]) + (pow(36,3) * a[2]) + (pow(36,2) * a[3]) + (36 * a[4]) + a[5];
					    w[i] = x;
                    }
                    else{
                        w[i] = 0;
                    }
                    //std::cout << i << " " << w[i] << std::endl;
				}
				unsigned long long retval = 0;
				for(unsigned k = 0; k < 5; k++){
                    //std::cout << k << std::endl;
					retval = retval + (rValues[k] * w[k]);
				}
                //std::cout << retval << std::endl;
                

				return (HASH_INDEX_T)retval;
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
