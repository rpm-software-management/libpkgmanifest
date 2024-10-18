#pragma once

#include "iinputfactory.hpp"

#include "impl/libpkgmanifest/objects/repositories/irepositoriesfactory.hpp"
#include "impl/libpkgmanifest/objects/version/iversionfactory.hpp"

namespace libpkgmanifest::internal {

constexpr const char * INPUT_DOCUMENT_ID = "rpm-package-input";

constexpr int INPUT_DOCUMENT_VERSION_MAJOR = 0;
constexpr int INPUT_DOCUMENT_VERSION_MINOR = 0;
constexpr int INPUT_DOCUMENT_VERSION_PATCH = 1;

class InputFactory : public IInputFactory {
public:
    InputFactory(
        std::shared_ptr<IRepositoriesFactory> repositories_factory,
        std::shared_ptr<IVersionFactory> version_factory);

    virtual std::unique_ptr<IInput> create() const override;

private:
    std::shared_ptr<IRepositoriesFactory> repositories_factory;
    std::shared_ptr<IVersionFactory> version_factory;
};

}