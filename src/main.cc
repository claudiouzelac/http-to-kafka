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
#include <string>
#include <iostream>
#include <set>
#include <map>

#include <boost/network/protocol/http/server.hpp>
#include "json_config.hpp"
#include "kafka_writer.hpp"

namespace http = boost::network::http;

struct handler;
typedef http::server<handler> server;

std::map<std::string,kafka_writer*> producers_by_topic;

/**
 *
 */
struct handler {
    void operator()(server::request const &request, server::response &response) {
        server::string_type ip = source(request);
        std::ostringstream data;
        std::string requested_topic = request.destination.erase(0, 1);

        kafka_writer * writer;
        std::map<std::string,kafka_writer*>::iterator it = producers_by_topic.find(requested_topic);
        if(it != producers_by_topic.end()) {
            std::string message = request.body;
            if(message.size() == 0) {
                data << "no message provided" << std::endl;
                response = server::response::stock_reply(server::response::ok, data.str());
            } else {
                writer = it->second;
                writer->write(message);
                data << "OK" << std::endl;
                response = server::response::stock_reply(server::response::ok, data.str());
            }
        } else {
            data << "topic not available" << std::endl;
            response = server::response::stock_reply(server::response::ok, data.str());
        }
    }
    void log(...) {
    }
};

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " json config" << std::endl;
        return 1;
    }
    try {
        json_config config(argv[1]);
        std::string server_address = config.get_string("address");
        std::string server_port = config.get_string("port");
        std::string broker_list = config.get_string("kafka-brokers");
        std::set<std::string> topics = config.get_strings("topics");
        std::set<std::string>::iterator it;
        for (it = topics.begin(); it != topics.end(); ++it) {
            std::cout << (*it).c_str() << std::endl;
            producers_by_topic[(*it).c_str()]= new kafka_writer(broker_list, *it);
        }
        handler handler;
        server::options options(handler);
        server server_(options.address(server_address).port(server_port));
        server_.run();
    }
    catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    return 0;
}
