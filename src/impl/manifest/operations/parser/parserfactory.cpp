#include "parserfactory.hpp"
#include "parser.hpp"

#include "impl/common/objects/repository/repositoryfactory.hpp"
#include "impl/common/objects/repository/repositoryparser.hpp"
#include "impl/common/objects/repositories/repositoriesfactory.hpp"
#include "impl/common/objects/repositories/repositoriesparser.hpp"
#include "impl/common/objects/version/versionfactory.hpp"
#include "impl/common/objects/version/versionparser.hpp"
#include "impl/common/tools/stringsplitter/stringsplitter.hpp"
#include "impl/common/yaml/yamlparser.hpp"
#include "impl/common/yaml/yamlnodefactory.hpp"
#include "impl/manifest/objects/checksum/checksumfactory.hpp"
#include "impl/manifest/objects/checksum/checksumparser.hpp"
#include "impl/manifest/objects/manifest/manifestfactory.hpp"
#include "impl/manifest/objects/manifest/manifestparser.hpp"
#include "impl/manifest/objects/module/modulefactory.hpp"
#include "impl/manifest/objects/module/moduleparser.hpp"
#include "impl/manifest/objects/nevra/nevrafactory.hpp"
#include "impl/manifest/objects/nevra/nevraparser.hpp"
#include "impl/manifest/objects/package/packagefactory.hpp"
#include "impl/manifest/objects/package/packageparser.hpp"
#include "impl/manifest/objects/packages/packagesfactory.hpp"
#include "impl/manifest/objects/packages/packagesparser.hpp"
#include "impl/manifest/operations/packagerepositorybinder/packagerepositorybinder.hpp"

namespace libpkgmanifest::internal::manifest {

using namespace libpkgmanifest::internal::common;

std::unique_ptr<IParser> ParserFactory::create() const {
    auto node_factory = std::make_shared<YamlNodeFactory>();
    auto string_splitter = std::make_shared<StringSplitter>();

    auto checksum_factory = std::make_shared<ChecksumFactory>();
    auto checksum_parser = std::make_unique<ChecksumParser>(checksum_factory, string_splitter);

    auto nevra_factory = std::make_shared<NevraFactory>();
    auto nevra_parser = std::make_unique<NevraParser>(nevra_factory);

    auto module_factory = std::make_shared<ModuleFactory>();
    auto module_parser = std::make_unique<ModuleParser>(module_factory, string_splitter);

    auto package_factory = std::make_shared<PackageFactory>(checksum_factory, nevra_factory, module_factory);
    auto package_parser = std::make_unique<PackageParser>(
        std::move(checksum_parser),
        std::move(nevra_parser),
        std::move(module_parser),
        std::move(package_factory)
    );

    auto packages_factory = std::make_shared<PackagesFactory>();
    auto packages_parser = std::make_unique<PackagesParser>(
        std::move(package_parser),
        packages_factory
    );

    auto repository_factory = std::make_shared<RepositoryFactory>();
    auto repository_parser = std::make_unique<RepositoryParser>(repository_factory);

    auto repositories_factory = std::make_shared<RepositoriesFactory>();
    auto repositories_parser = std::make_shared<RepositoriesParser>(std::move(repository_parser), repositories_factory);

    auto version_factory = std::make_shared<VersionFactory>();
    auto version_parser = std::make_shared<VersionParser>(version_factory, string_splitter);

    auto binder = std::make_shared<PackageRepositoryBinder>();

    auto manifest_factory = std::make_unique<ManifestFactory>(
        packages_factory, 
        repositories_factory, 
        version_factory, 
        binder);

    auto manifest_parser = std::make_unique<ManifestParser>(
        std::move(manifest_factory),
        std::move(packages_parser),
        repositories_parser,
        version_parser,
        binder
    );

    auto yaml_parser = std::make_unique<YamlParser>();

    return std::make_unique<Parser>(
        std::move(yaml_parser),
        std::move(manifest_parser)
    );
}

}