#include "repository.hpp"
#include "repositoryfactory.hpp"

namespace libpkgmanifest::internal::common {

std::unique_ptr<IRepository> RepositoryFactory::create() const {
    return std::make_unique<Repository>();
}   

}