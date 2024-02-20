// Copyright

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
//#include "Service.h"

#include "Logger.h"
#include "Controller.h"
#include "Registry.h"


using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;

using redislite::lib::Logger;
using redislite::Controller;
using redislite::Registry;

ABSL_FLAG(uint16_t, port, 50051, "Server port for the service");

int main() {
    Logger l;
    Registry r;
    std::string server_address = absl::StrFormat("0.0.0.0:%d", absl::GetFlag(FLAGS_port));
    l.log("hello from logger");
    Controller c(r,server_address);
    c.RunServer(absl::GetFlag(FLAGS_port));
    return 0;
}
