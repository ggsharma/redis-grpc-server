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

#ifndef REDISLITE_LOGGER_H
#define REDISLITE_LOGGER_H

#include <iostream>

namespace redislite{
    namespace lib{
        class Logger{
        public:
            Logger(){
                _init();
            };
            inline void log(std::string &&input){
                this->_print();
                std::cout << input << std::endl;
                this->_print();
            }
            inline void error(std::string &&input){
                this->_print();
                std::cerr << input << std::endl;
                this->_print();
            }
            const int getNumDashes() const {
                return this->_numDashes;
            }
            std::string getProjectName() const{
                return this->_projectName;
            }
        private:
            const std::string _projectName = "🔥redislite";
            void _print(){
                for(size_t idx = 0; idx < _numDashes; ++idx) {
                    std::cout << symbol;
                }
                std::cout << std::endl;
            }
            const int _numDashes = 20;
            const char symbol = '-';
            inline void _init(){
                std::cout << _projectName << std::endl;
                for(size_t idx = 0; idx < _numDashes; ++idx) {
                    std::cout << symbol;
                }
                std::cout << std::endl;
            }
        };// EO class Logger
    } // EO namespace lib
}; // EO namespace redislite
#endif //REDISLITE_LOGGER_H
