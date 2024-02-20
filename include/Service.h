//
// Created by Gautam Sharma on 2/19/24.
//

#ifndef REDISLITE_SERVICE_H
#define REDISLITE_SERVICE_H

#include <iostream>
#include <memory>
#include <string>

#include "absl/flags/flag.h"
#include "absl/flags/parse.h"
#include "absl/strings/str_format.h"

#include <grpcpp/ext/proto_server_reflection_plugin.h>
#include <grpcpp/grpcpp.h>
#include <grpcpp/health_check_service_interface.h>
#include "redislite.grpc.pb.h"
#include "redislite.pb.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;

using redislite::RedisLiteServer;
using redislite::InitRequest;
using redislite::InitReply;



// Logic and data behind the server's behavior.
class RedisLiteServiceImpl final : public RedisLiteServer::Service{
        Status InitConnection(ServerContext* context, const InitRequest* request,
                              InitReply* reply) override;

};

#endif //REDISLITE_SERVICE_H

