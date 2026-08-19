// Copyright The libpkgmanifest Authors
// SPDX-License-Identifier: LGPL-2.1-or-later

#include "impl/input/objects/options/options.hpp"

#include <gtest/gtest.h>

namespace {

using namespace libpkgmanifest::internal::input;

TEST(InputOptionsTest, DefaultAllowErasingIsFalse) {
    EXPECT_FALSE(Options().get_allow_erasing());
}

TEST(InputOptionsTest, DefaultHasAllowErasingIsFalse) {
    EXPECT_FALSE(Options().has_allow_erasing());
}

TEST(InputOptionsTest, HasAllowErasingIsTrueAfterSet) {
    Options options;
    options.set_allow_erasing(false);
    EXPECT_TRUE(options.has_allow_erasing());
}

TEST(InputOptionsTest, SetAllowErasingIsReturned) {
    Options options;
    options.set_allow_erasing(true);
    EXPECT_TRUE(options.get_allow_erasing());
}

TEST(InputOptionsTest, SetAllowErasingFalseIsReturned) {
    Options options;
    options.set_allow_erasing(false);
    EXPECT_FALSE(options.get_allow_erasing());
}

TEST(InputOptionsTest, ClonedObjectHasSameValuesAsOriginal) {
    Options options;
    options.set_allow_erasing(true);

    auto clone(options.clone());
    EXPECT_EQ(options.get_allow_erasing(), clone->get_allow_erasing());
    EXPECT_EQ(options.has_allow_erasing(), clone->has_allow_erasing());
}

TEST(InputOptionsTest, ClonedUnsetObjectHasNoValue) {
    Options options;

    auto clone(options.clone());
    EXPECT_FALSE(clone->has_allow_erasing());
}

}  // namespace
