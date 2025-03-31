#include "libpkgmanifest/common/repository.hpp"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace {

using namespace libpkgmanifest::common;

TEST(ApiRepositoryTest, SetId) {
    Repository repository;
    repository.set_id("repo1");
    EXPECT_EQ(repository.get_id(), "repo1");
}

TEST(ApiRepositoryTest, SetBaseurl) {
    Repository repository;
    repository.set_baseurl("baseurl1");
    EXPECT_EQ(repository.get_baseurl(), "baseurl1");
}

TEST(ApiRepositoryTest, SetMetalink) {
    Repository repository;
    repository.set_metalink("metalink1");
    EXPECT_EQ(repository.get_metalink(), "metalink1");
}

TEST(ApiRepositoryTest, SetMirrorlist) {
    Repository repository;
    repository.set_mirrorlist("mirrorlist1");
    EXPECT_EQ(repository.get_mirrorlist(), "mirrorlist1");
}

TEST(ApiRepositoryTest, CopyConstructorCreatesIndependentCopy) {
    Repository repository;
    repository.set_metalink("metalink1");

    Repository copied_repository(repository);
    EXPECT_EQ(copied_repository.get_metalink(), "metalink1");
    copied_repository.set_metalink("new_metalink1");
    EXPECT_EQ(repository.get_metalink(), "metalink1");
}

TEST(ApiRepositoryTest, CopyAssignmentCreatesIndependentCopy) {
    Repository repository;
    repository.set_baseurl("baseurl1");

    Repository copied_repository;
    copied_repository = repository;
    EXPECT_EQ(copied_repository.get_baseurl(), "baseurl1");
    copied_repository.set_baseurl("new_baseurl1");
    EXPECT_EQ(repository.get_baseurl(), "baseurl1");
}

TEST(ApiRepositoryTest, MoveConstructorTransfersOwnership) {
    Repository repository;
    repository.set_mirrorlist("mirrorlist1");

    Repository moved_repository(std::move(repository));
    EXPECT_EQ(moved_repository.get_mirrorlist(), "mirrorlist1");
}

TEST(ApiRepositoryTest, MoveAssignmentTransfersOwnership) {
    Repository repository;
    repository.set_id("repo1");

    Repository moved_repository;
    moved_repository = std::move(repository);
    EXPECT_EQ(moved_repository.get_id(), "repo1");
}

}