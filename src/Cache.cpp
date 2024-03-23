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

//
// Created by Gautam Sharma on 2/18/24.
//
#include "Cache.hpp"
#include "Macros.h"
#include <cassert>

using redisgrpc::lib::Cache;

std::pair<bool,std::string> Cache::Get(std::string key){
    if(this->_data.find(key) == this->_data.end()){
        return std::make_pair(false, __GET_ERROR__);
    }

    int oldFreq = this->_data[key].second;

    // increment the frequency
    this->_data[key].second += 1;

    int newFreq = this->_data[key].second;

    // Delete old freq to key
    // // freq = {key1, key2,key3.....}
    auto itToPairOfFreqAndKeys = this->_freqToKeys.find(oldFreq);

    if(itToPairOfFreqAndKeys != this->_freqToKeys.end()){

        auto itToKey = itToPairOfFreqAndKeys->second.find(key);
        // It to key in unordered_Set
        if(itToKey != itToPairOfFreqAndKeys->second.end()){
            // erase key
            itToPairOfFreqAndKeys->second.erase(itToKey);
            // if unordered_set empty now
            if(itToPairOfFreqAndKeys->second.empty()){
                // erase the key which is frequency as well
                this->_freqToKeys.erase(oldFreq);
                // erase the frequency from set
                this->_minFrequency.erase(oldFreq);
            }
        }
        // key not found -> Get Request sent before Set. Should be handled by the code at the start of the function
        else{
            // No Op
        }
    }


    // insert new freq
    this->_freqToKeys[newFreq].insert(key);

    // Insert new frequency
    this->_minFrequency.insert(newFreq);

    return std::make_pair(true, this->_data.at(key).first);
}

void Cache::removeLeastFrequencyElements(){
        auto itToMinFreq = this->_minFrequency.begin();
        assert(itToMinFreq != this->_minFrequency.end());
        int minFreq = *itToMinFreq;

        auto keys = this->_freqToKeys[minFreq];
        // Delete the least frequency element from map
        for(const auto&k : keys){
            this->_data.erase(k);
        }
        // Delete the least frequency element from set
        this->_minFrequency.erase(itToMinFreq);
        this->_freqToKeys.erase(minFreq);
}

void Cache::Set(std::string key, std::string value){
    // Key was already present
    if(this->_data.find(key) != this->_data.end()){
        return;
    }

    if(this->_data.size() == this->_maxNumEntries){
        // remove least frequency elements
        this->removeLeastFrequencyElements();
    }

    this->_freqToKeys[1].insert(key);

    this->_minFrequency.insert(1);

    this->_data[key].first = value;
    // init the frequency
    this->_data[key].second = 1;
}

std::unordered_map<std::string, std::string> Cache::getDataWithoutFreq() const{
    // It's not efficient to always send the whole map
    //  Should find some another way
    std::unordered_map<std::string, std::string> out;
    for(const auto& keyValue : this->_data){
        out[keyValue.first] = keyValue.second.first;
    }
    return out;
}

void Cache::print(){
    for(auto&[k,v] : this->_data){
        std::cout<< "Key: "<< k << " " << "Value: " << v.first << " " << "Frequency: "<< v.second << std::endl;
    }
}