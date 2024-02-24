# redis-grpc-server

by Gautam Sharma - [Visit Website](https://gsharma.dev)

## Introduction

Welcome to RedisGrpcServer! Here, we'll learn how to create a system similar to Redis, a popular data storage tool. But we'll do it in a way that's easy to understand, using a programming language called C++ and a method called gRPC.

## Getting Started

Let's start by understanding why we're doing this. I got interested in Redis and wanted to know how it works. So, I decided to build something similar myself using my knowledge of C++.

## The Framework

Instead of using complex methods, we'll use something called gRPC, which is a simpler and faster way for programs to talk to each other. This makes our project more efficient and easier to build.

## Components of RedisGrpcServer

Our system has three main parts:

1. **Controller**: It handles connections from other programs and sends their requests to the right place.
2. **Cache**: This is where we store the data. Think of it like a digital bookshelf where we keep our information.
3. **Registry**: It decides if we should store new information in the cache or get existing information from there.

## Implementation Details

We keep our system running smoothly by making sure we don't store too much data. We also make sure that when programs talk to each other, they do it quickly and without any delays.

## Building and Running

### For Mac:

1. Go to the `redis-grpc-server` folder.
2. Create a new folder called `build`.
3. Go into the `build` folder.
4. Type `cmake -DCMAKE_BUILD_TYPE=Debug .. && make -j16` and press Enter.
5. Run `./redis_grpc_server`.

### For Windows:

1. Go to the `redis-grpc-server` folder.
2. Create a new folder called `build`.
3. Go into the `build` folder.
4. Type `cmake ..` and press Enter.
5. After that, you can build and run the program using your preferred method for Windows.

## Using the Python Client Library

To use the Python client library, you can install it with a simple command:

```bash
pip install redisgrpc==0.4
```

Then, you can use the code below to try it out:

```python
from __future__ import print_function
import logging
from  redisgrpc import redisgrpc as rg

def run():
    # Initialize the Client with the server port
    c = rg.Client(50051)
    # Initialize the connection
    c.init_connection()
    # Perform some Redis-like operations
    for idx in range(1, 10):
        k = input("Set Key: ")
        v = input("Set Value: ")
        c.set(k, v)
        # Get the cached value back
        cached_val = c.get(k)
        print("Cached value of key {} is {}".format(k, cached_val))

if __name__ == "__main__":
    # Configure logging
    logging.basicConfig()
    # Run the example
    run()
```

## How gRPC works
Here's a simplified explanation of how gRPC works:

1. **Service Definition**: First, you define a service and its methods using Protocol Buffers (protobuf). This service definition acts as a contract between the client and server, specifying the available methods and their parameters.

2. **Code Generation**: Using the service definition, you generate client and server code in your preferred programming languages. This generated code includes classes and methods that handle communication and data serialization/deserialization.

3. **Client-Server Communication**: When a client wants to communicate with the server, it calls the corresponding method on its generated gRPC client object. The client object serializes the request parameters into binary data using protobuf and sends it to the server.

4. **Server-Side Handling**: The server receives the request and forwards it to the appropriate method implementation. This method processes the request, performs any necessary computations, and prepares the response.

5. **Response Transmission**: Once the server has processed the request and generated a response, it serializes the response data into binary format using protobuf. The server then sends this binary response back to the client.

6. **Client-Side Handling**: Upon receiving the response, the client's gRPC client object deserializes the binary data into the corresponding data structures. It then returns the response to the client code that initiated the request.

7. **Bi-Directional Streaming**: gRPC also supports bi-directional streaming, where both client and server can send multiple messages asynchronously over a single connection. This is useful for real-time communication or long-lived connections.

Certainly! Here's how you can add a license and contributing section to your project's README:


## License

This project is licensed under the [MIT License](https://opensource.org/licenses/MIT) - see the [LICENSE](LICENSE) file for details.

## Contributing

We welcome contributions to improve the project and encourage participation from the community! If you'd like to contribute, please follow these guidelines:

1. Fork the repository and clone it to your local machine.
2. Create a new branch for your feature or bug fix: `git checkout -b feature-branch`.
3. Make your changes and ensure they're well-tested.
4. Commit your changes: `git commit -m 'Add new feature'`.
5. Push to the branch: `git push origin feature-branch`.
6. Submit a pull request detailing your changes and explaining their purpose.
7. Our team will review your pull request and provide feedback. Once approved, your changes will be merged into the main branch.

Thank you for contributing to our project and helping make it better for everyone! 🎉

