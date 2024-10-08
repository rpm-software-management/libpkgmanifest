#pragma once

#include "libpkgmanifest/repositories.hpp"

#include "libpkgmanifest/objects/repositories/repositoriesfactory.hpp"

#include "repository_impl.hpp"

namespace libpkgmanifest {

class Repositories::Impl {
public:
    Impl() 
        : repositories(nullptr)
        , factory_repositories(nullptr) {}

    Impl(const Impl & other) {
        copy_object(other);
    }

    Impl & operator=(const Impl & other) {
        if (this != &other) {
            copy_object(other);
        }

        return *this;
    }

    internal::IRepositories * get() {
        ensure_object_exists();
        return repositories;
    }

    std::unique_ptr<internal::IRepositories> get_factory_object() {
        ensure_object_exists();
        return std::move(factory_repositories);
    }

    void init(internal::IRepositories * repositories) {
        this->repositories = repositories;
    }

    Repository wrap_internal_item(internal::IRepository * repository) const {
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
            factory_repositories = internal::RepositoriesFactory().create();
            init(factory_repositories.get());
        }
    }

    internal::IRepositories * repositories;
    std::unique_ptr<internal::IRepositories> factory_repositories;
};

class RepositoriesIterator::Impl {
public:
    Impl(Repositories * repositories) : repositories(repositories) {}

    void set(typename std::map<std::string, std::unique_ptr<internal::IRepository>>::iterator it) {
        this->it = it;
    }

    typename std::map<std::string, std::unique_ptr<internal::IRepository>>::iterator get() {
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
    typename std::map<std::string, std::unique_ptr<internal::IRepository>>::iterator it;
};

}