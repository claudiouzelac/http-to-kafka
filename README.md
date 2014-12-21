# HTTP-TO-KAFKA #

This server places a HTTP server in front of Kafka to allow the client to 
quickly post via a RESTful interface.

## Status ##

[![Build Status](https://travis-ci.org/bowlofstew/http-to-kafka.png)](https://travis-ci.org/bowlofstew/http-to-kafka)

## Prerequisites ##

  * BOOST 1.55+
  
  * CLang 3.4+

## Compilation ##

    `makedir build`
    
    `cmake ..`
    
    `make all`

## Usage ##

    `./http-to-kafka address port kafka-broker`
  
    `./http-to-kafka 0.0.0.0 8080 localhost:9092`

## Expected message format ##

The REST interface expects a POST request with a body in the 
following format:

    `
    {
      "topic":"",
      "payload":""
    }
    `
  
Where "topic" is the topic that you want your message to go into 
and "payload" is the message that you wish to place into the 
Kafka topic.


## License ##

    MIT
    
## CI ##

    https://travis-ci.org/bowlofstew/http-to-kafka

## Authors(s) ##

    Stewart Henderson<henderson.geoffrey@gmail.com>

