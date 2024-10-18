#include "input.hpp"
#include "inputfactory.hpp"

namespace libpkgmanifest::internal {

InputFactory::InputFactory(
    std::shared_ptr<IRepositoriesFactory> repositories_factory,
    std::shared_ptr<IVersionFactory> version_factory)
    : repositories_factory(repositories_factory)
    , version_factory(version_factory) {}

std::unique_ptr<IInput> InputFactory::create() const {
    throw;
}   

}