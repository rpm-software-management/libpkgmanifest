#pragma once

#include <memory>
#include <string>
#include <vector>

namespace libpkgmanifest::internal::input {

class IPackages {
public:
    virtual ~IPackages() = default;

    virtual std::unique_ptr<IPackages> clone() const = 0;

    virtual const std::vector<std::string> & get_installs() const = 0;
    virtual std::vector<std::string> & get_installs() = 0;
    virtual const std::vector<std::string> & get_reinstalls() const = 0;
    virtual std::vector<std::string> & get_reinstalls() = 0;
};

}