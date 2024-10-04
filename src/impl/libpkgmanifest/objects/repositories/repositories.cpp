#include "repositories.hpp"

namespace libpkgmanifest::internal {

Repositories::Repositories() {}

Repositories::Repositories(const Repositories & other) {
    for (const auto & [id, repository] : other.repositories) {
        repositories.insert({id, std::unique_ptr<IRepository>(repository->clone())});
    }
}

std::unique_ptr<IRepositories> Repositories::clone() const {
    return std::unique_ptr<IRepositories>(new Repositories(*this));
}

const std::map<std::string, std::unique_ptr<IRepository>> & Repositories::get() const {
    return repositories;
}

std::map<std::string, std::unique_ptr<IRepository>> & Repositories::get() {
    return repositories;
}

void Repositories::add(std::unique_ptr<IRepository> repository) {
    repositories[repository->get_id()] = std::move(repository);
}

}