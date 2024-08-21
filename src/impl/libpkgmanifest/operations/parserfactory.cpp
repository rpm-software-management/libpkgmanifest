#include "parserfactory.hpp"
#include "parser.hpp"

#include "libpkgmanifest/objects/checksum/checksumfactory.hpp"
#include "libpkgmanifest/objects/checksum/checksumparser.hpp"
#include "libpkgmanifest/objects/package/packagefactory.hpp"
#include "libpkgmanifest/objects/package/packageparser.hpp"
#include "libpkgmanifest/objects/packages/packagesfactory.hpp"
#include "libpkgmanifest/objects/packages/packagesparser.hpp"
#include "libpkgmanifest/objects/manifest/manifestfactory.hpp"
#include "libpkgmanifest/objects/manifest/manifestparser.hpp"
#include "libpkgmanifest/objects/version/versionfactory.hpp"
#include "libpkgmanifest/objects/version/versionparser.hpp"
#include "libpkgmanifest/tools/stringsplitter.hpp"
#include "libpkgmanifest/yaml/yamlparser.hpp"

namespace libpkgmanifest::internal {

std::unique_ptr<IParser> ParserFactory::create() const {
    auto string_splitter = std::make_shared<StringSplitter>();

    auto checksum_factory = std::make_unique<ChecksumFactory>();
    auto checksum_parser = std::make_unique<ChecksumParser>(std::move(checksum_factory), string_splitter);

    auto package_factory = std::make_unique<PackageFactory>();
    auto package_parser = std::make_unique<PackageParser>(
        std::move(checksum_parser), 
        std::move(package_factory)
    );

    auto packages_factory = std::make_unique<PackagesFactory>();
    auto packages_parser = std::make_unique<PackagesParser>(
        std::move(package_parser), 
        std::move(packages_factory)
    );

    auto version_factory = std::make_unique<VersionFactory>();
    auto version_parser = std::make_unique<VersionParser>(std::move(version_factory), string_splitter);

    auto manifest_factory = std::make_unique<ManifestFactory>();
    auto manifest_parser = std::make_unique<ManifestParser>(
        std::move(manifest_factory), 
        std::move(packages_parser), 
        std::move(version_parser)
    );

    auto yaml_parser = std::make_unique<YamlParser>();

    return std::make_unique<Parser>(
        std::move(yaml_parser), 
        std::move(manifest_parser)
    );
}

}