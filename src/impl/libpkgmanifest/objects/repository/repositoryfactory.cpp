#include "repository.hpp"
#include "repositoryfactory.hpp"

namespace libpkgmanifest::internal {

std::unique_ptr<IRepository> RepositoryFactory::create() const {
    return std::unique_ptr<IRepository>(new Repository());
}   

}