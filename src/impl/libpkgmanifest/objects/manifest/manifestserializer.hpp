#pragma once

#include "imanifestserializer.hpp"

#include "libpkgmanifest/objects/packages/ipackagesserializer.hpp"
#include "libpkgmanifest/objects/repositories/irepositoriesserializer.hpp"
#include "libpkgmanifest/objects/version/iversionserializer.hpp"
#include "libpkgmanifest/operations/ipackagerepositorybinder.hpp"
#include "libpkgmanifest/yaml/iyamlnodefactory.hpp"

namespace libpkgmanifest::internal {

class ManifestSerializer : public IManifestSerializer {
public:
    ManifestSerializer(
        std::shared_ptr<IYamlNodeFactory> node_factory, 
        std::unique_ptr<IPackagesSerializer> packages_serializer,
        std::unique_ptr<IRepositoriesSerializer> repositories_serializer,
        std::unique_ptr<IVersionSerializer> version_serializer,
        std::shared_ptr<IPackageRepositoryBinder> binder);

    virtual std::unique_ptr<IYamlNode> serialize(const IManifest & manifest) const override;

private:
    std::shared_ptr<IYamlNodeFactory> node_factory;
    std::unique_ptr<IPackagesSerializer> packages_serializer;
    std::unique_ptr<IRepositoriesSerializer> repositories_serializer;
    std::unique_ptr<IVersionSerializer> version_serializer;
    std::shared_ptr<IPackageRepositoryBinder> binder;
};

}