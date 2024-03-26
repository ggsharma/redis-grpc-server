// /*
//  * MIT License
//  *
//  * Copyright (c) 2024 Gautam Sharma
//  *
//  * Permission is hereby granted, free of charge, to any person obtaining a copy
//  * of this software and associated documentation files (the "Software"), to deal
//  * in the Software without restriction, including without limitation the rights
//  * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//  * copies of the Software, and to permit persons to whom the Software is
//  * furnished to do so, subject to the following conditions:
//  *
//  * The above copyright notice and this permission notice shall be included in all
//  * copies or substantial portions of the Software.
//  *
//  * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//  * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//  * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//  * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//  * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
//  * SOFTWARE.
//  *

#ifndef REDISGRPC_CACHE_H
#define REDISGRPC_CACHE_H

#include <iostream>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <memory>
#include <utility>



// TODO need to make it more flexible. Right now it just supports string as the key and value type.
// Might need to templatize it.

/*
 * Main data structure
 * It evicts entries based on the least frequency used (LRU) policy
 * Whenever a GET request comes in, the frequency related to the key gets incremented
 * The key's that have the least frequency are evicted if the cache gets full
 */


/*
 * The data structure is like this
 * _data : {key : [value, frequency]} ......
 * _minFrequency : {minimum heap of all the frequencies}
 * _freqToKeys : {frequency : [keys]}
 */
namespace redisgrpc{
    // TODO: Package this into a separate library
    namespace lib {
        using SetOfInt_T = std::set<int>;
        using Cache_T = std::unordered_map<std::string, std::pair<std::string,int>>;
        using MapOfIntToSetOfStr_T = std::unordered_map<int, std::unordered_set<std::string>>;
        class Cache{

        private:
            size_t _maxNumEntries; // max entries allowed in the cache

            size_t _numElementsToBeRemoved = 0.1*_maxNumEntries;

            /*
             * Stores the minimum frequency of keys seen till now.
             * Min heap
             */
            SetOfInt_T _minFrequency;

            // key : {value, frequency}
            Cache_T _data;

            /*
             * Associates the frequency with the respective keys
             */
            MapOfIntToSetOfStr_T _freqToKeys;

            // Removes the keys from the cache that have the least frequency
            void removeLeastFrequencyElements();

        public:

            // Default constructor
            Cache(size_t maxNumEntries = 100000): _maxNumEntries(maxNumEntries){
            };

            // Used for testing
            inline Cache_T getData(){return _data;}

            // Used to get the cache data to stream it to the front end client
            std::unordered_map<std::string, std::string> getDataWithoutFreq() const;

            // Getter for minimum frequency set
            const SetOfInt_T& getMinFrequencySet() const{
                return _minFrequency;
            };

            // Getter for frequency to keys map
            const MapOfIntToSetOfStr_T& getFreqToKeysMap() const{
                return _freqToKeys;
            };

            // Gets the pair of bool and string. The bool represents if the key is present in the cache and the string
            // represents the value corresponding the key
            std::pair<bool,std::string> Get(std::string key);

            // Inserts the key in the cache and sets its frequency to 1
            void Set(std::string key, std::string val);

            // Copies the content of the cache to a persistent file and returns the status as a boolean
            bool toDB() const;

            // Prints the cache to the console
            void print();

        }; // EO class Cache
    }; // EO namespace lib
}; // EO namespace redisgrpc

#endif //REDISGRPC_CACHE_H
