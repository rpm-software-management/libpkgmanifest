#pragma once

#include "libpkgmanifest/objects/nevra.hpp"

#include "impl/libpkgmanifest/objects/nevra/nevrafactory.hpp"

namespace libpkgmanifest {

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

    internal::INevra * get() {
        ensure_object_exists();
        return nevra;
    }

    std::unique_ptr<internal::INevra> get_factory_object() {
        ensure_object_exists();
        return std::move(factory_nevra);
    }

    void init(internal::INevra * nevra) {
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
            factory_nevra = internal::NevraFactory().create();
            init(factory_nevra.get());
        }
    }

    internal::INevra * nevra;
    std::unique_ptr<internal::INevra> factory_nevra;
};

}