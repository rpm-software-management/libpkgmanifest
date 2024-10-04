#include "parserfactory.hpp"
#include "parser.hpp"

#include "libpkgmanifest/objects/checksum/checksumfactory.hpp"
#include "libpkgmanifest/objects/checksum/checksumparser.hpp"
#include "libpkgmanifest/objects/module/modulefactory.hpp"
#include "libpkgmanifest/objects/module/moduleparser.hpp"
#include "libpkgmanifest/objects/nevra/nevrafactory.hpp"
#include "libpkgmanifest/objects/nevra/nevraparser.hpp"
#include "libpkgmanifest/objects/package/packagefactory.hpp"
#include "libpkgmanifest/objects/package/packageparser.hpp"
#include "libpkgmanifest/objects/packages/packagesfactory.hpp"
#include "libpkgmanifest/objects/packages/packagesparser.hpp"
#include "libpkgmanifest/objects/repository/repositoryfactory.hpp"
#include "libpkgmanifest/objects/repository/repositoryparser.hpp"
#include "libpkgmanifest/objects/repositories/repositoriesfactory.hpp"
#include "libpkgmanifest/objects/repositories/repositoriesparser.hpp"
#include "libpkgmanifest/objects/manifest/manifestfactory.hpp"
#include "libpkgmanifest/objects/manifest/manifestparser.hpp"
#include "libpkgmanifest/objects/version/versionfactory.hpp"
#include "libpkgmanifest/objects/version/versionparser.hpp"
#include "libpkgmanifest/operations/packagerepositorybinder.hpp"
#include "libpkgmanifest/tools/stringsplitter.hpp"
#include "libpkgmanifest/yaml/yamlparser.hpp"

namespace libpkgmanifest::internal {

std::unique_ptr<IParser> ParserFactory::create() const {
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
    auto repositories_parser = std::make_unique<RepositoriesParser>(std::move(repository_parser), repositories_factory);

    auto version_factory = std::make_shared<VersionFactory>();
    auto version_parser = std::make_unique<VersionParser>(version_factory, string_splitter);

    auto binder = std::make_shared<PackageRepositoryBinder>();

    auto manifest_factory = std::make_unique<ManifestFactory>(
        packages_factory, 
        repositories_factory, 
        version_factory, 
        binder);

    auto manifest_parser = std::make_unique<ManifestParser>(
        std::move(manifest_factory),
        std::move(packages_parser),
        std::move(repositories_parser),
        std::move(version_parser),
        binder
    );

    auto yaml_parser = std::make_unique<YamlParser>();

    return std::make_unique<Parser>(
        std::move(yaml_parser), 
        std::move(manifest_parser)
    );
}

}