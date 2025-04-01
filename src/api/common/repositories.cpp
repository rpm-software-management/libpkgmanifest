#include "repositories_impl.hpp"

#include "libpkgmanifest/common/repositories.hpp"

#include <vector>

namespace libpkgmanifest::common {

NoSuchRepositoryIdError::NoSuchRepositoryIdError(const std::string & message) : std::runtime_error(message) {}

Repositories::Repositories() : p_impl(std::make_unique<Impl>()) {}

Repositories::~Repositories() = default;

Repositories::Repositories(const Repositories & other) : p_impl(new Impl(*other.p_impl)) {}

Repositories & Repositories::operator=(const Repositories & other) {
    if (this != &other) {
        *p_impl = *other.p_impl;
    }
    return *this;
}

Repositories::Repositories(Repositories && other) noexcept = default;
Repositories & Repositories::operator=(Repositories && other) noexcept = default;

bool Repositories::contains(const std::string & id) const {
    return p_impl->get()->get().contains(id);
}

std::size_t Repositories::size() const {
    return p_impl->get()->get().size();
}

Repository Repositories::get(const std::string & id) const {
    if (!contains(id)) {
        throw NoSuchRepositoryIdError("Repository with ID \"" + id + "\" does not exist.");
    }

    Repository repository;
    repository.p_impl->init(p_impl->get()->get()[id].get());
    return repository;
}

void Repositories::add(Repository & repository) {
    p_impl->get()->add(repository.p_impl->get_owned_object());
}

RepositoriesIterator Repositories::begin() {
    RepositoriesIterator iterator(this);
    iterator.p_impl->set(p_impl->get()->get().begin());
    return iterator;
}

RepositoriesIterator Repositories::end() {
    RepositoriesIterator iterator(this);
    iterator.p_impl->set(p_impl->get()->get().end());
    return iterator;
}

RepositoriesIterator::RepositoriesIterator(Repositories * repositories)
    : p_impl(std::make_unique<Impl>(repositories)) {}

RepositoriesIterator::~RepositoriesIterator() = default;

RepositoriesIterator::RepositoriesIterator(const RepositoriesIterator & other) : p_impl(new Impl(*other.p_impl)) {}

RepositoriesIterator & RepositoriesIterator::operator=(const RepositoriesIterator & other) {
    if (this != &other) {
        *p_impl = *other.p_impl;
    }
    return *this;
}

RepositoriesIterator::RepositoriesIterator(RepositoriesIterator && other) noexcept = default;
RepositoriesIterator & RepositoriesIterator::operator=(RepositoriesIterator && other) noexcept = default;

Repository RepositoriesIterator::operator*() {
    Repository repository;
    repository.p_impl->init(p_impl->get_object());
    return repository;
}

RepositoriesIterator & RepositoriesIterator::operator++() {
    p_impl->inc();
    return *this;
}

bool RepositoriesIterator::operator!=(const RepositoriesIterator & other) const {
    return p_impl->get() != other.p_impl->get();
}

}