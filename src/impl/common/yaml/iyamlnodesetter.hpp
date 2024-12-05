#pragma once

#include "iyamlnode.hpp"

#include <memory>
#include <stdint.h>
#include <string>
#include <vector>

namespace libpkgmanifest::internal::common {

class IYamlNodeSetter {
public:
    virtual ~IYamlNodeSetter() = default;

    virtual void set(const std::string & value) = 0;
    // to prevent implicit conversions of char * -> bool
    virtual void set(const char * value) = 0;
    virtual void set(bool value) = 0;
    virtual void set(int value) = 0;
    virtual void set(unsigned value) = 0;
    virtual void set(uint64_t value) = 0;
    virtual void add(std::unique_ptr<IYamlNode> value) = 0;
    virtual void insert(const std::string & key, std::unique_ptr<IYamlNode> value) = 0;
};

}