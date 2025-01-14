#pragma once

#include "libpkgmanifest/input/modules.hpp"

#include "impl/input/objects/modules/modulesfactory.hpp"

namespace libpkgmanifest::input {

using namespace libpkgmanifest::internal::input;

class Modules::Impl {
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

    IModules * get() {
        ensure_object_exists();
        return modules;
    }

    std::unique_ptr<IModules> get_factory_object() {
        ensure_object_exists();
        return std::move(factory_modules);
    }

    void init(IModules * modules) {
        this->modules = modules;
    }

private:
    void copy_object(const Impl & other) {
        if (other.modules) {
            init(other.modules);
        } else if (other.factory_modules) {
            factory_modules = other.factory_modules->clone();
            init(factory_modules.get());
        }
    }

    void ensure_object_exists() {
        if (!modules) {
            factory_modules = ModulesFactory().create();
            init(factory_modules.get());
        }
    }

    IModules * modules = nullptr;
    std::unique_ptr<IModules> factory_modules;
};

}