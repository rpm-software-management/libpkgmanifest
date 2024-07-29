#pragma once

#include "iparser.hpp"
#include "iserializer.hpp"

#include <memory>

namespace liblockfile::internal {

class Factory {
public:
    static std::unique_ptr<IParser> create_parser();
    static std::unique_ptr<ISerializer> create_serializer();
};

}