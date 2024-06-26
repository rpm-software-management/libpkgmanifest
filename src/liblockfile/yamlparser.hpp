#pragma once

#include "liblockfile/iyamlparser.hpp"

#include <yaml-cpp/yaml.h>

namespace liblockfile {

template <typename T>
class YamlParser : IYamlParser<T> {
public:
    YamlParser(const YAML::Parser & parser)
        : parser(parser) {}

    virtual T get(const std::string & key) const {
        // TODO
    }

private:
    YAML::Parser & parser;
};

}