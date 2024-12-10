#pragma once

#include "libpkgmanifest/input/options.hpp"

#include "impl/input/objects/options/optionsfactory.hpp"

namespace libpkgmanifest::input {

using namespace libpkgmanifest::internal::input;

class Options::Impl {
public:
    Impl() 
        : options(nullptr)
        , factory_options(nullptr) {}
    
    Impl(const Impl & other) {
        copy_object(other);
    }

    Impl & operator=(const Impl & other) {
        if (this != &other) {
            copy_object(other);
        }

        return *this;
    }

    IOptions * get() {
        ensure_object_exists();
        return options;
    }

    std::unique_ptr<IOptions> get_factory_object() {
        ensure_object_exists();
        return std::move(factory_options);
    }

    void init(IOptions * options) {
        this->options = options;
    }

private:
    void copy_object(const Impl & other) {
        if (other.options) {
            init(other.options);
        } else if (other.factory_options) {
            factory_options = other.factory_options->clone();
            init(factory_options.get());
        }
    }

    void ensure_object_exists() {
        if (!options) {
            factory_options = OptionsFactory().create();
            init(factory_options.get());
        }
    }

    IOptions * options;
    std::unique_ptr<IOptions> factory_options;
};

}