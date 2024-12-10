#include "options_impl.hpp"

#include "libpkgmanifest/input/options.hpp"

namespace libpkgmanifest::input {

Options::Options() : p_impl(std::make_unique<Impl>()) {}

Options::~Options() = default;

Options::Options(const Options & other) : p_impl(new Impl(*other.p_impl)) {}

Options & Options::operator=(const Options & other) {
    if (this != &other) {
        if (p_impl) {
            *p_impl = *other.p_impl;
        } else {
            p_impl = std::make_unique<Impl>(*other.p_impl);
        }
    }

    return *this;
}

Options::Options(Options && other) noexcept = default;
Options & Options::operator=(Options && other) noexcept = default;

bool Options::get_allow_erasing() const {
    return p_impl->get()->get_allow_erasing();
}

void Options::set_allow_erasing(bool value) {
    return p_impl->get()->set_allow_erasing(value);
}

}