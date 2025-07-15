// Copyright The libpkgmanifest Authors
// SPDX-License-Identifier: LGPL-2.1-or-later

#include "input.hpp"
#include "inputfactory.hpp"

namespace libpkgmanifest::internal::input {

using namespace libpkgmanifest::internal::common;

InputFactory::InputFactory(
    std::shared_ptr<IRepositoriesFactory> repositories_factory,
    std::shared_ptr<IVersionFactory> version_factory,
    std::shared_ptr<IPackagesFactory> packages_factory,
    std::shared_ptr<IModulesFactory> modules_factory,
    std::shared_ptr<IOptionsFactory> options_factory)
    : repositories_factory(std::move(repositories_factory))
    , version_factory(std::move(version_factory))
    , packages_factory(std::move(packages_factory))
    , modules_factory(std::move(modules_factory))
    , options_factory(std::move(options_factory)) {}

std::unique_ptr<IInput> InputFactory::create() const {
    auto input = std::make_unique<Input>();
    input->set_document(INPUT_DOCUMENT_ID);
    input->set_repositories(repositories_factory->create());
    input->set_packages(packages_factory->create());
    input->set_modules(modules_factory->create());
    input->set_options(options_factory->create());

    auto version = version_factory->create();
    version->set_major(INPUT_DOCUMENT_VERSION_MAJOR);
    version->set_minor(INPUT_DOCUMENT_VERSION_MINOR);
    version->set_patch(INPUT_DOCUMENT_VERSION_PATCH);
    input->set_version(std::move(version));

    return input;
}   

}