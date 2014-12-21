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

#include <string>
#include "rdkafkacpp.h"

class kafka_writer {
public:
    kafka_writer(std::string brokers, std::string topicA) {
        conf = RdKafka::Conf::create(RdKafka::Conf::CONF_GLOBAL);
        tconf = RdKafka::Conf::create(RdKafka::Conf::CONF_TOPIC);
        set_brokers(brokers);
        create_producer();
        set_topic(topicA);
    }
    bool write(std::string message);
private:
    void set_brokers(std::string brokers);
    void set_topic(std::string topicA);
    void create_producer();
    RdKafka::Producer * producer;
    RdKafka::Conf * conf;
    RdKafka::Conf * tconf;
    RdKafka::Topic * topic;
    int32_t partition = RdKafka::Topic::PARTITION_UA;
};

void kafka_writer::set_topic(std::string topicA) {
    std::string errstr;
    RdKafka::Topic * topic = RdKafka::Topic::create(producer, topicA,
            tconf, errstr);
    if(!topic) {
        std::cerr << "create topic failed" << std::endl;
    }
}

bool kafka_writer::write(std::string messageA) {
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

void kafka_writer::set_brokers(std::string brokers) {
    std::string errstr;
    conf->set("metadata.broker.list", brokers, errstr);
}