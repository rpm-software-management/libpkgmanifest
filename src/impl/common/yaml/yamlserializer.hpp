#pragma once

#include "iyamlserializer.hpp"

namespace libpkgmanifest::internal::common {

class FileOutputError : public std::runtime_error {
public:
    FileOutputError(const std::string & message);
};

class YamlSerializer : public IYamlSerializer {
public:
    virtual std::string to_string(const IYamlNode & node) const override;
    virtual void to_file(const IYamlNode & node, const std::string & path) const override;
};

}