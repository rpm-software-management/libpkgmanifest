#include "repositories.hpp"
#include "repositoriesfactory.hpp"

namespace libpkgmanifest::internal {

std::unique_ptr<IRepositories> RepositoriesFactory::create() const {
    return std::unique_ptr<IRepositories>(new Repositories());
}   

}