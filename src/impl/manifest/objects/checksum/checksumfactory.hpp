// Copyright The libpkgmanifest Authors
// SPDX-License-Identifier: LGPL-2.1-or-later

#pragma once

#include "ichecksumfactory.hpp"

namespace libpkgmanifest::internal::manifest {

class ChecksumFactory : public IChecksumFactory {
public:
    virtual std::unique_ptr<IChecksum> create() const override;
};

}