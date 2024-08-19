#include "liblockfile/mocks/objects/packages/packagesmock.hpp"
#include "liblockfile/mocks/objects/version/versionmock.hpp"

#include "liblockfile/objects/lockfile/lockfile.hpp"

#include <gtest/gtest.h>

namespace {

using namespace liblockfile::internal;

using ::testing::NiceMock;
using ::testing::Return;

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

    const auto & const_file = file;
    EXPECT_EQ(version_ptr, &const_file.get_version());
}

TEST(LockFileTest, SetPackagesObjectIsReturned) {
    auto packages = std::make_unique<NiceMock<PackagesMock>>();
    auto packages_ptr = packages.get();

    LockFile file;
    file.set_packages(std::move(packages));

    EXPECT_EQ(packages_ptr, &file.get_packages());

    const auto & const_file = file;
    EXPECT_EQ(packages_ptr, &const_file.get_packages());
}

TEST(LockFileTest, ClonedObjectHasSameValuesAsOriginal) {
    // TODO: Tests cloned packages objects are the same

    auto packages = std::make_unique<NiceMock<PackagesMock>>();
    auto cloned_packages = std::make_unique<NiceMock<PackagesMock>>();
    auto version = std::make_unique<NiceMock<VersionMock>>();
    auto cloned_version = std::make_unique<NiceMock<VersionMock>>();
    EXPECT_CALL(*version, get_major()).WillOnce(Return(7));
    EXPECT_CALL(*cloned_version, get_major()).WillOnce(Return(7));
    EXPECT_CALL(*version, clone()).WillOnce(Return(std::move(cloned_version)));

    LockFile file;
    file.set_document("doc1");
    file.set_version(std::move(version));
    file.set_packages(std::move(packages));

    auto clone(file.clone());
    EXPECT_EQ(file.get_document(), clone->get_document());
    EXPECT_EQ(file.get_version().get_major(), clone->get_version().get_major());
}

}