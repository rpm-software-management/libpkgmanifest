#include "repositories_impl.hpp"

#include "libpkgmanifest/objects/repositories.hpp"

#include <vector>

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

bool Repositories::contains(const std::string & id) const {
    return p_impl->get()->get().contains(id);
}

std::size_t Repositories::size() const {
    return p_impl->get()->get().size();
}

Repository Repositories::get(const std::string & id) const {
    // TODO: Exception when no such repo
    return p_impl->wrap_internal_item(p_impl->get()->get()[id].get());
}

void Repositories::add(Repository & repository) {
    p_impl->get()->add(repository.p_impl->get_factory_object());
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
        if (p_impl) {
            *p_impl = *other.p_impl;
        } else {
            p_impl = std::make_unique<Impl>(*other.p_impl);
        }
    }

    return *this;
}

RepositoriesIterator::RepositoriesIterator(RepositoriesIterator && other) noexcept = default;
RepositoriesIterator & RepositoriesIterator::operator=(RepositoriesIterator && other) noexcept = default;

Repository RepositoriesIterator::operator*() {
    return p_impl->get_object();
}

RepositoriesIterator & RepositoriesIterator::operator++() {
    p_impl->inc();
    return *this;
}

bool RepositoriesIterator::operator!=(const RepositoriesIterator & other) const {
    return p_impl->get() != other.p_impl->get();
}

}