#pragma once

#include "iparser.hpp"

#include <memory>

namespace liblockfile {

class ParserFactory {
public:
    static std::unique_ptr<IParser> create();
};

}