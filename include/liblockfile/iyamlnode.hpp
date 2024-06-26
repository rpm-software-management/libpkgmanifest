#pragma once

#include <memory>
#include <stdint.h>
#include <string>
#include <vector>

namespace liblockfile {

class IYamlNode {
public:
    virtual ~IYamlNode() = default;

    virtual std::unique_ptr<IYamlNode> get(const std::string & key) const = 0;

    virtual std::string as_string() const = 0;
    virtual int as_int() const = 0;
    virtual uint64_t as_uint64() const = 0;
    virtual std::vector<std::unique_ptr<IYamlNode>> as_list() const = 0;
};

}