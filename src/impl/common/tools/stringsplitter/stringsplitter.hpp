#pragma once

#include "istringsplitter.hpp"

namespace libpkgmanifest::internal::common {

class StringSplitter : public IStringSplitter {
public:
    virtual std::vector<std::string> split(const std::string & string, char delimiter) const override;
};

}