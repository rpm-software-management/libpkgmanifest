#pragma once

#include "libpkgmanifest/common/repositories.hpp"

#include "impl/common/objects/repositories/repositoriesfactory.hpp"

#include "repository_impl.hpp"

namespace libpkgmanifest::common {

using namespace libpkgmanifest::internal::common;

class Repositories::Impl {
public:
    Impl() = default;

    Impl(const Impl & other) {
        copy_object(other);
    }

    Impl & operator=(const Impl & other) {
        if (this != &other) {
            copy_object(other);
        }

        return *this;
    }

    IRepositories * get() {
        ensure_object_exists();
        return repositories;
    }

    std::unique_ptr<IRepositories> get_factory_object() {
        ensure_object_exists();
        return std::move(factory_repositories);
    }

    void init(IRepositories * repositories) {
        this->repositories = repositories;
    }

    Repository wrap_internal_item(IRepository * repository) const {
        Repository wrapper;
        wrapper.p_impl->init(repository);
        return wrapper;
    }

private:
    void copy_object(const Impl & other) {
        if (other.repositories) {
            init(other.repositories);
        } else if (other.factory_repositories) {
            factory_repositories = other.factory_repositories->clone();
            init(factory_repositories.get());
        }
    }

    void ensure_object_exists() {
        if (!repositories) {
            factory_repositories = RepositoriesFactory().create();
            init(factory_repositories.get());
        }
    }

    IRepositories * repositories = nullptr;
    std::unique_ptr<IRepositories> factory_repositories;
};

class RepositoriesIterator::Impl {
public:
    Impl(Repositories * repositories) : repositories(repositories) {}

    void set(typename std::map<std::string, std::unique_ptr<IRepository>>::iterator it) {
        this->it = it;
    }

    typename std::map<std::string, std::unique_ptr<IRepository>>::iterator get() {
        return it;
    }

    void inc() {
        ++it;
    }

    Repository get_object() {
        return repositories->p_impl->wrap_internal_item(it->second.get());
    }

private:
    Repositories * repositories;
    typename std::map<std::string, std::unique_ptr<IRepository>>::iterator it;
};

}