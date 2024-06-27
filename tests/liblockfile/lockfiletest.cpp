#include "objects/lockfile/lockfile.hpp"

#include "ipackagesmock.hpp"
#include "iversionmock.hpp"

#include <gtest/gtest.h>

namespace {

using namespace liblockfile;

using ::testing::NiceMock;

TEST(LockFileTest, DefaultDocumentIsEmpty) {
    EXPECT_EQ(std::string(), LockFile().get_document());
}

TEST(LockFileTest, DefaultVersionIsNull) {
    EXPECT_EQ(nullptr, &LockFile().get_version());
}

TEST(LockFileTest, DefaultPackagesIsNull) {
    EXPECT_EQ(nullptr, &LockFile().get_packages());
}

TEST(LockFileTest, SetDocumentIsReturned) {
    LockFile file;
    file.set_document("document");
    EXPECT_EQ("document", file.get_document());
}

TEST(LockFileTest, SetVersionObjectIsReturned) {
    auto version = std::make_unique<NiceMock<VersionMock>>();
    auto version_ptr = version.get();

    LockFile file;
    file.set_version(std::move(version));

    EXPECT_EQ(version_ptr, &file.get_version());
}

TEST(LockFileTest, SetPackagesObjectIsReturned) {
    auto packages = std::make_unique<NiceMock<PackagesMock>>();
    auto packages_ptr = packages.get();

    LockFile file;
    file.set_packages(std::move(packages));

    EXPECT_EQ(packages_ptr, &file.get_packages());
}

}