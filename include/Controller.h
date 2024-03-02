//
// Created by Gautam Sharma on 2/18/24.
//

#ifndef REDISGRPC_CONTROLLER_H
#define REDISGRPC_CONTROLLER_H

#include <iostream>
#include <memory>
#include <string>
#include <thread>

//#include "absl/flags/flag.h"
//#include "absl/flags/parse.h"
//#include "absl/strings/str_format.h"
#include <grpcpp/ext/proto_server_reflection_plugin.h>
#include <grpcpp/grpcpp.h>
#include <grpcpp/health_check_service_interface.h>
#include <grpc/support/log.h>
#include <grpcpp/grpcpp.h>
#include "Registry.h"
#include "Macros.h"

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

#include "RedisGrpcServiceImpl.h"

#include "GlobalState.h"

#include "ControllerInterface.h"
namespace redisgrpc{


    class Controller: public ControllerInterface{

    public:
        Controller(std::string connectionId): _registry(new Registry()), _connectionID(connectionId){
            GlobalState::sClientAddressToController[connectionId] = this;
            this->Init();
        };
        // Initialize the registry
        void Init(){
            _registry->Init(this->_connectionID);
        }

        void RunServer() override{
            RedisGrpcServiceImpl service (_connectionID, _registry);
            grpc::EnableDefaultHealthCheckService(true);
            grpc::reflection::InitProtoReflectionServerBuilderPlugin();
            ServerBuilder builder;
            // Listen on the given address without any authentication mechanism.
            builder.AddListeningPort(_connectionID, grpc::InsecureServerCredentials());
            // Register "service" as the instance through which we'll communicate with
            // clients. In this case it corresponds to an *synchronous* service.
            builder.RegisterService(&service);
            // Finally assemble the server.
            server = builder.BuildAndStart();
            std::cout << "RedisGrpc server listening on " << _connectionID << std::endl;

            _serverStatus = SERVER_STATUS::RUNNING;

            // Wait for the server to shutdown. Note that some other thread must be
            // responsible for shutting down the server for this call to ever return.
            server->Wait();
        }

        void ShutDown(bool& serverStopped) override{
            server->Shutdown();
            _serverStatus = SERVER_STATUS::KILLED;
            serverStopped = true;
        }

        // Mainly used for testing
        inline std::string getConnectionID() const {
            return this->_connectionID;
        }

        inline SERVER_STATUS getServerStatus() const{
            return this->_serverStatus;
        }

    private:
        std::shared_ptr<Registry> _registry; // Reference to registry can be shared
        std::string _connectionID; // In the format "0.0.0.0:<portValue>"
        std::unique_ptr<Server> server; // Server should be unique
        SERVER_STATUS _serverStatus = SERVER_STATUS::NOT_STARTED;

    };




} // EO namespace redisgrpc



#endif //REDISGRPC_CONTROLLER_H
