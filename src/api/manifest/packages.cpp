#include "packages_impl.hpp"

#include "api/common/repositories_impl.hpp"

#include "libpkgmanifest/manifest/packages.hpp"

#include <algorithm>
#include <ranges>

namespace libpkgmanifest::manifest {

using namespace libpkgmanifest::common;

Packages::Packages() : p_impl(std::make_unique<Impl>()) {}

Packages::~Packages() = default;

Packages::Packages(const Packages & other) : p_impl(new Impl(*other.p_impl)) {}

Packages & Packages::operator=(const Packages & other) {
    if (this != &other) {
        *p_impl = *other.p_impl;
    }
    return *this;
}

Packages::Packages(Packages && other) noexcept = default;
Packages & Packages::operator=(Packages && other) noexcept = default;

std::vector<Package> Packages::get() const {
    std::vector<Package> all_packages;
    for (const auto & arch : p_impl->get()->get_archs()) {
        auto wrapped_arch_packages = p_impl->wrap_internal_items(p_impl->get()->get(arch));
        all_packages.insert(all_packages.end(), wrapped_arch_packages.begin(), wrapped_arch_packages.end());
    }
    return all_packages;
}

std::vector<Package> Packages::get(const std::string & basearch, bool with_source) const {
    auto impl_internal = p_impl->get();
    auto archs = impl_internal->get_archs();
    auto packages = p_impl->wrap_internal_items(impl_internal->get(basearch));
    if (std::find(archs.begin(), archs.end(), "noarch") != archs.end()) {
        auto & noarch_internal_packages = impl_internal->get("noarch");
        auto filtered_noarch = noarch_internal_packages | std::views::filter([&basearch](const auto & package) {
            auto parent_archs = package->get_parent_archs();
            return parent_archs.empty() || std::find(parent_archs.begin(), parent_archs.end(), basearch) != parent_archs.end();
        });
        auto noarch_packages = p_impl->wrap_internal_items(filtered_noarch);
        std::move(noarch_packages.begin(), noarch_packages.end(), std::back_inserter(packages));
    }
    if (with_source && std::find(archs.begin(), archs.end(), "src") != archs.end()) {
        auto & src_internal_packages = impl_internal->get("src");
        auto filtered_src = src_internal_packages | std::views::filter([&packages](const auto & source) {
            return !std::any_of(packages.begin(), packages.end(), [&source](auto & package) {
                return package.get_nevra().to_string() == source->get_nevra().to_string();
            });
        });
        auto source_packages = p_impl->wrap_internal_items(filtered_src);
        std::move(source_packages.begin(), source_packages.end(), std::back_inserter(packages));
    }
    return packages;
}

void Packages::add(Package & package) {
    p_impl->get()->add(package.p_impl->get_factory_object());
}

void Packages::add(Package & package, const std::string & basearch) {
    p_impl->get()->add(package.p_impl->get_factory_object(), basearch);
}

bool Packages::contains(const Package & package) {
    return p_impl->get()->contains(*package.p_impl->get());
}

void Packages::attach(Repositories & repositories) {
    p_impl->get_binder().bind(*repositories.p_impl->get(), *p_impl->get());
}

}