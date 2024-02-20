//
// Created by Gautam Sharma on 2/18/24.
//
// Copyright

#ifndef REDISLITE_CACHE_H
#define REDISLITE_CACHE_H

#include <iostream>
#include <unordered_map>
#include <memory>
#include <utility>
namespace redislite{
    namespace lib {
        class Cache{
        private:

            const size_t MAX_NUM_ENTRIES = 100;
            // TODO need to make it more flexible
            // value to frequency
            std::unordered_map<std::string, std::pair<std::string,int>> _data;
        public:
            Cache() noexcept = default;
            std::pair<bool,std::string> Get(std::string key);
            void Set(std::string key, std::string val);
        }; // EO class Cache
    }; // EO namespace lib
}; // EO namespace redislite

#endif //REDISLITE_CACHE_H
