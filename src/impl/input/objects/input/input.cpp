#include "input.hpp"

namespace libpkgmanifest::internal::input {

using namespace libpkgmanifest::internal::common;

Input::Input()
    : document()
    , version(nullptr)
    , repositories(nullptr)
    , packages()
    , archs() {}

Input::Input(const Input & other) 
    : document(other.document)
    , version(other.version->clone())
    , repositories(other.repositories->clone())
    , packages(other.packages)
    , archs(other.archs)
    , allow_erasing(other.allow_erasing) {}

std::unique_ptr<IInput> Input::clone() const {
    return std::unique_ptr<IInput>(new Input(*this));
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

const std::map<std::string, std::vector<std::string>> & Input::get_packages() const {
    return packages;
}

std::map<std::string, std::vector<std::string>> & Input::get_packages() {
    return packages;
}

const std::map<std::string, std::vector<std::string>> & Input::get_modules() const {
    return modules;
}

std::map<std::string, std::vector<std::string>> & Input::get_modules() {
    return modules;
}

const std::vector<std::string> & Input::get_archs() const {
    return archs;
}

std::vector<std::string> & Input::get_archs() {
    return archs;
}

bool Input::get_allow_erasing() const {
    return allow_erasing;
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

void Input::set_allow_erasing(bool allow_erasing) {
    this->allow_erasing = allow_erasing;
}

}
