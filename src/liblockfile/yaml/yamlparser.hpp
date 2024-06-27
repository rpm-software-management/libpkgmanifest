#pragma once

#include "iyamlparser.hpp"

#include <yaml-cpp/yaml.h>

namespace liblockfile {

class YamlFileError : public std::runtime_error {
public:
    YamlFileError(const std::string & message);
};

class YamlParseError : public std::runtime_error {
public:
    YamlParseError(const std::string & message);
};

class YamlParser : IYamlParser {
public:
    virtual std::unique_ptr<IYamlNode> from_string(const std::string & yaml) const override;
    virtual std::unique_ptr<IYamlNode> from_file(const std::string & path) const override;
};

}