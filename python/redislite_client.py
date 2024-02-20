#  /*
#   * MIT License
#   *
#   * Copyright (c) 2024 Gautam Sharma
#   *
#   * Permission is hereby granted, free of charge, to any person obtaining a copy
#   * of this software and associated documentation files (the "Software"), to deal
#   * in the Software without restriction, including without limitation the rights
#   * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
#   * copies of the Software, and to permit persons to whom the Software is
#   * furnished to do so, subject to the following conditions:
#   *
#   * The above copyright notice and this permission notice shall be included in all
#   * copies or substantial portions of the Software.
#   *
#   * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
#   * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
#   * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
#   * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
#   * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
#   * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
#   * SOFTWARE.
#   */
from __future__ import print_function

import logging

import grpc

import redislite_pb2 as redislite_pb2
import redislite_pb2_grpc as redislite_pb2_grpc
import random
import string
import time
# Define the characters to choose from for generating random strings
characters = string.ascii_letters + string.digits + string.punctuation

# Number of random strings to generate
num_strings = 200

# Length of each random string
string_length = 10
def run():
    # NOTE(gRPC Python Team): .close() is possible on a channel and should be
    # used in circumstances in which the with statement does not fit the needs
    # of the code.
    print("Will try to connect to server ...")
    with grpc.insecure_channel("localhost:50051") as channel:
        try:
            stub = redislite_pb2_grpc.RedisLiteServerStub(channel)
            # Generate random strings 200 times
            for _ in range(num_strings):
                # Generate a random string of specified length
                time.sleep(0.01)
                random_string = ''.join(random.choice(characters) for _ in range(string_length))
                response = stub.Set(redislite_pb2.SetRequest(key=random_string, value="sharma"))
            #response = stub.InitConnection(redislite_pb2.InitRequest(connection_id="0.0.0.0:50051"))
            #response = stub.Get(redislite_pb2.GetRequest(key="gautam1"))
        except:
            print("Server not started");
            return;
    print("Greeter client received: " + response.status)


if __name__ == "__main__":
    logging.basicConfig()
    run()