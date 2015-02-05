FROM ubuntu:precise
RUN apt-get update -y
RUN DEBIAN_FRONTEND=noninteractive apt-get install libssl-dev curl git -y
ADD https://github.com/bowlofstew/http-to-kafka/releases/download/1.0-alpha/http-to-kafka /kafka_http/
ADD src/config.json /kafka_http/
WORKDIR /kafka_http/
RUN ["http-to-kafka", "config.json"] 
