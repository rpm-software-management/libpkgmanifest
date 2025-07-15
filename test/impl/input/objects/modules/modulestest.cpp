// Copyright The libpkgmanifest Authors
// SPDX-License-Identifier: LGPL-2.1-or-later

#include "impl/input/objects/modules/modules.hpp"

#include <gtest/gtest.h>

namespace {

using namespace libpkgmanifest::internal::input;

TEST(InputModulesTest, DefaultEnablesIsEmpty) {
    EXPECT_TRUE(Modules().get_enables().empty());
    EXPECT_TRUE(static_cast<const Modules &>(Modules()).get_enables().empty());
}

TEST(InputModulesTest, DefaultDisablesIsEmpty) {
    EXPECT_TRUE(Modules().get_disables().empty());
    EXPECT_TRUE(static_cast<const Modules &>(Modules()).get_disables().empty());
}

TEST(InputModulesTest, ClonedObjectHasSameValuesAsOriginal) {
    Modules modules;
    modules.get_enables().push_back("module1");
    modules.get_enables().push_back("module2");
    modules.get_disables().push_back("module3");

    auto clone(modules.clone());
    EXPECT_EQ(modules.get_enables(), clone->get_enables());
    EXPECT_EQ(modules.get_disables(), clone->get_disables());
}

}