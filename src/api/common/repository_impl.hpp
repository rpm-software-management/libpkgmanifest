#pragma once

#include "libpkgmanifest/common/repository.hpp"

#include "impl/common/objects/repository/repositoryfactory.hpp"

namespace libpkgmanifest::common {

using namespace libpkgmanifest::internal::common;

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

    IRepository * get() {
        ensure_object_exists();
        return repository;
    }

    std::unique_ptr<IRepository> get_factory_object() {
        ensure_object_exists();
        return std::move(factory_repository);
    }

    void init(IRepository * repository) {
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
            factory_repository = RepositoryFactory().create();
            init(factory_repository.get());
        }
    }

    IRepository * repository;
    std::unique_ptr<IRepository> factory_repository;
};

}