// Copyright The libpkgmanifest Authors
// SPDX-License-Identifier: LGPL-2.1-or-later

#pragma once

#include "imanifestserializer.hpp"

#include "impl/common/objects/repositories/irepositoriesserializer.hpp"
#include "impl/common/objects/version/iversionserializer.hpp"
#include "impl/common/yaml/iyamlnodefactory.hpp"
#include "impl/manifest/objects/packages/ipackagesserializer.hpp"
#include "impl/manifest/operations/packagerepositorybinder/ipackagerepositorybinder.hpp"

namespace libpkgmanifest::internal::manifest {

using namespace libpkgmanifest::internal::common;

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