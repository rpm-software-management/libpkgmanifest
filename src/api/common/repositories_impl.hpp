// Copyright The libpkgmanifest Authors
// SPDX-License-Identifier: LGPL-2.1-or-later

#pragma once

#include "libpkgmanifest/common/repositories.hpp"

#include "api/shared/base_impl.hpp"
#include "impl/common/objects/repositories/repositoriesfactory.hpp"

#include "repository_impl.hpp"

namespace libpkgmanifest::common {

using namespace libpkgmanifest::internal::common;

class Repositories::Impl : public BaseImpl<IRepositories, RepositoriesFactory> {};

class RepositoriesIterator::Impl {
public:
    Impl(Repositories * repositories) : repositories(repositories) {}

    void set(typename std::map<std::string, std::unique_ptr<IRepository>>::iterator it) {
        this->it = it;
    }

    typename std::map<std::string, std::unique_ptr<IRepository>>::iterator get() {
        return it;
    }

    void inc() {
        ++it;
    }

    IRepository * get_object() {
        return it->second.get();
    }

private:
    Repositories * repositories;
    typename std::map<std::string, std::unique_ptr<IRepository>>::iterator it;
};

}