//
// Created by Gautam Sharma on 2/19/24.
//
#include "Service.h"



// Logic and data behind the server's behavior.
Status RedisLiteServiceImpl::InitConnection(ServerContext* context, const InitRequest* request,
        InitReply* reply){
    std::string prefix("Hello ");
    reply->set_status("success");
    std::cout << "Got message: " << request->connection_id()<< std::endl;
    return Status::OK;
}

