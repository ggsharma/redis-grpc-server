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

#include <gtest/gtest.h>
#include "Cache.hpp"
#include <string>
#include <random>
#include <vector>

// Demonstrate some basic assertions.
TEST(CacheTest, Init) {
using redisgrpc::lib::Cache;
Cache c;
EXPECT_EQ(c.getData().size(),0);
}


TEST(CacheTest, Set) {
using redisgrpc::lib::Cache;
Cache c;
std::string characters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~";

// Number of random strings to generate
int num_strings = 100;

// Length of each random string
int string_length = 10;

// Seed the random number generator
std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<> dis(0, characters.size() - 1);

// Generate random strings 200 times
for (int i = 0; i < num_strings; ++i) {
// Generate a random string of specified length
std::string random_string;
for (int j = 0; j < string_length; ++j) {
    random_string += characters[dis(gen)];

}
c.Set(random_string, "some_val");
}
EXPECT_EQ(c.getData().size(),100);
}


TEST(CacheTest, 1Entry) {
using redisgrpc::lib::Cache;
Cache c(5);
const int expectedFreq = 3;

c.Set("hello", "1");
c.Get("hello");
c.Get("hello");

auto&& minFreqSet = c.getMinFrequencySet();
auto&& freqToKeysMap = c.getFreqToKeysMap();

auto it = minFreqSet.begin();
EXPECT_EQ(*it,expectedFreq);

auto s = freqToKeysMap.at(expectedFreq);
ASSERT_EQ(*(s.begin()),"hello");

}

TEST(CacheTest, 2Entry) {
    using redisgrpc::lib::Cache;
    Cache c(5);
    const int expectedFreq = 3;
    c.Set("hello", "1");
    c.Set("mello", "3");
    c.Get("hello"); // 2
    c.Get("mello");
    c.Get("mello"); // 3

    auto&& minFreqSet = c.getMinFrequencySet();
    auto&& freqToKeysMap = c.getFreqToKeysMap();

    auto it = minFreqSet.begin();
    ++it;
    EXPECT_EQ(*it,expectedFreq);

    auto s = freqToKeysMap.at(expectedFreq);
    ASSERT_EQ(*(s.begin()),"mello");
}


TEST(CacheTest, 6Entry) {
using redisgrpc::lib::Cache;
Cache c(5);

c.Set("hello", "1");
c.Set("mello", "3");
c.Set("aello", "99");
c.Set("zello", "4");
c.Set("cello", "4"); // freq = 1 -> is expected to be deleted


c.Get("hello"); // 2
c.Get("mello");
c.Get("mello"); // 3
c.Get("aello"); // 2
c.Get("zello"); // 2

c.Set("trello", "5");
c.Get("trello");

auto&& minFreqSet = c.getMinFrequencySet();
auto&& freqToKeysMap = c.getFreqToKeysMap();

auto it = minFreqSet.begin();

ASSERT_EQ(c.getData().size(), 5);
ASSERT_EQ(*(it),2); // min frequency should be 2

EXPECT_ANY_THROW(freqToKeysMap.at(1));

}























//TEST(CacheTest, Get) {
//using redisgrpc::lib::Cache;
//Cache c;
//std::string characters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~";
//
//// Number of random strings to generate
//int num_strings = 1000;
//
//// Length of each random string
//int string_length = 10;
//
//// Seed the random number generator
//std::random_device rd;
//std::mt19937 gen(rd());
//std::uniform_int_distribution<> dis(0, characters.size() - 1);
//
//// Generate random strings 200 times
//for (int i = 0; i < num_strings; ++i) {
//    // Generate a random string of specified length
//    std::string random_string;
//    for (int j = 0; j < string_length; ++j) {
//    random_string += characters[dis(gen)];
//    }
//    // key and value are same
//    c.Set(random_string, random_string);
//    // Key should be present
//    EXPECT_TRUE(c.Get(random_string).first);
//    // value should match
//    EXPECT_EQ(c.Get(random_string).second,random_string);
//}
//c.print();
//}
//
//// Max entries allowed should be 100000
//TEST(CacheTest, MaxEntries) {
//    using redisgrpc::lib::Cache;
//    Cache c;
//    std::string characters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~";
//
//    // Number of random strings to generate
//    int num_strings = 100001;
//    int max_entries_allowed = 100000;
//    // Length of each random string
//    int string_length = 10;
//
//    // Seed the random number generator
//    std::random_device rd;
//    std::mt19937 gen(rd());
//    std::uniform_int_distribution<> dis(0, characters.size() - 1);
//
//    // Generate random strings 200 times
//    for (int i = 0; i < num_strings; ++i) {
//    // Generate a random string of specified length
//    std::string random_string;
//
//    for (int j = 0; j < string_length; ++j) {
//    random_string += characters[dis(gen)];
//    }
//
//    // key and value are same
//    c.Set(random_string, random_string);
//    }
//    auto cache = c.getData();
//
//    std::cout << cache.size() << std::endl;
//    // 10000 least frequency elements will be removed
//    EXPECT_EQ(cache.size(),num_strings - 10000 - 1);
//}
//
//
//// Max entries allowed should be 100000
//TEST(CacheTest, LeastFrequencyElementsRemoved) {
//using redisgrpc::lib::Cache;
//Cache c;
//std::string characters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~";
//
//// Number of random strings to generate
//int num_strings = 110000;
//// Length of each random string
//int string_length = 10;
//
//// Seed the random number generator
//std::random_device rd;
//std::mt19937 gen(rd());
//std::uniform_int_distribution<> dis(0, characters.size() - 1);
//
//std::vector<std::string> expectedKeysToBeRemoved;
//
//// Generate random strings 100002 times
//for (int i = 0; i < num_strings; ++i) {
//// Generate a random string of specified length
//std::string random_string;
//
//for (int j = 0; j < string_length; ++j) {
//random_string += characters[dis(gen)];
//}
//
//// key and value are same
//c.Set(random_string, random_string);
//
//if(i >= 0  && i < 10000){
//    expectedKeysToBeRemoved.push_back(random_string);
//}
//else{
//    // increase it's frequency
//    c.Get(random_string);
//    c.Get(random_string);
//}
//
//}
//
//auto cache = c.getData();
//
//std::cout << cache.size() << std::endl;
//// 10000 least frequency elements will be removed
//EXPECT_EQ(cache.size(), num_strings - 10000 - 1);
//
//// The 10000 with least frequency should be deleted
//for(size_t idx=0; idx < expectedKeysToBeRemoved.size(); ++idx){
////    std::cout << expectedKeysToBeRemoved[idx] << " " << c.Get(expectedKeysToBeRemoved[idx]).first << std::endl;
//    EXPECT_EQ(c.Get(expectedKeysToBeRemoved[idx]).first, false);
//}
//
//}
