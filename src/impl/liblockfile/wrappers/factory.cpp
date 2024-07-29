#include "factory.hpp"
#include "parser.hpp"
#include "serializer.hpp"

#include "liblockfile/objects/checksum/checksumfactory.hpp"
#include "liblockfile/objects/checksum/checksumparser.hpp"
#include "liblockfile/objects/checksum/checksumserializer.hpp"
#include "liblockfile/objects/package/packagefactory.hpp"
#include "liblockfile/objects/package/packageparser.hpp"
#include "liblockfile/objects/package/packageserializer.hpp"
#include "liblockfile/objects/packages/packagesfactory.hpp"
#include "liblockfile/objects/packages/packagesparser.hpp"
#include "liblockfile/objects/packages/packagesserializer.hpp"
#include "liblockfile/objects/lockfile/lockfilefactory.hpp"
#include "liblockfile/objects/lockfile/lockfileparser.hpp"
#include "liblockfile/objects/lockfile/lockfileserializer.hpp"
#include "liblockfile/objects/version/versionfactory.hpp"
#include "liblockfile/objects/version/versionparser.hpp"
#include "liblockfile/objects/version/versionserializer.hpp"
#include "liblockfile/tools/stringsplitter.hpp"
#include "liblockfile/yaml/yamlnodefactory.hpp"
#include "liblockfile/yaml/yamlparser.hpp"
#include "liblockfile/yaml/yamlserializer.hpp"

namespace liblockfile::internal {

std::unique_ptr<IParser> Factory::create_parser() {
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

    auto lockfile_factory = std::make_unique<LockFileFactory>();
    auto lockfile_parser = std::make_unique<LockFileParser>(
        std::move(lockfile_factory), 
        std::move(packages_parser), 
        std::move(version_parser)
    );

    auto yaml_parser = std::make_unique<YamlParser>();

    return std::make_unique<Parser>(
        std::move(yaml_parser), 
        std::move(lockfile_parser)
    );
}

std::unique_ptr<ISerializer> Factory::create_serializer() {
    auto node_factory = std::make_shared<YamlNodeFactory>();

    auto checksum_serializer = std::make_unique<ChecksumSerializer>(node_factory);
    auto package_serializer = std::make_unique<PackageSerializer>(node_factory, std::move(checksum_serializer));
    auto packages_serializer = std::make_unique<PackagesSerializer>(node_factory, std::move(package_serializer));
    auto version_serializer = std::make_unique<VersionSerializer>(node_factory);

    auto lockfile_serializer = std::make_unique<LockFileSerializer>(
        node_factory, 
        std::move(packages_serializer), 
        std::move(version_serializer)
    );

    auto yaml_serializer = std::make_unique<YamlSerializer>();

    return std::make_unique<Serializer>(
        std::move(yaml_serializer), 
        std::move(lockfile_serializer)
    );
}

}