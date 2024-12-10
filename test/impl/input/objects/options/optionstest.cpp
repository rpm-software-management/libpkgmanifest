#include "impl/input/objects/options/options.hpp"

#include <gtest/gtest.h>

namespace {

using namespace libpkgmanifest::internal::input;

TEST(InputOptionsTest, DefaultAllowErasingIsFalse) {
    EXPECT_FALSE(Options().get_allow_erasing());
}

TEST(InputOptionsTest, SetAllowErasingIsReturned) {
    Options options;
    options.set_allow_erasing(true);
    EXPECT_TRUE(options.get_allow_erasing());
}

TEST(InputOptionsTest, ClonedObjectHasSameValuesAsOriginal) {
    Options options;
    options.set_allow_erasing(true);

    auto clone(options.clone());
    EXPECT_EQ(options.get_allow_erasing(), clone->get_allow_erasing());
}

}