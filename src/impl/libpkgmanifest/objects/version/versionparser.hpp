#pragma once

#include "iversionfactory.hpp"
#include "iversionparser.hpp"

#include "impl/libpkgmanifest/tools/istringsplitter.hpp"

namespace libpkgmanifest::internal {

class VersionParser : public IVersionParser {
public:
    VersionParser(std::shared_ptr<IVersionFactory> version_factory, std::shared_ptr<IStringSplitter> string_splitter);

    virtual std::unique_ptr<IVersion> parse(const IYamlNode & node) const override;

private:
    std::shared_ptr<IVersionFactory> version_factory;
    std::shared_ptr<IStringSplitter> string_splitter;
};

}