#pragma once

#include <string>

namespace liblockfile {

template <typename T>
class IYamlParser {
public:
    virtual ~IYamlParser() = default;

    virtual T get(const std::string & key) const = 0;
};

}