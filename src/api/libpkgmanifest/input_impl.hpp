#pragma once

#include "libpkgmanifest/objects/input.hpp"

#include "impl/libpkgmanifest/objects/input/inputfactory.hpp"
#include "impl/libpkgmanifest/objects/repositories/repositoriesfactory.hpp"
#include "impl/libpkgmanifest/objects/version/versionfactory.hpp"

#include "repositories_impl.hpp"
#include "version_impl.hpp"

namespace libpkgmanifest {

class Input::Impl {
public:
    Impl() 
        : input(nullptr)
        , factory_input(nullptr)
        , parsed_input(nullptr)
        , repositories()
        , version() {}

    Impl(const Impl & other) {
        copy_object(other);
    }

    Impl & operator=(const Impl & other) {
        if (this != &other) {
            copy_object(other);
        }

        return *this;
    }

    internal::IInput * get() {
        ensure_object_exists();
        return input;
    }

    std::unique_ptr<internal::IInput> get_factory_object() {
        ensure_object_exists();
        return std::move(factory_input);
    }

    Repositories & get_repositories() {
        ensure_object_exists();
        return repositories;
    }

    Version & get_version() {
        ensure_object_exists();
        return version;
    }

    void init(internal::IInput * input) {
        this->input = input;
        repositories.p_impl->init(&input->get_repositories());
        version.p_impl->init(&input->get_version());
    }
    
    void set(std::unique_ptr<internal::IInput> parsed_input) {
        init(parsed_input.get());
        this->parsed_input = std::move(parsed_input);
    }

private:
    void copy_object(const Impl & other) {
        if (other.parsed_input) {
            parsed_input = other.parsed_input->clone();
            init(parsed_input.get());
        } else if (other.factory_input) {
            factory_input = other.factory_input->clone();
            init(factory_input.get());
        }
    }

    void ensure_object_exists() {
        if (!input) {
            auto input_factory = internal::InputFactory(
                std::shared_ptr<internal::IRepositoriesFactory>(new internal::RepositoriesFactory()),
                std::shared_ptr<internal::IVersionFactory>(new internal::VersionFactory()));
            factory_input = input_factory.create();
            init(factory_input.get());
        }
    }

    internal::IInput * input;
    std::unique_ptr<internal::IInput> factory_input;
    std::unique_ptr<internal::IInput> parsed_input;
    Repositories repositories;
    Version version;
};

}