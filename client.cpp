#include <stdexcept>
#include <iostream>
#include <csignal>

#include <cppkafka/cppkafka.h>

using namespace std;

bool running = true;

int main() {
    // Stop processing on SIGINT
    signal(SIGINT, [](int) { running = false; });

    auto brokersHost = getenv("KAFKA_BROKERS");
    if(brokersHost == nullptr) {
        brokersHost = strdup("127.0.0.1:9092");
        cout<<"Using default Kafka host: "<<brokersHost<<endl;
    }

    // Create the config
    cppkafka::Configuration config = {
            { "metadata.broker.list", brokersHost },
            { "group.id",             1 },
    };

    // Create the consumer
    cppkafka::Consumer consumer(config);

    // Subscribe to the topic
    consumer.subscribe({ "forecast" });

    int count = 0;
    double sum = 0.0;
    double average = 0.0;
    auto start = chrono::steady_clock::now();
    while (running) {
        double temperature;
        cppkafka::Message msg = consumer.poll();
        if (msg) {
            if (msg.get_error()) {
                cout << "ERROR: " << msg.get_error() << endl;
            }
            else {
                temperature = stod(msg.get_payload());
                sum += temperature;
                count++;
                average = sum / count;
                consumer.commit(msg);
            }
        }
        auto end = chrono::steady_clock::now();
        if (chrono::duration_cast<chrono::seconds>(end - start).count() >= 5) {
            cout << "Average temperature: " << average << " at time: " << time(nullptr) << endl;
            cout << "Accumulated temperature: " << sum << endl;
            cout << "Number of samples: " << count << endl;
            cout << "----------------------------------------" << endl;
            start = chrono::steady_clock::now();
        }
    }
}