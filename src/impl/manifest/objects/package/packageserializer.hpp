// Copyright The libpkgmanifest Authors
// SPDX-License-Identifier: LGPL-2.1-or-later

#pragma once

#include "ipackageserializer.hpp"

#include "impl/manifest/objects/checksum/ichecksumserializer.hpp"
#include "impl/manifest/objects/module/imoduleserializer.hpp"
#include "impl/common/yaml/iyamlnodefactory.hpp"

namespace libpkgmanifest::internal::manifest {

using namespace libpkgmanifest::internal::common;

class PackageSerializer : public IPackageSerializer {
public:
    PackageSerializer(
        std::shared_ptr<IYamlNodeFactory> node_factory, 
        std::unique_ptr<IChecksumSerializer> checksum_serializer,
        std::unique_ptr<IModuleSerializer> module_serializer);

    virtual std::unique_ptr<IYamlNode> serialize(const IPackage & package) const override;

private:
    std::shared_ptr<IYamlNodeFactory> node_factory;
    std::unique_ptr<IChecksumSerializer> checksum_serializer;
    std::unique_ptr<IModuleSerializer> module_serializer;
};

}