// Copyright The libpkgmanifest Authors
// SPDX-License-Identifier: LGPL-2.1-or-later

#pragma once

#include <memory>
#include <string>

namespace libpkgmanifest::internal::manifest {

class IModule {
public:
    virtual ~IModule() = default;

    virtual std::unique_ptr<IModule> clone() const = 0;

    virtual std::string get_name() const = 0;
    virtual std::string get_stream() const = 0;

    virtual void set_name(const std::string & name) = 0;
    virtual void set_stream(const std::string & stream) = 0;
};

}