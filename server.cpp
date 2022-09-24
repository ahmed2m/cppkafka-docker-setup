#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <random>

#include <cppkafka/cppkafka.h>

using namespace std;

// create a random number generator for temperature
random_device rd;
default_random_engine engine(rd());

int main() {
    auto brokersHost = getenv("KAFKA_BROKERS");
    if(brokersHost == nullptr) {
        brokersHost = strdup("127.0.0.1:9094");
        cout<<"Using default Kafka host: "<<brokersHost<<endl;
    }

    // Create the config
    cppkafka::Configuration config = {
            { "metadata.broker.list", brokersHost },
    };

    // Create the producer
    cppkafka::Producer producer(config);

    uniform_real_distribution<double> starting_gen(10.0, 45.9);
    double past_temperature = starting_gen(engine);
    while (true) {
        uniform_real_distribution<double> dist(past_temperature - 0.5, past_temperature + 0.5);

        // Create a random temperature rounded to 2 points and convert it to a string
        // Used string stream because to_string() has trailing zeros problem
        auto random_temp = dist(engine);
        past_temperature = random_temp;
        stringstream ss;
        ss << fixed << setprecision(2) << random_temp;
        string temperature = ss.str();

        // Create a message
        cppkafka::MessageBuilder builder("forecast");
        builder.payload(temperature);

        // Send the message
        producer.produce(builder);
        cout << "Sent temperature: " << temperature << " at time: " << time(nullptr) << endl;

        this_thread::sleep_for(chrono::seconds(1));
    }
}
