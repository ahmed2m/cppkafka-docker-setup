docker-compose up -d --no-deps
sleep 5
docker exec -it kafka /bin/sh -c "cd /opt/kafka/bin && kafka-topics.sh --create --topic forecast --bootstrap-server localhost:9092"
