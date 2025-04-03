#pragma once

#include "modules_impl.hpp"
#include "options_impl.hpp"
#include "packages_impl.hpp"

#include "libpkgmanifest/input/input.hpp"

#include "api/common/repositories_impl.hpp"
#include "api/common/version_impl.hpp"
#include "api/shared/base_impl.hpp"
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

class Input::Impl : public BaseImpl<IInput, InputFactory> {
public:
    Impl() = default;

    Impl(const Impl & other) : BaseImpl() {
        copy_object(other);
    }

    Impl & operator=(const Impl & other) {
        if (this != &other) {
            copy_object(other);
        }
        return *this;
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

    void init(IInput * input) override {
        object = input;
        repositories.p_impl->init(&input->get_repositories());
        version.p_impl->init(&input->get_version());
        packages.p_impl->init(&input->get_packages());
        modules.p_impl->init(&input->get_modules());
        options.p_impl->init(&input->get_options());
    }
    
protected:
    void ensure_object_exists() override {
        if (!object) {
            auto input_factory = InputFactory(
                std::make_shared<RepositoriesFactory>(),
                std::make_shared<VersionFactory>(),
                std::make_shared<PackagesFactory>(),
                std::make_shared<ModulesFactory>(),
                std::make_shared<OptionsFactory>());
            owned_object = input_factory.create();
            init(owned_object.get());
        }
    }

private:
    Repositories repositories;
    Version version;
    Packages packages;
    Modules modules;
    Options options;
};

}