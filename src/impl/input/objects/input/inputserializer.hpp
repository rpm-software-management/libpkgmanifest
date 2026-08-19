// Copyright The libpkgmanifest Authors
// SPDX-License-Identifier: LGPL-2.1-or-later

#pragma once

#include "iinputserializer.hpp"
#include "impl/common/objects/repositories/irepositoriesserializer.hpp"
#include "impl/common/objects/version/iversionserializer.hpp"
#include "impl/common/yaml/iyamlnodefactory.hpp"
#include "impl/input/objects/modules/imodulesserializer.hpp"
#include "impl/input/objects/options/ioptionsserializer.hpp"
#include "impl/input/objects/packages/ipackagesserializer.hpp"

namespace libpkgmanifest::internal::input {

using namespace libpkgmanifest::internal::common;

class InputSerializer : public IInputSerializer {
public:
    InputSerializer(
        std::shared_ptr<IYamlNodeFactory> node_factory,
        std::unique_ptr<IPackagesSerializer> packages_serializer,
        std::unique_ptr<IRepositoriesSerializer> repositories_serializer,
        std::unique_ptr<IVersionSerializer> version_serializer,
        std::unique_ptr<IModulesSerializer> modules_serializer,
        std::unique_ptr<IOptionsSerializer> options_serializer);

    virtual std::unique_ptr<IYamlNode> serialize(const IInput & input) const override;

private:
    std::shared_ptr<IYamlNodeFactory> node_factory;
    std::unique_ptr<IPackagesSerializer> packages_serializer;
    std::unique_ptr<IRepositoriesSerializer> repositories_serializer;
    std::unique_ptr<IVersionSerializer> version_serializer;
    std::unique_ptr<IModulesSerializer> modules_serializer;
    std::unique_ptr<IOptionsSerializer> options_serializer;
};

}  // namespace libpkgmanifest::internal::input
