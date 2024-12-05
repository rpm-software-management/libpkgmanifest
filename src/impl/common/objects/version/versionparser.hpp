#pragma once

#include "iversionfactory.hpp"
#include "iversionparser.hpp"

#include "impl/common/tools/stringsplitter/istringsplitter.hpp"

namespace libpkgmanifest::internal::common {

class VersionParser : public IVersionParser {
public:
    VersionParser(std::shared_ptr<IVersionFactory> version_factory, std::shared_ptr<IStringSplitter> string_splitter);

    virtual std::unique_ptr<IVersion> parse(const IYamlNode & node) const override;

private:
    std::shared_ptr<IVersionFactory> version_factory;
    std::shared_ptr<IStringSplitter> string_splitter;
};

}