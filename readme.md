# Temperature sensors simulation - Client/Server (Kafka)

This is a simple client/server application that demonstrates a publisher/subscriber pattern to send a message to connected clients.

Used Kafka as a message broker and cppkafka client library to communicate with it.

The server is a simple C++ application that uses cppkafka library to communicate with Kafka. It is a simple publisher that sends a message to a topic.

The client(s) are simple subscribers that receive a message from a topic that they're subscribed to.

## Architectural Decision Records (ADRs)

- **vspkg** for dependency management.
  - Used vcpkg for dependency management to keep package management simple and consistent across platforms.
- **kafka** as a message broker.
  - Kafka is used for building real-time data pipelines and streaming apps. It is scalable, fast and fault-tolerant. [[1]](https://www.kafka-summit.org/about-kafka/)
  - Maybe the straight forward solution would be ASIO sockets with boost or something similar, but I wanted to try Kafka with C++ seemed like a good fit for this task and a new challenge (I only used Python with ELK+Kafka before). 
  - Can be easily attached to **ELK stack** for logging and monitoring purposes, with **Kibana** as a dashboard.
- **cppkafka** as a C++ client library for Kafka.
  - Found another client `librdkafka` but it was a bit more complicated to use.
  - `cppkafka` is basically a wrapper around `librdkafka` but with a simpler API, and it utilizes modern C++ features. 
- **docker-compose** used to easily manage the containers and the environment variables, the kafka image is from `wurstmeister` and I only build the project image once and use it with the client and server services with different environment variables.

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

To run a client:
```bash
docker-compose run client
```


## To do

- [ ] Add tests.
  - [ ] Checkout gtest or boost for tests.
- [ ] Handle client group id dynamically (group id being hard coded causes some conflicts when running multiple clients).
