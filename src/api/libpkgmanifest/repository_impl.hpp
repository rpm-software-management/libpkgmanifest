#pragma once

#include "libpkgmanifest/repository.hpp"

#include "libpkgmanifest/objects/repository/repositoryfactory.hpp"

namespace libpkgmanifest {

class Repository::Impl {
public:
    Impl() 
        : repository(nullptr)
        , factory_repository(nullptr) {}
    
    Impl(const Impl & other) {
        copy_object(other);
    }

    Impl & operator=(const Impl & other) {
        if (this != &other) {
            copy_object(other);
        }

        return *this;
    }

    internal::IRepository * get() {
        ensure_object_exists();
        return repository;
    }

    std::unique_ptr<internal::IRepository> get_factory_object() {
        ensure_object_exists();
        return std::move(factory_repository);
    }

    void init(internal::IRepository * repository) {
        this->repository = repository;
    }

private:
    void copy_object(const Impl & other) {
        if (other.repository) {
            init(other.repository);
        } else if (other.factory_repository) {
            factory_repository = other.factory_repository->clone();
            init(factory_repository.get());
        }
    }

    void ensure_object_exists() {
        if (!repository) {
            factory_repository = internal::RepositoryFactory().create();
            init(factory_repository.get());
        }
    }

    internal::IRepository * repository;
    std::unique_ptr<internal::IRepository> factory_repository;
};

}