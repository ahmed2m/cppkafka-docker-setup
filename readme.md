# Dell task - Client/Server

This is a simple client/server application that demonstrates a publisher/subscriber pattern to send a message to connected clients.

Used Kafka as a message broker and cppkafka client library to communicate with it.

The server is a simple C++ application that uses cppkafka library to communicate with Kafka. It is a simple publisher that sends a message to a topic.

The client(s) are simple subscribers that receive a message from a topic that they're subscribed to.

## How to run

Docker is required to run the application, at least to run kafka and zookeeper.

### Run Kafka and Zookeeper

Run the provided bash and bat scripts (depends on your OS) to run Kafka and Zookeeper and create the relevant topics.
`docker_script.bash` or `docker_script.bat`

### Running the server and client(s)
#### To run locally

To run the server and client locally you'd have to have vcpgk installed (on Windows Visual Studio is required to build) and run the following commands:

```bash
cmake . -DCMAKE_TOOLCHAIN_FILE={path_to_vcpkg}/scripts/buildsystems/vcpkg.cmake && cmake --build .
```
Then run the server and client executables.


#### To run with docker

The server and the client containers are built from the same image, only environment variables are different.

To run the server:
```bash
docker-compose run server
```

To run one client:
```bash
docker-compose run client
```
