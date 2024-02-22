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

TEST(CacheTest, Get) {
using redisgrpc::lib::Cache;
Cache c;
std::string characters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~";

// Number of random strings to generate
int num_strings = 1000;

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
c.Set(random_string, random_string);
EXPECT_TRUE(c.Get(random_string).first);
EXPECT_EQ(c.Get(random_string).second,random_string);

for(int idx=0; idx < i; ++idx){
    c.Get(random_string);
}

}
c.print();
}


