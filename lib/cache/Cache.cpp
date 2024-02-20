//
// Created by Gautam Sharma on 2/18/24.
//
#include "Cache.hpp"

using redislite::lib::Cache;

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

