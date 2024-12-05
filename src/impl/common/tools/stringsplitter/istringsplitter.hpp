#pragma once

#include <string>
#include <vector>

namespace libpkgmanifest::internal::common {

class IStringSplitter {
public:
    virtual ~IStringSplitter() = default;

    virtual std::vector<std::string> split(const std::string & string, char delimiter) const = 0;
};

}