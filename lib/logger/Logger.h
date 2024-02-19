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
            Logger();
            void log();
            void error();
        private:
            void _print();

        };// EO class Logger
    } // EO namespace lib
}; // EO namespace redislite
#endif //REDISLITE_LOGGER_H
