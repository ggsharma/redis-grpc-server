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
#include <map>
#include <set>
#include <unordered_set>
#include <memory>
#include <utility>

namespace redisgrpc{
    namespace lib {
        class Cache{
        private:
            size_t _maxNumEntries;
            size_t _numElementsToBeRemoved = 0.1*_maxNumEntries;
            // TODO need to make it more flexible
            // value to frequency
            // min heap
            std::set<int> _minFrequency;
            // key : {value, frequency}
            std::unordered_map<std::string, std::pair<std::string,int>> _data;
            // freq = {key1, key2,key3.....}
            std::unordered_map<int, std::unordered_set<std::string>> _freqToKeys;
            void removeLeastFrequencyElements();
        public:
            // Default constructor
            Cache(size_t maxNumEntries = 100000): _maxNumEntries(maxNumEntries){
            };

            // used for testing
            inline std::unordered_map<std::string, std::pair<std::string,int>> getData(){return _data;}
            std::unordered_map<std::string, std::string> getDataWithoutFreq() const;
            const std::set<int>& getMinFrequencySet() const{
                return _minFrequency;
            };
            const std::unordered_map<int, std::unordered_set<std::string>>& getFreqToKeysMap() const{
                return _freqToKeys;
            };
            std::pair<bool,std::string> Get(std::string key);
            void Set(std::string key, std::string val);
            void print();
        }; // EO class Cache
    }; // EO namespace lib
}; // EO namespace redisgrpc

#endif //REDISGRPC_CACHE_H
