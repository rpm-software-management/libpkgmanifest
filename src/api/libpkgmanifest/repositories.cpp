#include "repositories_impl.hpp"

#include "libpkgmanifest/repositories.hpp"

namespace libpkgmanifest {

Repositories::Repositories() : p_impl(std::make_unique<Impl>()) {}

Repositories::~Repositories() = default;

Repositories::Repositories(const Repositories & other) : p_impl(new Impl(*other.p_impl)) {}

Repositories & Repositories::operator=(const Repositories & other) {
    if (this != &other) {
        if (p_impl) {
            *p_impl = *other.p_impl;
        } else {
            p_impl = std::make_unique<Impl>(*other.p_impl);
        }
    }

    return *this;
}

Repositories::Repositories(Repositories && other) noexcept = default;
Repositories & Repositories::operator=(Repositories && other) noexcept = default;

std::map<std::string, Repository> Repositories::get() const {
    std::map<std::string, Repository> repositories_map;
    for (auto & [id, internal_repository] : p_impl->get()->get()) {
        Repository repository;
        repository.p_impl->init(internal_repository.get());
        repositories_map.insert({id, std::move(repository)});
    }
    return repositories_map;
}

Repository Repositories::get(const std::string & id) const {
    // TODO: Exception when no such repo

    auto & internal_repository = p_impl->get()->get()[id];

    Repository repository;
    repository.p_impl->init(internal_repository.get());
    return repository;
}

void Repositories::add(Repository & repository) {
    p_impl->get()->add(repository.p_impl->get_factory_object());
}

}