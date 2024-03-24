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

#ifndef REDISGRPC_REGISTRY_H
#define REDISGRPC_REGISTRY_H

#include <string>
#include <memory>
#include <utility>
#include <unordered_map>

#include "Cache.hpp"
#include "Logger.h"

namespace redisgrpc{
    class Registry{
    private:
        redisgrpc::lib::Logger _logger;
    public:
        // Default constructor
        Registry() = default;

        // Takes a connection id that is a local host running on a particular port number
        void Init(std::string connection_id);

        // Gets the pair of bool and string. The bool represents if the key is present in the cache and the string
        // represents the value corresponding the key
        std::pair<bool,std::string> Get(std::string uniqueID, std::string key);

        // Inserts the key in the cache and sets its frequency to 1
        void Set(std::string uniqueID, std::string key, std::string value);

        // Used to get the cache data to stream it to the front end client
        std::unordered_map<std::string, std::string> getDataWithoutFreq(std::string uniqueID);

    private:
        // Initializes a shared_ptr to Cache
        void _init(const std::string& uniqueID);

        // Gets shared_ptr instance to the cache
        std::shared_ptr<redisgrpc::lib::Cache> _getInstance(const std::string& uniqueID);

        // Stores a cache for a unique address
        std::unordered_map<std::string, std::shared_ptr<redisgrpc::lib::Cache>> _uniqueIDToCacheMap;
    };
}
#endif //REDISGRPC_REGISTRY_H
