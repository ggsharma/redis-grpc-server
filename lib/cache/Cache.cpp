//
// Created by Gautam Sharma on 2/18/24.
//
#include "Cache.hpp"

using redislite::lib::Cache;

//redislite::lib::Cache::Cache() noexcept{
//    std::cout << "Cache initialized" << std::endl;
//}

std::shared_ptr<Cache> Cache::getInstance(const std::string& uniqueID){
    if(this->_uniqueIDToCacheMap.find(uniqueID) != this->_uniqueIDToCacheMap.end()){
        return this->_uniqueIDToCacheMap[uniqueID];
    }
    this->_uniqueIDToCacheMap[uniqueID] = std::make_shared<Cache>(Cache());
    return this->_uniqueIDToCacheMap[uniqueID];
}