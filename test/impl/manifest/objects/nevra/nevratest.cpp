// Copyright The libpkgmanifest Authors
// SPDX-License-Identifier: LGPL-2.1-or-later

#include "impl/manifest/objects/nevra/nevra.hpp"

#include <gtest/gtest.h>

namespace {

using namespace libpkgmanifest::internal::manifest;

TEST(NevraTest, DefaultNameIsEmpty) {
    EXPECT_EQ(std::string(), Nevra().get_name());
}

TEST(NevraTest, DefaultEpochIsEmpty) {
    EXPECT_EQ(std::string(), Nevra().get_epoch());
}

TEST(NevraTest, DefaultVersionIsEmpty) {
    EXPECT_EQ(std::string(), Nevra().get_version());
}

TEST(NevraTest, DefaultReleaseIsEmpty) {
    EXPECT_EQ(std::string(), Nevra().get_release());
}

TEST(NevraTest, DefaultArchIsEmpty) {
    EXPECT_EQ(std::string(), Nevra().get_arch());
}

TEST(NevraTest, DefaultNevraStringIsEmpty) {
    EXPECT_TRUE(Nevra().to_string().empty());
}

TEST(NevraTest, DefaultEvrStringIsEmpty) {
    EXPECT_TRUE(Nevra().to_evr_string().empty());
}

TEST(NevraTest, SetNameIsReturned) {
    Nevra nevra;
    nevra.set_name("name");
    EXPECT_EQ("name", nevra.get_name());
}

TEST(NevraTest, SetEpochIsReturned) {
    Nevra nevra;
    nevra.set_epoch("epoch");
    EXPECT_EQ("epoch", nevra.get_epoch());
}

TEST(NevraTest, SetVersionIsReturned) {
    Nevra nevra;
    nevra.set_version("version");
    EXPECT_EQ("version", nevra.get_version());
}

TEST(NevraTest, SetReleaseIsReturned) {
    Nevra nevra;
    nevra.set_release("release");
    EXPECT_EQ("release", nevra.get_release());
}

TEST(NevraTest, SetArchIsReturned) {
    Nevra nevra;
    nevra.set_arch("arch");
    EXPECT_EQ("arch", nevra.get_arch());
}

TEST(NevraTest, ToStringContainsAllElements) {
    Nevra nevra;
    nevra.set_name("pkg");
    nevra.set_epoch("1");
    nevra.set_version("1.4");
    nevra.set_release("3.rel");
    nevra.set_arch("arch");
    EXPECT_EQ("pkg-1:1.4-3.rel.arch", nevra.to_string());
}

TEST(NevraTest, ToStringDoesNotContainEpochIfZero) {
    Nevra nevra;
    nevra.set_name("pkg");
    nevra.set_epoch("0");
    nevra.set_version("1.4");
    nevra.set_release("3.rel");
    nevra.set_arch("arch");
    EXPECT_EQ("pkg-1.4-3.rel.arch", nevra.to_string());
}

TEST(NevraTest, ToStringDoesNotContainEpochIfEmpty) {
    Nevra nevra;
    nevra.set_name("pkg");
    nevra.set_version("1.4");
    nevra.set_release("3.rel");
    nevra.set_arch("arch");
    EXPECT_EQ("pkg-1.4-3.rel.arch", nevra.to_string());
}

TEST(NevraTest, ToEvrStringContainsJustEpochVersionRelease) {
    Nevra nevra;
    nevra.set_epoch("1");
    nevra.set_version("1.4");
    nevra.set_release("3.rel");
    EXPECT_EQ("1:1.4-3.rel", nevra.to_evr_string());
}

TEST(NevraTest, ToEvrStringDoesNotContainEpochIfZero) {
    Nevra nevra;
    nevra.set_epoch("0");
    nevra.set_version("1.4");
    nevra.set_release("3.rel");
    EXPECT_EQ("1.4-3.rel", nevra.to_evr_string());
}

TEST(NevraTest, ToEvrStringDoesNotContainEpochIfEmpty) {
    Nevra nevra;
    nevra.set_version("1.4");
    nevra.set_release("3.rel");
    EXPECT_EQ("1.4-3.rel", nevra.to_evr_string());
}

TEST(NevraTest, ClonedObjectHasSameValuesAsOriginal) {
    Nevra nevra;
    nevra.set_name("name");
    nevra.set_epoch("epoch");
    nevra.set_version("version");
    nevra.set_release("release");
    nevra.set_arch("arch");

    auto clone(nevra.clone());
    EXPECT_EQ(nevra.get_name(), clone->get_name());
    EXPECT_EQ(nevra.get_epoch(), clone->get_epoch());
    EXPECT_EQ(nevra.get_version(), clone->get_version());
    EXPECT_EQ(nevra.get_release(), clone->get_release());
    EXPECT_EQ(nevra.get_arch(), clone->get_arch());
}

}