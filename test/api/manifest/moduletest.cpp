// Copyright The libpkgmanifest Authors
// SPDX-License-Identifier: LGPL-2.1-or-later

#include "libpkgmanifest/manifest/module.hpp"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace {

using namespace libpkgmanifest::manifest;

TEST(ApiModuleTest, SetName) {
    Module module;
    module.set_name("module1");
    EXPECT_EQ(module.get_name(), "module1");
}

TEST(ApiModuleTest, SetStream) {
    Module module;
    module.set_stream("stream1");
    EXPECT_EQ(module.get_stream(), "stream1");
}

TEST(ApiModuleTest, CopyConstructorCreatesIndependentCopy) {
    Module module;
    module.set_name("module1");

    Module copied_module(module);
    EXPECT_EQ(copied_module.get_name(), "module1");
    copied_module.set_name("module2");
    EXPECT_EQ(module.get_name(), "module1");
}

TEST(ApiModuleTest, CopyAssignmentCreatesIndependentCopy) {
    Module module;
    module.set_name("module1");

    Module copied_module;
    copied_module = module;
    EXPECT_EQ(copied_module.get_name(), "module1");
    copied_module.set_name("module2");
    EXPECT_EQ(module.get_name(), "module1");
}

TEST(ApiModuleTest, MoveConstructorTransfersOwnership) {
    Module module;
    module.set_name("module1");

    Module moved_module(std::move(module));
    EXPECT_EQ(moved_module.get_name(), "module1");
}

TEST(ApiModuleTest, MoveAssignmentTransfersOwnership) {
    Module module;
    module.set_name("module1");

    Module moved_module;
    moved_module = std::move(module);
    EXPECT_EQ(moved_module.get_name(), "module1");
}

}