//
// Created by Gautam Sharma on 2/18/24.
//

#ifndef REDISGRPC_TCONTROLLER_H
#define REDISGRPC_TCONTROLLER_H
#include <gtest/gtest.h>

#include "Controller.h"

using redisgrpc::Controller;
using redisgrpc::SERVER_STATUS;


// Tests if the Controller has the correct server address
TEST(Controller, ServerAddress) {
uint16_t portValue = 63000;
std::string server_address = absl::StrFormat("0.0.0.0:%d", portValue);
Controller c (server_address);
ASSERT_EQ(c.getConnectionID(), server_address);
}

// Tests if the Server status is correct on initialization
TEST(Controller, ServerStatusWhenInit) {
uint16_t portValue = 63000;
std::string server_address = absl::StrFormat("0.0.0.0:%d", portValue);
Controller c (server_address);
ASSERT_EQ(c.getServerStatus(), SERVER_STATUS::NOT_STARTED);
}

// Tests if the Server status is correct when started
TEST(Controller, ServerStatusWhenStarted) {
uint16_t portValue = 63000;
std::string server_address = absl::StrFormat("0.0.0.0:%d", portValue);
Controller c (server_address);
ASSERT_EQ(c.getServerStatus(), SERVER_STATUS::RUNNING);
}


#endif //REDISGRPC_TCONTROLLER_H
