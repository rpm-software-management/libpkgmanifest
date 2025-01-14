#pragma once

#include "modules_impl.hpp"
#include "options_impl.hpp"
#include "packages_impl.hpp"

#include "libpkgmanifest/input/input.hpp"

#include "api/common/repositories_impl.hpp"
#include "api/common/version_impl.hpp"
#include "impl/common/objects/repositories/repositoriesfactory.hpp"
#include "impl/common/objects/version/versionfactory.hpp"
#include "impl/input/objects/input/inputfactory.hpp"
#include "impl/input/objects/modules/modulesfactory.hpp"
#include "impl/input/objects/options/optionsfactory.hpp"
#include "impl/input/objects/packages/packagesfactory.hpp"

namespace libpkgmanifest::input {

using namespace libpkgmanifest::common;
using namespace libpkgmanifest::internal::common;
using namespace libpkgmanifest::internal::input;

class Input::Impl {
public:
    Impl() 
        : input(nullptr)
        , factory_input(nullptr)
        , parsed_input(nullptr)
        , repositories()
        , version()
        , packages()
        , modules()
        , options() {}

    Impl(const Impl & other) {
        copy_object(other);
    }

    Impl & operator=(const Impl & other) {
        if (this != &other) {
            copy_object(other);
        }

        return *this;
    }

    IInput * get() {
        ensure_object_exists();
        return input;
    }

    std::unique_ptr<IInput> get_factory_object() {
        ensure_object_exists();
        return std::move(factory_input);
    }

    libpkgmanifest::common::Repositories & get_repositories() {
        ensure_object_exists();
        return repositories;
    }

    libpkgmanifest::common::Version & get_version() {
        ensure_object_exists();
        return version;
    }

    Packages & get_packages() {
        ensure_object_exists();
        return packages;
    }

    Modules & get_modules() {
        ensure_object_exists();
        return modules;
    }

    Options & get_options() {
        ensure_object_exists();
        return options;
    }

    void init(IInput * input) {
        this->input = input;
        repositories.p_impl->init(&input->get_repositories());
        version.p_impl->init(&input->get_version());
        packages.p_impl->init(&input->get_packages());
        modules.p_impl->init(&input->get_modules());
        options.p_impl->init(&input->get_options());
    }
    
    void set(std::unique_ptr<IInput> parsed_input) {
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
            auto input_factory = InputFactory(
                std::make_shared<RepositoriesFactory>(),
                std::make_shared<VersionFactory>(),
                std::make_shared<PackagesFactory>(),
                std::make_shared<ModulesFactory>(),
                std::make_shared<OptionsFactory>());
            factory_input = input_factory.create();
            init(factory_input.get());
        }
    }

    IInput * input;
    std::unique_ptr<IInput> factory_input;
    std::unique_ptr<IInput> parsed_input;
    Repositories repositories;
    Version version;
    Packages packages;
    Modules modules;
    Options options;
};

}