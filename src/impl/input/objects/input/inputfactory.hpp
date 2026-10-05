// Copyright The libpkgmanifest Authors
// SPDX-License-Identifier: LGPL-2.1-or-later

#pragma once

#include "iinputfactory.hpp"
#include "impl/common/objects/repositories/irepositoriesfactory.hpp"
#include "impl/common/objects/version/version.hpp"
#include "impl/input/objects/modules/imodulesfactory.hpp"
#include "impl/input/objects/options/ioptionsfactory.hpp"
#include "impl/input/objects/packages/ipackagesfactory.hpp"
#include "libpkgmanifest/input/input.hpp"

namespace libpkgmanifest::internal::input {

using namespace libpkgmanifest::internal::common;

constexpr const char * INPUT_DOCUMENT_ID = libpkgmanifest::input::INPUT_DOCUMENT_IDENTIFIER;

inline const Version INPUT_DOCUMENT_VERSION = [] {
    Version version;
    version.set_major(libpkgmanifest::input::CURRENT_INPUT_SCHEMA_VERSION.get_major());
    version.set_minor(libpkgmanifest::input::CURRENT_INPUT_SCHEMA_VERSION.get_minor());
    version.set_patch(libpkgmanifest::input::CURRENT_INPUT_SCHEMA_VERSION.get_patch());
    return version;
}();

inline std::string input_document_version_string() {
    return std::to_string(INPUT_DOCUMENT_VERSION.get_major()) + "." +
           std::to_string(INPUT_DOCUMENT_VERSION.get_minor()) + "." +
           std::to_string(INPUT_DOCUMENT_VERSION.get_patch());
}

class InputFactory : public IInputFactory {
public:
    InputFactory(
        std::shared_ptr<IRepositoriesFactory> repositories_factory,
        std::shared_ptr<IPackagesFactory> packages_factory,
        std::shared_ptr<IModulesFactory> modules_factory,
        std::shared_ptr<IOptionsFactory> options_factory);

    virtual std::unique_ptr<IInput> create() const override;

private:
    std::shared_ptr<IRepositoriesFactory> repositories_factory;
    std::shared_ptr<IPackagesFactory> packages_factory;
    std::shared_ptr<IModulesFactory> modules_factory;
    std::shared_ptr<IOptionsFactory> options_factory;
};

}  // namespace libpkgmanifest::internal::input
