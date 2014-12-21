/**
 * @file kafka_writer.hpp
 * @brief entry point for http-to-kafka application.
 * @author Stewart Henderson
 * @version 1.0
 * @date 2014
 * @copyright Copyright 2014 Stewart Henderson. All rights reserved.
 * @copyright Licensed under the MIT License
 * @copyright http://opensource.org/licenses/MIT
 */
#pragma once

#include <iostream>
#include <string>
#include "rdkafkacpp.h"

class kafka_writer {
public:
    kafka_writer(std::string brokers) {
        set_brokers(brokers);
        create_producer();
        conf = RdKafka::Conf::create(RdKafka::Conf::CONF_GLOBAL);
        tconf = RdKafka::Conf::create(RdKafka::Conf::CONF_TOPIC);
    }
    bool set_brokers(std::string brokers);
    bool write(std::string topic, std::string message);
private:
    void create_producer();
    RdKafka::Producer * producer;
    RdKafka::Conf * conf;
    RdKafka::Conf * tconf;
};

bool kafka_writer::write(std::string topicA, std::string messageA) {
    std::string errstr;
    RdKafka::Topic * topic = RdKafka::Topic::create(producer, topicA,
            tconf, errstr);
    if(!topic) {
        std::cerr << "create topic failed" << std::endl;
        return false;
    }
    int32_t partition = RdKafka::Topic::PARTITION_UA;
    RdKafka::ErrorCode resp =
            producer->produce(topic, partition,
                    RdKafka::Producer::MSG_COPY,
                    const_cast<char *>(messageA.c_str()), messageA.size(),
                    NULL, NULL);
    if(resp != RdKafka::ERR_NO_ERROR) {
        std::cerr << "producer error" << std::endl;
        return false;
    }
    return true;
}

void kafka_writer::create_producer() {
    std::string errstr;
    producer = RdKafka::Producer::create(conf, errstr);
}

bool kafka_writer::set_brokers(std::string brokers) {
    std::string errstr;
    return conf->set("metadata.broker.list", brokers, errstr) != RdKafka::Conf::CONF_OK;
}