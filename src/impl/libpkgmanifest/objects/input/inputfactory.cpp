#include "input.hpp"
#include "inputfactory.hpp"

namespace libpkgmanifest::internal {

InputFactory::InputFactory(
    std::shared_ptr<IRepositoriesFactory> repositories_factory,
    std::shared_ptr<IVersionFactory> version_factory)
    : repositories_factory(repositories_factory)
    , version_factory(version_factory) {}

std::unique_ptr<IInput> InputFactory::create() const {
    auto input = std::make_unique<Input>();
    input->set_document(INPUT_DOCUMENT_ID);
    input->set_repositories(repositories_factory->create());

    auto version = version_factory->create();
    version->set_major(INPUT_DOCUMENT_VERSION_MAJOR);
    version->set_minor(INPUT_DOCUMENT_VERSION_MINOR);
    version->set_patch(INPUT_DOCUMENT_VERSION_PATCH);
    input->set_version(std::move(version));

    return input;
}   

}