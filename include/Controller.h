//
// Created by Gautam Sharma on 2/18/24.
//

#ifndef REDISGRPC_CONTROLLER_H
#define REDISGRPC_CONTROLLER_H

#include <iostream>
#include <memory>
#include <string>
#include <thread>

#include "absl/flags/flag.h"
#include "absl/flags/parse.h"
#include "absl/strings/str_format.h"
#include <grpcpp/ext/proto_server_reflection_plugin.h>
#include <grpcpp/grpcpp.h>
#include <grpcpp/health_check_service_interface.h>
#include <grpc/support/log.h>
#include <grpcpp/grpcpp.h>
#include "Registry.h"

#include "redisgrpc.grpc.pb.h"
#include "redisgrpc.pb.h"

using grpc::Server;
using grpc::ServerAsyncResponseWriter;
using grpc::ServerBuilder;
using grpc::ServerCompletionQueue;
using grpc::ServerContext;
using grpc::Status;

using redisgrpc::RedisGrpcServer;
using redisgrpc::InitRequest;
using redisgrpc::InitReply;
using redisgrpc::SetRequest;
using redisgrpc::SetReply;

namespace redisgrpc{
    class RedisGrpcServiceImpl final : public RedisGrpcServer::Service {
        std::string _connectionID;
        Registry& _registry;
    public:
        RedisGrpcServiceImpl(std::string connectionId,Registry& registry):_connectionID(connectionId), _registry(registry){};
        Status InitConnection(ServerContext* context, const InitRequest* request,
                              InitReply* reply) override {
            std::string connectionId = request->connection_id();
            if(connectionId == _connectionID){
                reply->set_status("REDISLITE_OK");
            }
            else{
                reply->set_status("REDISLITE_ERROR");
            }
            return Status::OK;
        }

        Status Set(ServerContext* context, const SetRequest* request,
                   SetReply* reply) override {
            std::string key = request->key();
            std::string value = request->value();
            _registry.Set(_connectionID, key, value);
            reply->set_status("REDISLITE_OK");
            return Status::OK;
        }

        Status Get(ServerContext* context, const GetRequest* request,
                   GetReply* reply) override {
            std::string key = request->key();
            auto val = _registry.Get(_connectionID, key);
            if(val.first){
                reply->set_status("REDISLITE_OK");
            }
            else{
                reply->set_status("REDISLITE_KEY_NOT_FOUND");
            }
            reply->set_value(val.second);
            return Status::OK;
        }
    };

    class Controller{
    public:
        Controller(Registry& registry, std::string connectionId): _registry(registry), _connectionID(connectionId){
            this->Init();
        };
        void Init(){
            _registry.Init(this->_connectionID);
        }

        void Set(std::string key, std::string value){
            _registry.Set(this->_connectionID, key, value);
        }

        std::string Get(std::string key){
            auto val = _registry.Get(this->_connectionID, key);
            return val.second;
        }

        void RunServer(uint16_t port) {
            std::string server_address = absl::StrFormat("0.0.0.0:%d", port);
            RedisGrpcServiceImpl service (_connectionID, _registry);

            grpc::EnableDefaultHealthCheckService(true);
            grpc::reflection::InitProtoReflectionServerBuilderPlugin();
            ServerBuilder builder;
            // Listen on the given address without any authentication mechanism.
            builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
            // Register "service" as the instance through which we'll communicate with
            // clients. In this case it corresponds to an *synchronous* service.
            builder.RegisterService(&service);
            // Finally assemble the server.
            std::unique_ptr<Server> server(builder.BuildAndStart());
            std::cout << "RedisGrpc server listening on " << server_address << std::endl;

            // Wait for the server to shutdown. Note that some other thread must be
            // responsible for shutting down the server for this call to ever return.
            server->Wait();
        }

    private:
        Registry& _registry;
        std::string _connectionID;
    };
}



#endif //REDISGRPC_CONTROLLER_H
