docker-compose up -d --no-deps
timeout /t 5
docker exec kafka /bin/bash -c "cd /opt/kafka/bin; kafka-topics.sh --create --topic forecast --bootstrap-server localhost:9092"
