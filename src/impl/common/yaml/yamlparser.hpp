#pragma once

#include "iyamlparser.hpp"

namespace libpkgmanifest::internal::common {

class YamlFileError : public std::runtime_error {
public:
    YamlFileError(const std::string & message);
};

class YamlParseError : public std::runtime_error {
public:
    YamlParseError(const std::string & message);
};

class YamlParser : public IYamlParser {
public:
    virtual std::unique_ptr<IYamlNode> from_string(const std::string & yaml) const override;
    virtual std::unique_ptr<IYamlNode> from_file(const std::string & path) const override;
};

}