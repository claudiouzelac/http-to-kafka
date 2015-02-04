#pragma once

#include <fstream>
#include <set>
#include "rapidjson/document.h"

/**
* @file json_config.hpp
* @brief JSON configuration utility for loading JSON file from
*        the file system.
* @author Stewart Henderson
* @version 1.0
* @date 2014
* @copyright Copyright 2014 Stewart Henderson. All rights reserved.
* @copyright Licensed under the MIT License
* @copyright http://opensource.org/licenses/MIT
*/
class json_config {
public:
    json_config(std::string filePathA);
    std::string get_string(std::string keyA);
    int get_int(std::string keyA);
    std::string load_file(std::string filePathA);
    std::set<std::string>  get_strings(std::string keyA);
private:
    rapidjson::Document jsonM;
};

json_config::json_config(std::string filePathA) {
    std::string file = load_file(filePathA);
    jsonM.Parse(file.c_str());
}

std::string json_config::get_string(std::string keyA) {
    return jsonM[keyA.c_str()].GetString();
}

int json_config::get_int(std::string keyA) {
    return jsonM[keyA.c_str()].GetInt();
}

std::set<std::string> json_config::get_strings(std::string keyA) {
    std::set<std::string> strings;
    const rapidjson::Value& a = jsonM[keyA.c_str()];
    assert(a.IsArray());
    for (rapidjson::SizeType i = 0; i < a.Size(); i++) // Uses SizeType instead of size_t
       strings.insert(a[i].GetString());
    return strings;
}

std::string json_config::load_file(std::string filePathA) {
    std::ifstream input_file(filePathA, std::ifstream::in);
    std::stringstream sstr;
    sstr << input_file.rdbuf();
    return sstr.str();
}
