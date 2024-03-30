# redis-grpc-server

by Gautam Sharma - [Visit Website](https://gsharma.dev)

# redis-grpc-server
![GitHub Actions Workflow Status](https://img.shields.io/github/actions/workflow/status/gautam-sharma1/redis-grpc-server/.github/workflows/cmake-multi-platform.yml)
![GitHub License](https://img.shields.io/github/license/gautam-sharma1/redis-grpc-server?color=yellow)
![](https://img.shields.io/badge/Code-C++-green)
![](https://img.shields.io/badge/Code-Python-green)
![](https://img.shields.io/badge/Dependency-gRPC-orange)
![GitHub repo file or directory count](https://img.shields.io/github/directory-file-count/gautam-sharma1/redis-grpc-server)
![GitHub commit activity](https://img.shields.io/github/commit-activity/t/gautam-sharma1/redis-grpc-server)


## Introduction

Welcome to RedisGrpcServer! This is a simple **Redis like** cache server built on top of gRPC for programming language agnostic client hookups. 

It uses a Least Frequency Used policy to evict entries from the cache. 

The frequency of each key is incremented on a `get` request. More information in examples directory.

## Choice of language

We wanted our cache to be extremely fast with low latency. There are a lot of new languages that are extremely fast. C++ was chosen to be our primary 
backend language for the following reasons:

- Gives us low level control of the memory
- Extremely fast and mature language
- Gives us the power to design our data structure in any way we so desire

The client for now is written in Python but we are looking for contributors to extend the use case to other languages as well/

## Getting Started

Let's start by understanding why we're doing this. I got interested in Redis and wanted to know how it works. The best way to learn something is by building it
and I hope you too learn something from this project and contribute something to it as well.

## The Framework

Instead of using complex methods, we'll use something called gRPC, which is a simpler and faster way for programs to talk to each other. This makes our project more efficient and easier to build.

## Components of RedisGrpcServer

Our system has three main parts:

1. **Controller**: It handles connections from other programs and sends their requests to the right place.
2. **Cache**: This is where we store the data. Think of it like a digital bookshelf where we keep our information.
3. **Registry**: It decides if we should store new information in the cache or get existing information from there.

## Implementation Details

We keep our system running smoothly by making sure we don't store too much data. We also make sure that when programs talk to each other, they do it quickly and without any delays.


### Cache Data Structure
 Our Cache data structure is a hashmap that stores a `std::string` as it's key and a `std::pair<std::string, int>` that corresponds to the value and the frequency of the key.
Visually it looks like this:

[Cache Data structure![](https://app.eraser.io/workspace/BuQcYkI5awNzJA2tpTs2/preview)](https://app.eraser.io/workspace/BuQcYkI5awNzJA2tpTs2)

Look at `Cache.hpp` or `Cache.cpp` for implementation details.

## Building and Running

### For Mac:

1. Go to the `redis-grpc-server` folder.
2. `mkdir build`
3. `cd build`
4. `cmake -DCMAKE_BUILD_TYPE=Debug .. && make -j16`
5. `./redis_grpc_server <optional argument as port number>`.

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

## TODO / Work in Progress
- Date completed: Mar 2, 2024; ~~Add the functionality to stop the server using a separate thread~~
- ~~Modify the cache to delete a particular set of elements based on their frequency~~
- Make a web client in flask to monitor the current status of the cache
- Add a proxy client running on a separate thread that reads the information from the cache and publishes it to the flask server
- ~~Change cache data structure from an unordered_map to an ordered_map~~
- ~~Make the cache persistent by saving the cache to a file~~
- ~~Document the code~~
- Possible make the python client part of the repo instead of a separate package
- Date completed: Mar 30, 2024; ~~Add Github actions to automate build for linux and mac~~


## How gRPC works
Here's a simplified explanation of how gRPC works:

1. **Service Definition**: First, you define a service and its methods using Protocol Buffers (protobuf). This service definition acts as a contract between the client and server, specifying the available methods and their parameters.

2. **Code Generation**: Using the service definition, you generate client and server code in your preferred programming languages. This generated code includes classes and methods that handle communication and data serialization/deserialization.

3. **Client-Server Communication**: When a client wants to communicate with the server, it calls the corresponding method on its generated gRPC client object. The client object serializes the request parameters into binary data using protobuf and sends it to the server.

4. **Server-Side Handling**: The server receives the request and forwards it to the appropriate method implementation. This method processes the request, performs any necessary computations, and prepares the response.

5. **Response Transmission**: Once the server has processed the request and generated a response, it serializes the response data into binary format using protobuf. The server then sends this binary response back to the client.

6. **Client-Side Handling**: Upon receiving the response, the client's gRPC client object deserializes the binary data into the corresponding data structures. It then returns the response to the client code that initiated the request.

7. **Bi-Directional Streaming**: gRPC also supports bi-directional streaming, where both client and server can send multiple messages asynchronously over a single connection. This is useful for real-time communication or long-lived connections.

For more information on how gRPC works look at the official doc: [gRPC](https://grpc.io)

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

