#include "libpkgmanifest/mocks/objects/checksum/checksummock.hpp"
#include "libpkgmanifest/mocks/objects/module/modulemock.hpp"
#include "libpkgmanifest/mocks/objects/nevra/nevramock.hpp"

#include "libpkgmanifest/objects/package/package.hpp"

#include <gtest/gtest.h>

namespace {

using namespace libpkgmanifest::internal;

using ::testing::NiceMock;
using ::testing::Return;

TEST(PackageTest, DefaultRepoIdIsEmpty) {
    EXPECT_EQ(std::string(), Package().get_repo_id());
}

TEST(PackageTest, DefaultUrlIsEmpty) {
    EXPECT_EQ(std::string(), Package().get_url());
}

TEST(PackageTest, DefaultSizeIsZero) {
    EXPECT_EQ(0, Package().get_size());
}

TEST(PackageTest, DefaultChecksumIsNull) {
    EXPECT_EQ(nullptr, &Package().get_checksum());
}

TEST(PackageTest, DefaultNevraIsNull) {
    EXPECT_EQ(nullptr, &Package().get_nevra());
}

TEST(PackageTest, DefaultSrpmIsNull) {
    EXPECT_EQ(nullptr, &Package().get_srpm());
}

TEST(PackageTest, DefaultModuleIsNull) {
    EXPECT_EQ(nullptr, &Package().get_module());
}

TEST(PackageTest, SetRepoIdIsReturned) {
    Package package;
    package.set_repo_id("repo1");
    EXPECT_EQ("repo1", package.get_repo_id());
}

TEST(PackageTest, SetUrlIsReturned) {
    Package package;
    package.set_url("url");
    EXPECT_EQ("url", package.get_url());
}

TEST(PackageTest, SetSizeIsReturned) {
    Package package;
    package.set_size(5678U);
    EXPECT_EQ(5678U, package.get_size());
}

TEST(PackageTest, SetChecksumObjectIsReturned) {
    auto checksum = std::make_unique<NiceMock<ChecksumMock>>();
    auto checksum_ptr = checksum.get();

    Package package;
    package.set_checksum(std::move(checksum));

    EXPECT_EQ(checksum_ptr, &package.get_checksum());

    const auto & const_package = package;
    EXPECT_EQ(checksum_ptr, &const_package.get_checksum());
}

TEST(PackageTest, SetNevraObjectIsReturned) {
    auto nevra = std::make_unique<NiceMock<NevraMock>>();
    auto nevra_ptr = nevra.get();

    Package package;
    package.set_nevra(std::move(nevra));

    EXPECT_EQ(nevra_ptr, &package.get_nevra());

    const auto & const_package = package;
    EXPECT_EQ(nevra_ptr, &const_package.get_nevra());
}

TEST(PackageTest, SetSrpmObjectIsReturned) {
    auto nevra = std::make_unique<NiceMock<NevraMock>>();
    auto nevra_ptr = nevra.get();

    Package package;
    package.set_srpm(std::move(nevra));

    EXPECT_EQ(nevra_ptr, &package.get_srpm());

    const auto & const_package = package;
    EXPECT_EQ(nevra_ptr, &const_package.get_srpm());
}

TEST(PackageTest, SetModuleObjectIsReturned) {
    auto module = std::make_unique<NiceMock<ModuleMock>>();
    auto module_ptr = module.get();

    Package package;
    package.set_module(std::move(module));

    EXPECT_EQ(module_ptr, &package.get_module());

    const auto & const_package = package;
    EXPECT_EQ(module_ptr, &const_package.get_module());
}

TEST(PackageTest, ClonedObjectHasSameValuesAsOriginal) {
    auto checksum = std::make_unique<NiceMock<ChecksumMock>>();
    auto cloned_checksum = std::make_unique<NiceMock<ChecksumMock>>();
    EXPECT_CALL(*checksum, get_digest()).WillOnce(Return("same_digest"));
    EXPECT_CALL(*cloned_checksum, get_digest()).WillOnce(Return("same_digest"));
    EXPECT_CALL(*checksum, clone()).WillOnce(Return(std::move(cloned_checksum)));

    auto nevra = std::make_unique<NiceMock<NevraMock>>();
    auto cloned_nevra = std::make_unique<NiceMock<NevraMock>>();
    EXPECT_CALL(*nevra, get_name()).WillOnce(Return("same_package"));
    EXPECT_CALL(*cloned_nevra, get_name()).WillOnce(Return("same_package"));
    EXPECT_CALL(*nevra, clone()).WillOnce(Return(std::move(cloned_nevra)));

    auto srpm = std::make_unique<NiceMock<NevraMock>>();
    auto cloned_srpm = std::make_unique<NiceMock<NevraMock>>();
    EXPECT_CALL(*srpm, get_name()).WillOnce(Return("same_source"));
    EXPECT_CALL(*cloned_srpm, get_name()).WillOnce(Return("same_source"));
    EXPECT_CALL(*srpm, clone()).WillOnce(Return(std::move(cloned_srpm)));

    auto module = std::make_unique<NiceMock<ModuleMock>>();
    auto cloned_module = std::make_unique<NiceMock<ModuleMock>>();
    EXPECT_CALL(*module, get_name()).WillOnce(Return("same_name"));
    EXPECT_CALL(*cloned_module, get_name()).WillOnce(Return("same_name"));
    EXPECT_CALL(*module, clone()).WillOnce(Return(std::move(cloned_module)));

    Package package;
    package.set_repo_id("id1234");
    package.set_url("no-url");
    package.set_size(1979843615U);
    package.set_checksum(std::move(checksum));
    package.set_nevra(std::move(nevra));
    package.set_srpm(std::move(srpm));
    package.set_module(std::move(module));

    auto clone(package.clone());
    EXPECT_EQ(package.get_repo_id(), clone->get_repo_id());
    EXPECT_EQ(package.get_url(), clone->get_url());
    EXPECT_EQ(package.get_size(), clone->get_size());
    EXPECT_EQ(package.get_checksum().get_digest(), clone->get_checksum().get_digest());
    EXPECT_EQ(package.get_nevra().get_name(), clone->get_nevra().get_name());
    EXPECT_EQ(package.get_srpm().get_name(), clone->get_srpm().get_name());
    EXPECT_EQ(package.get_module().get_name(), clone->get_module().get_name());
}

}