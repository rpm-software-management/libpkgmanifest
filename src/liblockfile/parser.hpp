#pragma once

#include "liblockfile/iparser.hpp"

namespace liblockfile {

class Parser : IParser {
public:
    virtual std::unique_ptr<ILockFile> parse(const std::string & path) const override;
};

}