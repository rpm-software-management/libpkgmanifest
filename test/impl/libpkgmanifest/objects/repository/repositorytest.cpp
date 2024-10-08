#include "impl/libpkgmanifest/objects/repository/repository.hpp"

#include <gtest/gtest.h>

namespace {

using namespace libpkgmanifest::internal;

TEST(RepositoryTest, DefaultIdIsEmpty) {
    EXPECT_EQ(std::string(), Repository().get_id());
}

TEST(RepositoryTest, DefaultUrlIsEmpty) {
    EXPECT_EQ(std::string(), Repository().get_url());
}

TEST(RepositoryTest, SetIdIsReturned) {
    Repository repository;
    repository.set_id("repo_id");
    EXPECT_EQ("repo_id", repository.get_id());
}

TEST(RepositoryTest, SetUrlIsReturned) {
    Repository repository;
    repository.set_url("url url url");
    EXPECT_EQ("url url url", repository.get_url());
}

TEST(RepositoryTest, ClonedObjectHasSameValuesAsOriginal) {
    Repository repository;
    repository.set_id("idy");
    repository.set_url("http://repo.lol");

    auto clone(repository.clone());
    EXPECT_EQ(repository.get_id(), clone->get_id());
    EXPECT_EQ(repository.get_url(), clone->get_url());
}

}