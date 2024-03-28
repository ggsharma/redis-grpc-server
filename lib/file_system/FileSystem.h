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
// Created by Gautam Sharma on 3/24/24.
//

#ifndef REDISGRPC_FILESYSTEM_H
#define REDISGRPC_FILESYSTEM_H


#include <string>
#include <unordered_map>
#include <utility>
#include <iostream>
#include <fstream>
#include <filesystem> // For filesystem operations
namespace fs = std::filesystem;


namespace redisgrpc {
    namespace lib{
        using Cache_T = std::unordered_map<std::string, std::pair<std::string,int>>;
        class FileSystem{
        private:
            std::string _fileName;
            std::string _directoryName;
        private:
            FileSystem() = delete;
        public:
            inline static bool sendContentsToDB( const Cache_T& cache, const std::string& fileName="redisgrpc_cache", const std::string& directoryName = "db"){
                // Create a directory called "db" if it doesn't exist
                fs::path directory = directoryName;
                if (!fs::exists(directory)) {
                    fs::create_directory(directory);
                    std::cout << "Directory " << directoryName << " created." << std::endl;
                } else {
                    std::cout << "Directory " << directoryName << " already exists." << std::endl;
                }

                // Open a file inside the "db" directory for writing
                fs::path filePath = directory / (fileName+".rg");
                std::ofstream outFile(filePath);
                if (!outFile.is_open()) {
                    std::cerr << "Error opening file for writing." << std::endl;
                    return false;
                }

                for(const auto&[k,v] : cache){
                    // Write data to the file
                    outFile << k << " " << v.first << std::endl;
                }

                // Close the file
                outFile.close();

                std::cout << "File " << fileName << "saved inside directory " << directoryName << std::endl;

                return true;
            }
        }; // EO class Filesystem
    } // EO namespace lib
}// EO namespace redisgrpc




#endif //REDISGRPC_FILESYSTEM_H
