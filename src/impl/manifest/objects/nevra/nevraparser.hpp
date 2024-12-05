#pragma once

#include "inevrafactory.hpp"
#include "inevraparser.hpp"

namespace libpkgmanifest::internal::manifest {

using namespace libpkgmanifest::internal::common;

class NevraParseError : public std::runtime_error {
public:
    NevraParseError(const std::string & message);
};

class NevraParser : public INevraParser {
public:
    NevraParser(std::shared_ptr<INevraFactory> nevra_factory);

    virtual std::unique_ptr<INevra> parse(const IYamlNode & node) const override;
    virtual std::unique_ptr<INevra> parse(const std::string & name, const std::string & arch, const IYamlNode & node) const override;

private:
    std::shared_ptr<INevraFactory> nevra_factory;
};

}