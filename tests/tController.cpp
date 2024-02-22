//
// Created by Gautam Sharma on 2/18/24.
//

#ifndef REDISGRPC_TCONTROLLER_H
#define REDISGRPC_TCONTROLLER_H
#include <gtest/gtest.h>
#include "Controller.h"
// Demonstrate some basic assertions.
TEST(HelloTest, BasicAssertions) {
// Expect two strings not to be equal.
EXPECT_STRNE("hello", "world");
// Expect equality.
EXPECT_EQ(7 * 6, 42);
}

TEST(HelloTest1, BasicAssertions) {
// Expect two strings not to be equal.
redisgrpc::Controller c1;
EXPECT_STRNE("hello", "world");
// Expect equality.
EXPECT_EQ(7 * 6, 42);
}
#endif //REDISGRPC_TCONTROLLER_H
