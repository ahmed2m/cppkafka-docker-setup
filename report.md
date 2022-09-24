# Dell task - Client/Server

This is a simple client/server application that demonstrates a publisher/subscriber pattern to send a message to connected clients.

Implemented in C++ using Kafka as a message broker and cppkafka client library to communicate with it. The final application is dockerized and can be run with docker-compose.

The usage of kafka might be unneeded but I believe most of the edge devices communicate with the central server using some kind of message broker, not relying on direct connections (like sockets or TCP connections).

The code is quite simple with the model API of `cppkafka` and the `kafka/zookeeper` docker image, the build system is CMake, and the dependency management is done with `vcpkg`.

`CMakeLists.txt` file includes some hacks to include cppkafka from vcpkg, because it's a port that is not yet fully supporting vcpkg from the maintainers side.

Usage instructions can be found in the [README](readme.md) also Archtiecture decision records (ADRs) are further explained there.
