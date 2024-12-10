#pragma once

#include "iinputfactory.hpp"

#include "impl/common/objects/repositories/irepositoriesfactory.hpp"
#include "impl/common/objects/version/iversionfactory.hpp"
#include "impl/input/objects/modules/imodulesfactory.hpp"
#include "impl/input/objects/options/ioptionsfactory.hpp"
#include "impl/input/objects/packages/ipackagesfactory.hpp"

namespace libpkgmanifest::internal::input {

using namespace libpkgmanifest::internal::common;

constexpr const char * INPUT_DOCUMENT_ID = "rpm-package-input";

constexpr int INPUT_DOCUMENT_VERSION_MAJOR = 0;
constexpr int INPUT_DOCUMENT_VERSION_MINOR = 0;
constexpr int INPUT_DOCUMENT_VERSION_PATCH = 1;

class InputFactory : public IInputFactory {
public:
    InputFactory(
        std::shared_ptr<IRepositoriesFactory> repositories_factory,
        std::shared_ptr<IVersionFactory> version_factory,
        std::shared_ptr<IPackagesFactory> packages_factory,
        std::shared_ptr<IModulesFactory> modules_factory,
        std::shared_ptr<IOptionsFactory> options_factory);

    virtual std::unique_ptr<IInput> create() const override;

private:
    std::shared_ptr<IRepositoriesFactory> repositories_factory;
    std::shared_ptr<IVersionFactory> version_factory;
    std::shared_ptr<IPackagesFactory> packages_factory;
    std::shared_ptr<IModulesFactory> modules_factory;
    std::shared_ptr<IOptionsFactory> options_factory;
};

}