// Copyright The libpkgmanifest Authors
// SPDX-License-Identifier: LGPL-2.1-or-later

#include "impl/common/tools/stringsplitter/istringsplitter.hpp"

#include <gmock/gmock.h>

using namespace libpkgmanifest::internal::common;

namespace {

class StringSplitterMock : public IStringSplitter {
public:
    MOCK_METHOD(std::vector<std::string>, split, (const std::string &, char), (const, override));
};

}
