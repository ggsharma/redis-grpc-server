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
#include <cassert>

using redisgrpc::lib::Cache;

std::pair<bool,std::string> Cache::Get(std::string key){
    if(this->_data.find(key) == this->_data.end()){
        return std::make_pair(false, "REDISLITE_NONE");
    }
    // increment the frequency
    this->_data[key].second += 1;
    return  std::make_pair(true, this->_data.at(key).first);
}

void Cache::Set(std::string key, std::string value){
    if(this->_data.size() == this->MAX_NUM_ENTRIES){
        // Find the element with the minimum frequency
        auto min_freq_itr = this->_data.begin();
        for (auto itr = this->_data.begin(); itr != this->_data.end(); ++itr) {
            if (itr->second.second < min_freq_itr->second.second) {
                min_freq_itr = itr;
            }
        }

        // Erase the element with the minimum frequency
        if (min_freq_itr != _data.end()) {
            _data.erase(min_freq_itr);
        }
    }
    this->_data[key].first = value;
    // init the frequency
    this->_data[key].second = 1;
    assert(this->_data.size() <= MAX_NUM_ENTRIES);
}

void Cache::print(){
    for(auto&[k,v] : this->_data){
        std::cout<< "Key: "<< k << " " << "Value: " << v.first << " " << "Frequency: "<< v.second << std::endl;
    }
}