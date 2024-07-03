#pragma once

#include "istringsplitter.hpp"

namespace liblockfile {

class StringSplitter : public IStringSplitter {
public:
    virtual std::vector<std::string> split(const std::string & string, char delimiter) const override;
};

}