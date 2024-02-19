#include <iostream>

#include <memory>
#include <string>
#include <thread>

#include "absl/flags/flag.h"
#include "absl/flags/parse.h"
#include "absl/strings/str_format.h"

#include <grpc/support/log.h>
#include <grpcpp/grpcpp.h>

#include "Server.hpp"

int main() {
    std::cout << "Hello, World!" << std::endl;
    print_server();
    return 0;
}
