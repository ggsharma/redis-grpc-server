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
// Created by Gautam Sharma on 3/2/24.
//

#ifndef REDISGRPC_REDISGRPCSERVICEIMPL_H
#define REDISGRPC_REDISGRPCSERVICEIMPL_H

#include <iostream>
#include <memory>
#include <string>
#include <thread>
#include <future>

#include "absl/flags/flag.h"
#include "absl/flags/parse.h"
#include "absl/strings/str_format.h"
#include <grpcpp/ext/proto_server_reflection_plugin.h>
#include <grpcpp/grpcpp.h>
#include <grpcpp/health_check_service_interface.h>
#include <grpc/support/log.h>
#include <grpcpp/grpcpp.h>
#include "Registry.h"
#include "Macros.h"
#include "GlobalState.h"
#include "ControllerInterface.h"

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
        std::shared_ptr<Registry> _registry;

    public:
        RedisGrpcServiceImpl(std::string connectionId,std::shared_ptr<Registry> registry):_connectionID(connectionId), _registry(registry){};

        Status InitConnection(ServerContext* context, const InitRequest* request,
                              InitReply* reply) override {
            std::string connectionId = request->connection_id();
            if(connectionId == _connectionID){
                reply->set_status(__CONNECTION_OK__);
            }
            else{
                reply->set_status(__CONNECTION_ERROR__);
            }
            return Status::OK;
        }

        // There should be no error `setting` the value
        Status Set(ServerContext* context, const SetRequest* request,
                   SetReply* reply) override {
            std::string key = request->key();
            std::string value = request->value();
            _registry->Set(_connectionID, key, value);
            reply->set_status(__SET_SUCCESS__);
            return Status::OK;
        }

        // Gets the value of the key if present in the cache
        Status Get(ServerContext* context, const GetRequest* request,
                   GetReply* reply) override {
            std::string key = request->key();
            auto val = _registry->Get(_connectionID, key);
            if(val.first){
                reply->set_status(__GET_SUCCESS__);
            }
            else{
                reply->set_status(__GET_ERROR__);
            }
            reply->set_value(val.second);
            return Status::OK;
        }

        // Shuts down the server
        Status Shutdown(ServerContext* context, const ShutdownRequest* request,
                        ShutdownReply* reply) override{
            bool serverStopped = false;
            GlobalState::sClientAddressToController[this->_connectionID]->ShutDown(serverStopped);
            if(serverStopped){
                    reply->set_status(__SHUTDOWN_OK__);
                }
                else{
                    reply->set_status(__SHUTDOWN_ERROR__);
                }
            return Status::OK;
        }

        // Get Cache for logger service
        Status GetCacheForLogging(ServerContext* context, const LoggerGetRequest* request ,
                                  LoggerGetReply* reply) override{
            const auto cache = _registry->getDataWithoutFreq(_connectionID);
            if(cache){
                reply->set_status(__CACHE_RETRIEVAL_SUCCESS__);
                for(const auto& keyValue : cache){
                    reply->mutable_cache()->insert({keyValue.first,keyValue.second});
                }
            }
            else{
                reply->set_status(__CACHE_RETRIEVAL_ERROR__);
            }

            return Status::OK;
        }

    };





} // EO namespace redisgrpc

#endif //REDISGRPC_REDISGRPCSERVICEIMPL_H
