FROM ubuntu:precise
RUN apt-get update -y
RUN DEBIAN_FRONTEND=noninteractive apt-get install libssl-dev curl git -y
RUN curl -L https://github.com/bowlofstew/http-to-kafka/releases/download/1.0-alpha/http-to-kafka > http-to-kafka
ADD src/config.json
ADD http-to-kafka /http-to-kafka
WORKDIR http-to-kafka
RUN ["http-to-kafka", "config.json"] 
