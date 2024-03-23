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

#ifndef REDISGRPC_MACROS_H
#define REDISGRPC_MACROS_H

#include <string>

namespace redisgrpc{
    namespace status{
        #define __CONNECTION_OK__ "REDISGRPC_OK"
        #define __CONNECTION_ERROR__ "REDISGRPC_CONNECTION_ERROR"
        #define __SET_SUCCESS__ "REDISGRPC_SET_OK"
        #define __SET_ERROR__ "REDISGRPC_SET_ERROR"
        #define __GET_SUCCESS__ "REDISGRPC_GET_OK"
        #define __GET_ERROR__ "REDISGRPC_KEY_NOT_FOUND"
        #define __SHUTDOWN_OK__ "REDISGRPC_SHUTDOWN_OK"
        #define __SHUTDOWN_ERROR__ "REDISGRPC_SHUTDOWN_ERROR"
        #define __CONNECTION_ID_ERROR__ "REDISGRPC_INCORRECT_CONNECTION_ID"
        #define __CACHE_RETRIEVAL_SUCCESS__ "REDISGRPC_CACHE_RETRIEVAL_SUCCESSFUL"
        #define __CACHE_RETRIEVAL_ERROR__ "REDISGRPC_CACHE_RETRIEVAL_NOT_SUCCESSFUL"
    }

    enum class SERVER_STATUS{
        NOT_STARTED, RUNNING, KILLED
    };
}


#endif //REDISGRPC_MACROS_H
