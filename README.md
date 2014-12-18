# HTTP-TO-KAFKA #

This server places a HTTP server in front of Kafka to allow the client to 
quickly post via a RESTful interface.

## PREREQUISITES ##

  * BOOST 1.55+
  
  * GCC 4.8+

## COMPILATION ##

    `makedir build`
    
    `cmake ..`
    
    `make all`

## USAGE ##

    `./http-to-kafka address port kafka-broker`
  
    `./http-to-kafka 0.0.0.0 8080 localhost:9092`

## EXPECTED MESSAGE FORMAT ##

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

## LICENSE ##

    MIT

## AUTHOR(s) ##

    Stewart Henderson<henderson.geoffrey@gmail.com>

