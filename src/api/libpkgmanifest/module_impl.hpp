#pragma once

#include "libpkgmanifest/module.hpp"

#include "libpkgmanifest/objects/module/modulefactory.hpp"

namespace libpkgmanifest {

class Module::Impl {
public:
    Impl() 
        : module(nullptr)
        , factory_module(nullptr) {}
    
    Impl(const Impl & other) {
        copy_object(other);
    }

    Impl & operator=(const Impl & other) {
        if (this != &other) {
            copy_object(other);
        }

        return *this;
    }

    internal::IModule * get() {
        ensure_object_exists();
        return module;
    }

    std::unique_ptr<internal::IModule> get_factory_object() {
        ensure_object_exists();
        return std::move(factory_module);
    }

    void init(internal::IModule * module) {
        this->module = module;
    }

private:
    void copy_object(const Impl & other) {
        if (other.module) {
            init(other.module);
        } else if (other.factory_module) {
            factory_module = other.factory_module->clone();
            init(factory_module.get());
        }
    }

    void ensure_object_exists() {
        if (!module) {
            factory_module = internal::ModuleFactory().create();
            init(factory_module.get());
        }
    }

    internal::IModule * module;
    std::unique_ptr<internal::IModule> factory_module;
};

}