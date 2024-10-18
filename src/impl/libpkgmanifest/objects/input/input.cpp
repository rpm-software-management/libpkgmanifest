#include "input.hpp"

namespace libpkgmanifest::internal {

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
    , archs(other.archs) {}

std::unique_ptr<Input> Input::clone() const {
    throw;
}

std::string Input::get_document() const {
    throw;
}

const IVersion & Input::get_version() const {
    throw;
}

IVersion & Input::get_version() {
    throw;
}

const IRepositories & Input::get_repositories() const {
    throw;
}

IRepositories & Input::get_repositories() {
    throw;
}

const std::vector<std::string> & Input::get_packages() const {
    throw;
}

std::vector<std::string> & Input::get_packages() {
    throw;
}

const std::vector<std::string> & Input::get_archs() const {
    throw;
}

std::vector<std::string> & Input::get_archs() {
    throw;
}

void Input::set_document([[maybe_unused]] const std::string & document) {
    throw;
}

void Input::set_version([[maybe_unused]] std::unique_ptr<IVersion> version) {
    throw;
}

void Input::set_repositories([[maybe_unused]] std::unique_ptr<IRepositories> repositories) {
    throw;
}

}
