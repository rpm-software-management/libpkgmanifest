#include "impl/manifest/mocks/objects/nevra/nevramock.hpp"
#include "impl/manifest/mocks/objects/package/packagemock.hpp"

#include "impl/manifest/objects/packages/packages.hpp"

#include <gtest/gtest.h>

namespace {

using namespace libpkgmanifest::internal::manifest;

using ::testing::ElementsAre;
using ::testing::NiceMock;
using ::testing::Return;
using ::testing::ReturnPointee;

TEST(PackagesTest, DefaultArchsAreEmpty) {
    EXPECT_EQ(0, Packages().get_archs().size());
}

TEST(PackagesTest, DefaultGetThrowsAnException) {
    EXPECT_THROW(Packages().get("arch"), PackagesNoSuchArchError);
}

TEST(PackagesTest, AddedPackageIsReturned) {
    auto nevra = std::make_unique<NiceMock<NevraMock>>();
    EXPECT_CALL(*nevra, get_arch()).WillRepeatedly(Return("arch"));

    auto package = std::make_unique<NiceMock<PackageMock>>();
    auto package_ptr = package.get();
    EXPECT_CALL(*package, get_nevra()).WillRepeatedly(ReturnPointee(nevra.get()));
    EXPECT_CALL(Const(*package), get_nevra()).WillRepeatedly(ReturnPointee(nevra.get()));

    Packages packages;
    packages.add(std::move(package));

    auto & arch_packages = packages.get("arch");
    EXPECT_EQ(1, arch_packages.size());
    EXPECT_EQ(package_ptr, arch_packages.front().get());
}

TEST(PackagesTest, AddedPackageWithBaseArchIsReturnedInTheSameWayAsWithTheAddMethod) {
    auto empty_archs = std::vector<std::string>();

    auto nevra = std::make_unique<NiceMock<NevraMock>>();
    EXPECT_CALL(*nevra, get_arch()).WillRepeatedly(Return("arch"));

    auto package = std::make_unique<NiceMock<PackageMock>>();
    auto package_ptr = package.get();
    EXPECT_CALL(*package, get_nevra()).WillRepeatedly(ReturnPointee(nevra.get()));
    EXPECT_CALL(Const(*package), get_nevra()).WillRepeatedly(ReturnPointee(nevra.get()));
    EXPECT_CALL(*package, get_parent_archs()).WillRepeatedly(ReturnPointee(&empty_archs));

    Packages packages;
    packages.add(std::move(package), "basearch");

    auto & arch_packages = packages.get("arch");
    EXPECT_EQ(1, arch_packages.size());
    EXPECT_EQ(package_ptr, arch_packages.front().get());
}

TEST(PackagesTest, AddedPackageWithBaseArchAddsLinkInParentArchs) {
    auto parent_archs = std::vector<std::string>();

    auto nevra = std::make_unique<NiceMock<NevraMock>>();
    EXPECT_CALL(*nevra, get_arch()).WillRepeatedly(Return("arch"));

    auto package = std::make_unique<NiceMock<PackageMock>>();
    EXPECT_CALL(*package, get_nevra()).WillRepeatedly(ReturnPointee(nevra.get()));
    EXPECT_CALL(Const(*package), get_nevra()).WillRepeatedly(ReturnPointee(nevra.get()));
    EXPECT_CALL(*package, get_parent_archs()).WillRepeatedly(ReturnPointee(&parent_archs));

    Packages packages;
    packages.add(std::move(package), "basearch");

    EXPECT_THAT(parent_archs, ElementsAre("basearch"));
}

TEST(PackagesTest, AddingPackageAddsANewArch) {
    auto nevra = std::make_unique<NiceMock<NevraMock>>();
    EXPECT_CALL(*nevra, get_arch()).WillRepeatedly(Return("arch"));

    auto package = std::make_unique<NiceMock<PackageMock>>();
    EXPECT_CALL(*package, get_nevra()).WillRepeatedly(ReturnPointee(nevra.get()));
    EXPECT_CALL(Const(*package), get_nevra()).WillRepeatedly(ReturnPointee(nevra.get()));

    Packages packages;
    packages.add(std::move(package));

    EXPECT_EQ(1, packages.get_archs().size());
    EXPECT_EQ("arch", packages.get_archs()[0]);
}

TEST(PackagesTest, AddingTheSamePackageDoesNothing) {
    auto nevra1 = std::make_unique<NiceMock<NevraMock>>();
    EXPECT_CALL(*nevra1, get_arch()).WillRepeatedly(Return("arch"));
    EXPECT_CALL(*nevra1, to_string()).WillRepeatedly(Return("12345"));

    auto nevra2 = std::make_unique<NiceMock<NevraMock>>();
    EXPECT_CALL(*nevra2, get_arch()).WillRepeatedly(Return("arch"));
    EXPECT_CALL(*nevra2, to_string()).WillRepeatedly(Return("12345"));

    auto package1 = std::make_unique<NiceMock<PackageMock>>();
    EXPECT_CALL(*package1, get_nevra()).WillRepeatedly(ReturnPointee(nevra1.get()));
    EXPECT_CALL(Const(*package1), get_nevra()).WillRepeatedly(ReturnPointee(nevra1.get()));
    EXPECT_CALL(*package1, get_repo_id()).WillRepeatedly(Return("repo1"));

    auto package2 = std::make_unique<NiceMock<PackageMock>>();
    EXPECT_CALL(*package2, get_nevra()).WillRepeatedly(ReturnPointee(nevra2.get()));
    EXPECT_CALL(Const(*package2), get_nevra()).WillRepeatedly(ReturnPointee(nevra2.get()));
    EXPECT_CALL(*package2, get_repo_id()).WillRepeatedly(Return("repo1"));

    Packages packages;
    packages.add(std::move(package1));
    packages.add(std::move(package2));

    auto & arch_packages = packages.get("arch");
    EXPECT_EQ(1, arch_packages.size());
}

TEST(PackagesTest, ContainsReturnsFalseWhenNoPackages) {
    NiceMock<NevraMock> nevra;
    EXPECT_CALL(nevra, get_arch()).WillOnce(Return("arch"));

    NiceMock<PackageMock> package;
    EXPECT_CALL(Const(package), get_nevra()).WillOnce(ReturnPointee(&nevra));

    Packages packages;
    EXPECT_FALSE(packages.contains(package));
}

TEST(PackagesTest, ContainsReturnsTrueWhenPackageWithSameNevraAndRepoIdIsPresent) {
    auto existing_nevra = std::make_unique<NiceMock<NevraMock>>();
    EXPECT_CALL(*existing_nevra, get_arch()).WillRepeatedly(Return("arch"));
    EXPECT_CALL(*existing_nevra, to_string()).WillRepeatedly(Return("12345"));

    auto existing_package = std::make_unique<NiceMock<PackageMock>>();
    EXPECT_CALL(*existing_package, get_nevra()).WillRepeatedly(ReturnPointee(existing_nevra.get()));
    EXPECT_CALL(Const(*existing_package), get_nevra()).WillRepeatedly(ReturnPointee(existing_nevra.get()));
    EXPECT_CALL(*existing_package, get_repo_id()).WillRepeatedly(Return("repo1"));

    auto checked_nevra = std::make_unique<NiceMock<NevraMock>>();
    EXPECT_CALL(*checked_nevra, get_arch()).WillRepeatedly(Return("arch"));
    EXPECT_CALL(*checked_nevra, to_string()).WillRepeatedly(Return("12345"));

    auto checked_package = std::make_unique<NiceMock<PackageMock>>();
    EXPECT_CALL(*checked_package, get_nevra()).WillRepeatedly(ReturnPointee(checked_nevra.get()));
    EXPECT_CALL(Const(*checked_package), get_nevra()).WillRepeatedly(ReturnPointee(checked_nevra.get()));
    EXPECT_CALL(*checked_package, get_repo_id()).WillRepeatedly(Return("repo1"));

    Packages packages;
    packages.add(std::move(existing_package));
    EXPECT_TRUE(packages.contains(*checked_package));
}

TEST(PackagesTest, ContainsReturnsFalseWhenPackageWithDifferentNevraIsPresent) {
    auto existing_nevra = std::make_unique<NiceMock<NevraMock>>();
    EXPECT_CALL(*existing_nevra, get_arch()).WillRepeatedly(Return("arch"));
    EXPECT_CALL(*existing_nevra, to_string()).WillRepeatedly(Return("12345"));

    auto existing_package = std::make_unique<NiceMock<PackageMock>>();
    EXPECT_CALL(*existing_package, get_nevra()).WillRepeatedly(ReturnPointee(existing_nevra.get()));
    EXPECT_CALL(Const(*existing_package), get_nevra()).WillRepeatedly(ReturnPointee(existing_nevra.get()));

    auto checked_nevra = std::make_unique<NiceMock<NevraMock>>();
    EXPECT_CALL(*checked_nevra, get_arch()).WillRepeatedly(Return("arch"));
    EXPECT_CALL(*checked_nevra, to_string()).WillRepeatedly(Return("11111"));

    auto checked_package = std::make_unique<NiceMock<PackageMock>>();
    EXPECT_CALL(*checked_package, get_nevra()).WillRepeatedly(ReturnPointee(checked_nevra.get()));
    EXPECT_CALL(Const(*checked_package), get_nevra()).WillRepeatedly(ReturnPointee(checked_nevra.get()));

    Packages packages;
    packages.add(std::move(existing_package));
    EXPECT_FALSE(packages.contains(*checked_package));
}

TEST(PackagesTest, ContainsReturnsFalseWhenPackageWithDifferentRepoIdIsPresent) {
    auto existing_nevra = std::make_unique<NiceMock<NevraMock>>();
    EXPECT_CALL(*existing_nevra, get_arch()).WillRepeatedly(Return("arch"));
    EXPECT_CALL(*existing_nevra, to_string()).WillRepeatedly(Return("12345"));

    auto existing_package = std::make_unique<NiceMock<PackageMock>>();
    EXPECT_CALL(*existing_package, get_nevra()).WillRepeatedly(ReturnPointee(existing_nevra.get()));
    EXPECT_CALL(Const(*existing_package), get_nevra()).WillRepeatedly(ReturnPointee(existing_nevra.get()));
    EXPECT_CALL(*existing_package, get_repo_id()).WillRepeatedly(Return("repo1"));

    auto checked_nevra = std::make_unique<NiceMock<NevraMock>>();
    EXPECT_CALL(*checked_nevra, get_arch()).WillRepeatedly(Return("arch"));
    EXPECT_CALL(*checked_nevra, to_string()).WillRepeatedly(Return("12345"));

    auto checked_package = std::make_unique<NiceMock<PackageMock>>();
    EXPECT_CALL(*checked_package, get_nevra()).WillRepeatedly(ReturnPointee(checked_nevra.get()));
    EXPECT_CALL(Const(*checked_package), get_nevra()).WillRepeatedly(ReturnPointee(checked_nevra.get()));
    EXPECT_CALL(*checked_package, get_repo_id()).WillRepeatedly(Return("repo2"));

    Packages packages;
    packages.add(std::move(existing_package));
    EXPECT_FALSE(packages.contains(*checked_package));
}

TEST(PackagesTest, AddingPackageWithSameBaseArchAsItsArchDoesNotUpdateItsParentArchs) {
    auto parent_archs = std::vector<std::string>();

    auto nevra = std::make_unique<NiceMock<NevraMock>>();
    EXPECT_CALL(*nevra, get_arch()).WillRepeatedly(Return("arch"));

    auto package = std::make_unique<NiceMock<PackageMock>>();
    EXPECT_CALL(*package, get_nevra()).WillRepeatedly(ReturnPointee(nevra.get()));
    EXPECT_CALL(Const(*package), get_nevra()).WillRepeatedly(ReturnPointee(nevra.get()));
    EXPECT_CALL(*package, get_parent_archs()).WillRepeatedly(ReturnPointee(&parent_archs));

    Packages packages;
    packages.add(std::move(package), "arch");

    EXPECT_TRUE(parent_archs.empty());
}

TEST(PackagesTest, AddingAlreadyExistingPackageWithDifferentBaseArchOnlyLinksToTheNewBaseArch) {
    auto parent_archs1 = std::vector<std::string>();
    auto parent_archs2 = std::vector<std::string>();

    auto nevra1 = std::make_unique<NiceMock<NevraMock>>();
    EXPECT_CALL(*nevra1, get_arch()).WillRepeatedly(Return("arch"));

    auto nevra2 = std::make_unique<NiceMock<NevraMock>>();
    EXPECT_CALL(*nevra2, get_arch()).WillRepeatedly(Return("arch"));

    auto package1 = std::make_unique<NiceMock<PackageMock>>();
    EXPECT_CALL(*package1, get_nevra()).WillRepeatedly(ReturnPointee(nevra1.get()));
    EXPECT_CALL(Const(*package1), get_nevra()).WillRepeatedly(ReturnPointee(nevra1.get()));
    EXPECT_CALL(*package1, get_parent_archs()).WillRepeatedly(ReturnPointee(&parent_archs1));

    auto package2 = std::make_unique<NiceMock<PackageMock>>();
    EXPECT_CALL(*package2, get_nevra()).WillRepeatedly(ReturnPointee(nevra2.get()));
    EXPECT_CALL(Const(*package2), get_nevra()).WillRepeatedly(ReturnPointee(nevra2.get()));
    EXPECT_CALL(*package2, get_parent_archs()).WillRepeatedly(ReturnPointee(&parent_archs2));

    // adding the same package but in the second call, link it to a different basearch
    Packages packages;
    packages.add(std::move(package1), "basearch1");
    packages.add(std::move(package2), "basearch2");

    // check that no second package was added
    EXPECT_EQ(1, packages.get("arch").size());

    // expect that all basearch are present in the first package
    EXPECT_THAT(parent_archs1, ElementsAre("basearch1", "basearch2"));
}

TEST(PackagesTest, ClonedObjectHasSameValuesAsOriginal) {
    auto nevra1 = std::make_unique<NiceMock<NevraMock>>();
    EXPECT_CALL(*nevra1, get_arch()).WillRepeatedly(Return("arch1"));
    EXPECT_CALL(*nevra1, to_string()).WillRepeatedly(Return("pkg1"));
    auto package1 = std::make_unique<NiceMock<PackageMock>>();
    EXPECT_CALL(*package1, get_nevra()).WillRepeatedly(ReturnPointee(nevra1.get()));
    EXPECT_CALL(Const(*package1), get_nevra()).WillRepeatedly(ReturnPointee(nevra1.get()));
    EXPECT_CALL(*package1, get_repo_id()).WillRepeatedly(Return("repoid1"));

    auto nevra2 = std::make_unique<NiceMock<NevraMock>>();
    EXPECT_CALL(*nevra2, get_arch()).WillRepeatedly(Return("noarch"));
    EXPECT_CALL(*nevra2, to_string()).WillRepeatedly(Return("pkg2"));
    auto package2 = std::make_unique<NiceMock<PackageMock>>();
    EXPECT_CALL(*package2, get_nevra()).WillRepeatedly(ReturnPointee(nevra2.get()));
    EXPECT_CALL(Const(*package2), get_nevra()).WillRepeatedly(ReturnPointee(nevra2.get()));
    EXPECT_CALL(*package2, get_repo_id()).WillRepeatedly(Return("repoid2"));

    auto cloned_package1 = std::make_unique<NiceMock<PackageMock>>();
    auto cloned_package2 = std::make_unique<NiceMock<PackageMock>>();
    EXPECT_CALL(*package1, get_location()).WillRepeatedly(Return("1xyz"));
    EXPECT_CALL(*package2, get_location()).WillRepeatedly(Return("2xyz"));
    EXPECT_CALL(*cloned_package1, get_location()).WillRepeatedly(Return(package1->get_location()));
    EXPECT_CALL(*cloned_package2, get_location()).WillRepeatedly(Return(package2->get_location()));
    EXPECT_CALL(*cloned_package1, get_nevra()).WillRepeatedly(ReturnPointee(&package1->get_nevra()));
    EXPECT_CALL(*cloned_package2, get_nevra()).WillRepeatedly(ReturnPointee(&package2->get_nevra()));
    EXPECT_CALL(Const(*cloned_package1), get_nevra()).WillRepeatedly(ReturnPointee(&package1->get_nevra()));
    EXPECT_CALL(Const(*cloned_package2), get_nevra()).WillRepeatedly(ReturnPointee(&package2->get_nevra()));
    EXPECT_CALL(*package1, clone()).WillOnce(Return(std::move(cloned_package1)));
    EXPECT_CALL(*package2, clone()).WillOnce(Return(std::move(cloned_package2)));

    Packages packages;
    packages.add(std::move(package1));
    packages.add(std::move(package2));

    auto clone(packages.clone());
    EXPECT_EQ(packages.get_archs(), clone->get_archs());
    EXPECT_EQ(packages.get("arch1").size(), clone->get("arch1").size());
    EXPECT_EQ(packages.get("arch1")[0]->get_location(), clone->get("arch1")[0]->get_location());
    EXPECT_EQ(packages.get("noarch").size(), clone->get("noarch").size());
    EXPECT_EQ(packages.get("noarch")[0]->get_location(), clone->get("noarch")[0]->get_location());
}

}