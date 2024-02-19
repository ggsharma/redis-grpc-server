//
// Created by Gautam Sharma on 2/19/24.
//
#include "Service.h"



// Logic and data behind the server's behavior.
Status GreeterServiceImpl::SayHello(ServerContext* context, const HelloRequest* request,
                HelloReply* reply)  {
    std::string prefix("Hello ");
    reply->set_message(prefix + request->name());
    return Status::OK;
}

