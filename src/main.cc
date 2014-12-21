/**
 * @file main.cc
 * @brief entry point for http-to-kafka application.
 * @author Stewart Henderson
 * @version 1.0
 * @date 2014
 * @copyright Copyright 2014 Stewart Henderson. All rights reserved.
 * @copyright Licensed under the MIT License
 * @copyright http://opensource.org/licenses/MIT
 */
#include <iostream>
#include <boost/network/protocol/http/server.hpp>
#include "rapidjson/document.h"
#include "kafka_writer.hpp"

std::string broker_list;
namespace http = boost::network::http;

struct handler;
typedef http::server<handler> server;

struct handler {
    void operator()(server::request const &request, server::response &response) {
        server::string_type ip = source(request);
        //TODO: Add logging.
        std::cout << "request ip=" << ip << std::endl;
        std::string json = request.body;
        std::ostringstream data;
        if(json.size() == 0) {
            data << "no message provided" << std::endl;
            response = server::response::stock_reply(server::response::ok, data.str());
        } else {
            //TODO: Cache the writers for later re-use.
            kafka_writer * writer = new kafka_writer("kafka-1.qa.ciq-internal.net:9092");
            rapidjson::Document d;
            try {
                d.Parse<0>(json.c_str());
                std::string topic = d["topic"].GetString();
                std::string payload = d["payload"].GetString();
                if(!writer->write(topic, payload)) {
                    std::cerr << "kafka write failed to topic=" << topic << std::endl;
                }
            } catch(...) {
                std::cerr << "failed to send message" << std::endl;
            }
            free(writer);
            data << "OK" << std::endl;
            response = server::response::stock_reply(server::response::ok, data.str());
        }
    }
    void log(...) {
    }
};

int main(int argc, char *argv[]) {
    if (argc != 4) {
        std::cerr << "Usage: " << argv[0] << " address port brokers" << std::endl;
        return 1;
    }
    try {
        broker_list = argv[3];
        handler handler;
        server::options options(handler);
        server server_(options.address(argv[1]).port(argv[2]));
        server_.run();
    }
    catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    return 0;
}
