#include "input_impl.hpp"

#include "libpkgmanifest/input/input.hpp"

namespace libpkgmanifest::input {

using namespace libpkgmanifest::common;

Input::Input() : p_impl(std::make_unique<Impl>()) {}

Input::~Input() = default;

Input::Input(const Input & other) : p_impl(new Impl(*other.p_impl)) {}

Input & Input::operator=(const Input & other) {
    if (this != &other) {
        *p_impl = *other.p_impl;
    }
    return *this;
}

Input::Input(Input && other) noexcept = default;
Input & Input::operator=(Input && other) noexcept = default;

std::string Input::get_document() const {
    return p_impl->get()->get_document();
}

Version & Input::get_version() {
    return p_impl->get_version();
}

Repositories & Input::get_repositories() {
    return p_impl->get_repositories();
}

Packages & Input::get_packages() {
    return p_impl->get_packages();
}

Modules & Input::get_modules() {
    return p_impl->get_modules();
}

std::vector<std::string> & Input::get_archs() {
    return p_impl->get()->get_archs();
}

Options & Input::get_options() {
    return p_impl->get_options();
}

void Input::set_document(const std::string & document) {
    p_impl->get()->set_document(document);
}

void Input::set_version(Version & version) {
    p_impl->get()->set_version(version.p_impl->get_owned_object());
    p_impl->get_version().p_impl->init(&p_impl->get()->get_version());
}

void Input::set_repositories(Repositories & repositories) {
    p_impl->get()->set_repositories(repositories.p_impl->get_owned_object());
    p_impl->get_repositories().p_impl->init(&p_impl->get()->get_repositories());
}

void Input::set_packages(Packages & packages) {
    p_impl->get()->set_packages(packages.p_impl->get_owned_object());
    p_impl->get_packages().p_impl->init(&p_impl->get()->get_packages());
}

void Input::set_modules(Modules & modules) {
    p_impl->get()->set_modules(modules.p_impl->get_owned_object());
    p_impl->get_modules().p_impl->init(&p_impl->get()->get_modules());
}

void Input::set_options(Options & options) {
    p_impl->get()->set_options(options.p_impl->get_owned_object());
    p_impl->get_options().p_impl->init(&p_impl->get()->get_options());
}

}