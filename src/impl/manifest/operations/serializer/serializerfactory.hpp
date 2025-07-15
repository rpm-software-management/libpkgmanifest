// Copyright The libpkgmanifest Authors
// SPDX-License-Identifier: LGPL-2.1-or-later

#pragma once

#include "iserializerfactory.hpp"

namespace libpkgmanifest::internal::manifest {

class SerializerFactory : public ISerializerFactory {
public:
    virtual std::unique_ptr<ISerializer> create() const override;
};

}