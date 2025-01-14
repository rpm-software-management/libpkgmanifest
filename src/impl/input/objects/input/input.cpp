#include "input.hpp"

namespace libpkgmanifest::internal::input {

using namespace libpkgmanifest::internal::common;

Input::Input()
    : document()
    , version(nullptr)
    , repositories(nullptr)
    , packages(nullptr)
    , modules(nullptr)
    , options(nullptr)
    , archs() {}

Input::Input(const Input & other) 
    : document(other.document)
    , version(other.version->clone())
    , repositories(other.repositories->clone())
    , packages(other.packages->clone())
    , modules(other.modules->clone())
    , options(other.options->clone())
    , archs(other.archs) {}

std::unique_ptr<IInput> Input::clone() const {
    return std::make_unique<Input>(*this);
}

std::string Input::get_document() const {
    return document;
}

const IVersion & Input::get_version() const {
    return *version;
}

IVersion & Input::get_version() {
    return *version;
}

const IRepositories & Input::get_repositories() const {
    return *repositories;
}

IRepositories & Input::get_repositories() {
    return *repositories;
}

const IPackages & Input::get_packages() const {
    return *packages;
}

IPackages & Input::get_packages() {
    return *packages;
}

const IModules & Input::get_modules() const {
    return *modules;
}

IModules & Input::get_modules() {
    return *modules;
}

const std::vector<std::string> & Input::get_archs() const {
    return archs;
}

std::vector<std::string> & Input::get_archs() {
    return archs;
}

const IOptions & Input::get_options() const {
    return *options;
}

IOptions & Input::get_options() {
    return *options;
}

void Input::set_document(const std::string & document) {
    this->document = document;
}

void Input::set_version(std::unique_ptr<IVersion> version) {
    this->version = std::move(version);
}

void Input::set_repositories(std::unique_ptr<IRepositories> repositories) {
    this->repositories = std::move(repositories);
}

void Input::set_packages(std::unique_ptr<IPackages> packages) {
    this->packages = std::move(packages);
}

void Input::set_modules(std::unique_ptr<IModules> modules) {
    this->modules = std::move(modules);
}

void Input::set_options(std::unique_ptr<IOptions> options) {
    this->options = std::move(options);
}

}
