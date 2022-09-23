#include <iostream>
#include <iomanip>

#include <cppkafka/cppkafka.h>

using namespace std;

int main() {
    // Create the config
    cppkafka::Configuration config = {
            { "metadata.broker.list", "127.0.0.1:9092" }
    };

    // Create the producer
    cppkafka::Producer producer(config);

    while (true) {
        string temperature = "24.7";

        // Create a message
        cppkafka::MessageBuilder builder("forecast");
        builder.payload(temperature);

        // Send the message
        producer.produce(builder);
        cout<<"Sent temperature: "<<temperature<< " at time: "<<time(nullptr)<<endl;

        this_thread::sleep_for(chrono::seconds(1));
    }
}
