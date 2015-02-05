# HTTP-TO-KAFKA #

This server places a HTTP server in front of Kafka to allow the client to 
quickly post via a RESTful interface.

## Status ##

[![Build Status](https://travis-ci.org/bowlofstew/http-to-kafka.png)](https://travis-ci.org/bowlofstew/http-to-kafka)

## Prerequisites ##

  * BOOST 1.55+
  
  * CLang 3.4+

## Compilation ##

    makedir build
    
    cmake ..
    
    make all

## Usage ##

    ./http-to-kafka {config file}

## Configuration ##

The configuration is stored in the config.json file and looks like:

  ```json
  {
    "address": "0.0.0.0",
    "port": "8084",
    "kafka-brokers": "localhost:9092",
    "topics": ["topic1", "topic2"]
  }
  ```
  
  Where address is the server address, port is the server port, kafka-brokers
  are the Kafka brokers that this service connects to and topics are the permitted
  topics that this service may publish to.  Once configured and running you can 
  simply post to the server topics like:
  
  POST http://0.0.0.0:8084/topic1
  
  POST http://0.0.0.0:8084/topic2

## Expected message format ##

The REST interface expects a POST request.  The body will
be the body of your Kafka message.

## License ##

    MIT
    
## CI ##

    https://travis-ci.org/bowlofstew/http-to-kafka

## Authors(s) ##

    Stewart Henderson<henderson.geoffrey@gmail.com>

