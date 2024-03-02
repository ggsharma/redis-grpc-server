//
// Created by Gautam Sharma on 2/18/24.
//

#ifndef REDISGRPC_TCONTROLLER_H
#define REDISGRPC_TCONTROLLER_H

#include <gtest/gtest.h>
#include <thread>

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

// Create the controller instance
Controller c(server_address);

// Start the server in a separate thread
std::thread serverThread([&]() {
    c.RunServer();
});

// Wait for the server to start
std::this_thread::sleep_for(std::chrono::seconds(3));

// Join the thread
serverThread.detach();

// Check the server status
ASSERT_EQ(c.getServerStatus(), SERVER_STATUS::RUNNING);


}

// Tests if the Server can be killed
TEST(Controller, ServerStatusWhenStopped) {
uint16_t portValue = 40004;
std::string server_address = absl::StrFormat("0.0.0.0:%d", portValue);
Controller c (server_address);
std::thread serverThread([&](){
    c.RunServer();
});

// Wait for the server to start
std::this_thread::sleep_for(std::chrono::seconds(1));

ASSERT_EQ(c.getServerStatus(),SERVER_STATUS::RUNNING);

// Check the server status
bool serverStopped = false;
c.ShutDown(serverStopped);

ASSERT_TRUE(serverStopped);
ASSERT_EQ(c.getServerStatus(),SERVER_STATUS::KILLED);

serverThread.join();
}


#endif //REDISGRPC_TCONTROLLER_H
