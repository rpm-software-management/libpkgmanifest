#include "module_impl.hpp"

#include "libpkgmanifest/manifest/module.hpp"

namespace libpkgmanifest::manifest {

Module::Module() : p_impl(std::make_unique<Impl>()) {}

Module::~Module() = default;

Module::Module(const Module & other) : p_impl(new Impl(*other.p_impl)) {}

Module & Module::operator=(const Module & other) {
    if (this != &other) {
        *p_impl = *other.p_impl;
    }
    return *this;
}

Module::Module(Module && other) noexcept = default;
Module & Module::operator=(Module && other) noexcept = default;

std::string Module::get_name() const {
    return p_impl->get()->get_name();
}

std::string Module::get_stream() const {
    return p_impl->get()->get_stream();
}

void Module::set_name(const std::string & name) {
    p_impl->get()->set_name(name);
}

void Module::set_stream(const std::string & stream) {
    p_impl->get()->set_stream(stream);
}

}