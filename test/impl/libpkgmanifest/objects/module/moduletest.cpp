#include "libpkgmanifest/objects/module/module.hpp"

#include <gtest/gtest.h>

namespace {

using namespace libpkgmanifest::internal;

TEST(ModuleTest, DefaultNameIsEmpty) {
    EXPECT_EQ(std::string(), Module().get_name());
}

TEST(ModuleTest, DefaultStreamIsEmpty) {
    EXPECT_EQ(std::string(), Module().get_stream());
}

TEST(ModuleTest, SetNameIsReturned) {
    Module module;
    module.set_name("module");
    EXPECT_EQ("module", module.get_name());
}

TEST(ModuleTest, SetStreamIsReturned) {
    Module module;
    module.set_stream("stream");
    EXPECT_EQ("stream", module.get_stream());
}

TEST(ModuleTest, ClonedObjectHasSameValuesAsOriginal) {
    Module module;
    module.set_name("jack");
    module.set_stream("black");

    auto clone(module.clone());
    EXPECT_EQ(module.get_name(), clone->get_name());
    EXPECT_EQ(module.get_stream(), clone->get_stream());
}

}