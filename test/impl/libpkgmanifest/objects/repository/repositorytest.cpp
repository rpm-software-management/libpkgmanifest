#include "impl/libpkgmanifest/objects/repository/repository.hpp"

#include <gtest/gtest.h>

namespace {

using namespace libpkgmanifest::internal;

TEST(RepositoryTest, DefaultIdIsEmpty) {
    EXPECT_EQ(std::string(), Repository().get_id());
}

TEST(RepositoryTest, DefaultUrlIsEmpty) {
    EXPECT_EQ(std::string(), Repository().get_baseurl());
}

TEST(RepositoryTest, SetIdIsReturned) {
    Repository repository;
    repository.set_id("repo_id");
    EXPECT_EQ("repo_id", repository.get_id());
}

TEST(RepositoryTest, SetBaseurlIsReturned) {
    Repository repository;
    repository.set_baseurl("url url url");
    EXPECT_EQ("url url url", repository.get_baseurl());
}

TEST(RepositoryTest, SetMirrorlistIsReturned) {
    Repository repository;
    repository.set_mirrorlist("mirrors mirrors on the mirrorish wall");
    EXPECT_EQ("mirrors mirrors on the mirrorish wall", repository.get_mirrorlist());
}

TEST(RepositoryTest, SetMetalinkIsReturned) {
    Repository repository;
    repository.set_metalink("META");
    EXPECT_EQ("META", repository.get_metalink());
}

TEST(RepositoryTest, ClonedObjectHasSameValuesAsOriginal) {
    Repository repository;
    repository.set_id("idy");
    repository.set_baseurl("http://repo.lol");
    repository.set_metalink("https://metalink.org/metalink?repo=ugh-$val1&var2=$val2");
    repository.set_mirrorlist("http://mirrors.example.com/mirrorlist.txt");

    auto clone(repository.clone());
    EXPECT_EQ(repository.get_id(), clone->get_id());
    EXPECT_EQ(repository.get_baseurl(), clone->get_baseurl());
    EXPECT_EQ(repository.get_metalink(), clone->get_metalink());
    EXPECT_EQ(repository.get_mirrorlist(), clone->get_mirrorlist());
}

}