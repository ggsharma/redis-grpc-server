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
// Created by Gautam Sharma on 2/19/24.
//

#include "Registry.h"
#include "absl/flags/flag.h"
#include "absl/flags/parse.h"
#include "absl/strings/str_format.h"

using redisgrpc::Registry;
using redisgrpc::lib::Cache;

void Registry::Init(std::string connection_id){
    this->_init(connection_id);
    _logger.log(absl::StrFormat("Cache initialized with connection id %s", connection_id));
}

std::pair<bool,std::string> Registry::Get(std::string uniqueID, std::string key){
    _logger.log(absl::StrFormat("Getting Value for Key:%s", key));
    const auto& cachePtr = this->_getInstance(uniqueID);
    return cachePtr->Get(key);
}

void Registry::Set(std::string uniqueID, std::string key, std::string value){
     _logger.log(absl::StrFormat("Setting Value:%s for Key:%s ",value, key));
    const auto& cachePtr = this->_getInstance(uniqueID);
    cachePtr->Set(key, value);
}

std::unordered_map<std::string, std::string> Registry::getDataWithoutFreq(std::string uniqueID){
    const auto& cachePtr = this->_getInstance(uniqueID);
    return cachePtr->getDataWithoutFreq();
}


void Registry::_init(const std::string& uniqueID){
    this->_uniqueIDToCacheMap[uniqueID] = std::make_shared<Cache>(Cache());
}

std::shared_ptr<Cache> Registry::_getInstance(const std::string& uniqueID){
    if(this->_uniqueIDToCacheMap.find(uniqueID) != this->_uniqueIDToCacheMap.end()){
        return this->_uniqueIDToCacheMap[uniqueID];
    }
    this->_uniqueIDToCacheMap[uniqueID] = std::make_shared<Cache>(Cache());
    return this->_uniqueIDToCacheMap[uniqueID];
}