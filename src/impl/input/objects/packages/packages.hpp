#pragma once

#include "ipackages.hpp"

namespace libpkgmanifest::internal::input {

class Packages : public IPackages {
public:
    Packages();

    virtual std::unique_ptr<IPackages> clone() const override;

    virtual const std::vector<std::string> & get_installs() const override;
    virtual std::vector<std::string> & get_installs() override;
    virtual const std::vector<std::string> & get_reinstalls() const override;
    virtual std::vector<std::string> & get_reinstalls() override;

private:
    std::vector<std::string> installs;
    std::vector<std::string> reinstalls;
};

}