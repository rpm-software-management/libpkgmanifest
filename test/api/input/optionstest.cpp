#include "libpkgmanifest/input/options.hpp"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace {

using namespace libpkgmanifest::input;

TEST(ApiOptionsTest, SetAllowErasing) {
    Options options;
    options.set_allow_erasing(true);
    EXPECT_EQ(options.get_allow_erasing(), true);
}

TEST(ApiOptionsTest, CopyConstructorCreatesIndependentCopy) {
    Options options;
    options.set_allow_erasing(true);

    Options copied_options(options);
    EXPECT_EQ(copied_options.get_allow_erasing(), true);
    copied_options.set_allow_erasing(false);
    EXPECT_EQ(options.get_allow_erasing(), true);
}

TEST(ApiOptionsTest, CopyAssignmentCreatesIndependentCopy) {
    Options options;
    options.set_allow_erasing(true);

    Options copied_options;
    copied_options = options;
    EXPECT_EQ(copied_options.get_allow_erasing(), true);
    copied_options.set_allow_erasing(false);
    EXPECT_EQ(options.get_allow_erasing(), true);
}

TEST(ApiOptionsTest, MoveConstructorTransfersOwnership) {
    Options options;
    options.set_allow_erasing(true);

    Options moved_options(std::move(options));
    EXPECT_EQ(moved_options.get_allow_erasing(), true);
}

TEST(ApiOptionsTest, MoveAssignmentTransfersOwnership) {
    Options options;
    options.set_allow_erasing(true);

    Options moved_options;
    moved_options = std::move(options);
    EXPECT_EQ(moved_options.get_allow_erasing(), true);
}

}