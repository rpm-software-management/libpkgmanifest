#pragma once

#include "iyamlnode.hpp"

#include <yaml-cpp/yaml.h>

namespace liblockfile {

class YamlUnknownKeyError : public std::runtime_error {
public:
    YamlUnknownKeyError(const std::string & message);
};

class YamlInvalidValueConversionError : public std::runtime_error {
public:
    YamlInvalidValueConversionError(const std::string & message);
};

class YamlNode : public IYamlNode {
public:
    YamlNode(const YAML::Node & node);

    virtual std::unique_ptr<IYamlNode> get(const std::string & key) const override;

    virtual std::string as_string() const override;
    virtual int as_int() const override;
    virtual unsigned as_uint() const override;
    virtual uint64_t as_uint64() const override;
    virtual std::vector<std::unique_ptr<IYamlNode>> as_list() const override;
    virtual std::map<std::string, std::unique_ptr<IYamlNode>> as_map() const override;

private:
    template<typename T>
    T as() const {
        try {
            return node.as<T>();
        } catch(YAML::TypedBadConversion<T> & ex) {
            throw YamlInvalidValueConversionError(ex.msg);
        }
    }

    YAML::Node node;
};

}