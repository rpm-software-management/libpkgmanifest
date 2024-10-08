#pragma once

#include "ipackagefactory.hpp"
#include "ipackageparser.hpp"

#include "impl/libpkgmanifest/objects/checksum/ichecksumparser.hpp"
#include "impl/libpkgmanifest/objects/nevra/inevraparser.hpp"
#include "impl/libpkgmanifest/objects/module/imoduleparser.hpp"

namespace libpkgmanifest::internal {

class PackageParser : public IPackageParser {
public:
    PackageParser(
        std::unique_ptr<IChecksumParser> checksum_parser,
        std::unique_ptr<INevraParser> nevra_parser,
        std::unique_ptr<IModuleParser> module_parser,
        std::shared_ptr<IPackageFactory> package_factory);

    virtual std::unique_ptr<IPackage> parse(const std::string & arch, const IYamlNode & node) const override;

private:
    std::unique_ptr<IChecksumParser> checksum_parser;
    std::unique_ptr<INevraParser> nevra_parser;
    std::unique_ptr<IModuleParser> module_parser;
    std::shared_ptr<IPackageFactory> package_factory;
};

}