//
// Created by Gautam Sharma on 2/18/24.
//
// Copyright

#ifndef REDISLITE_CACHE_H
#define REDISLITE_CACHE_H

#include <iostream>
#include <unordered_map>
#include <memory>

namespace redislite{
    namespace lib {
        class Cache{
        private:
            Cache() noexcept = default;
            std::unordered_map<std::string, std::shared_ptr<Cache>> _uniqueIDToCacheMap;
            // TODO need to make it more flexible
            std::unordered_map<std::string, int> _data;
        public:
            std::shared_ptr<Cache> getInstance(const std::string& uniqueID);
        }; // EO class Cache
    }; // EO namespace lib
}; // EO namespace redislite

#endif //REDISLITE_CACHE_H
