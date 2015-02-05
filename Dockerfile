FROM ubuntu:precise
RUN apt-get update -y
RUN DEBIAN_FRONTEND=noninteractive apt-get install libssl-dev curl git -y
ADD https://github.com/bowlofstew/http-to-kafka/releases/download/untagged-8b6a37f3b5ed86d773d8/http-to-kafka /kafka_http/
ADD src/config.json /kafka_http/
WORKDIR /kafka_http/
RUN ["http-to-kafka", "config.json"] 
