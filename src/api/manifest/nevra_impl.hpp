#pragma once

#include "libpkgmanifest/manifest/nevra.hpp"

#include "impl/manifest/objects/nevra/nevrafactory.hpp"

namespace libpkgmanifest::manifest {

using namespace libpkgmanifest::internal::manifest;

class Nevra::Impl {
public:
    Impl() 
        : nevra(nullptr)
        , factory_nevra(nullptr) {}
    
    Impl(const Impl & other) {
        copy_object(other);
    }

    Impl & operator=(const Impl & other) {
        if (this != &other) {
            copy_object(other);
        }

        return *this;
    }

    INevra * get() {
        ensure_object_exists();
        return nevra;
    }

    std::unique_ptr<INevra> get_factory_object() {
        ensure_object_exists();
        return std::move(factory_nevra);
    }

    void init(INevra * nevra) {
        this->nevra = nevra;
    }

private:
    void copy_object(const Impl & other) {
        if (other.nevra) {
            init(other.nevra);
        } else if (other.factory_nevra) {
            factory_nevra = other.factory_nevra->clone();
            init(factory_nevra.get());
        }
    }

    void ensure_object_exists() {
        if (!nevra) {
            factory_nevra = NevraFactory().create();
            init(factory_nevra.get());
        }
    }

    INevra * nevra;
    std::unique_ptr<INevra> factory_nevra;
};

}