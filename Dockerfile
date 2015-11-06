FROM ubuntu:precise
ADD https://github.com/bowlofstew/http-to-kafka/releases/download/1.0.1/http-to-kafka /kafka_http/
ADD src/config.json /kafka_http/
WORKDIR /kafka_http/
RUN chmod 744 http-to-kafka
CMD ./http-to-kafka config.json
