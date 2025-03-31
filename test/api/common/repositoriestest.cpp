#include "libpkgmanifest/common/repositories.hpp"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace {

using namespace libpkgmanifest::common;

using ::testing::ElementsAre;

TEST(ApiRepositoriesTest, ExceptionIsThrownWhenTryingToGetNonExistingRepository) {
    Repositories repositories;

    Repository repository;
    repository.set_id("repo1");

    repositories.add(repository);

    EXPECT_THROW(repositories.get("repo2"), NoSuchRepositoryIdError);
}

TEST(ApiRepositoriesTest, CopyConstructorCreatesIndependentCopy) {
    Repositories repositories;

    Repository repository1;
    repository1.set_id("repo1");
    repository1.set_baseurl("url1");
    Repository repository2;
    repository2.set_id("repo2");
    repository2.set_baseurl("url2");

    repositories.add(repository1);
    repositories.add(repository2);

    Repositories copied_repositories(repositories);

    std::vector<std::string> ids;
    for (auto repository : copied_repositories) {
        ids.push_back(repository.get_id());
    }

    EXPECT_THAT(ids, ElementsAre("repo1", "repo2"));

    copied_repositories.get("repo1").set_baseurl("new_url1");
    EXPECT_EQ(repositories.get("repo1").get_baseurl(), "url1");
}

TEST(ApiRepositoriesTest, CopyAssignmentCreatesIndependentCopy) {
    Repositories repositories;

    Repository repository1;
    repository1.set_id("repo1");
    repository1.set_baseurl("url1");
    Repository repository2;
    repository2.set_id("repo2");
    repository2.set_baseurl("url2");

    repositories.add(repository1);
    repositories.add(repository2);

    Repositories copied_repositories;
    copied_repositories = repositories;

    std::vector<std::string> ids;
    for (auto repository : copied_repositories) {
        ids.push_back(repository.get_id());
    }

    EXPECT_THAT(ids, ElementsAre("repo1", "repo2"));

    copied_repositories.get("repo1").set_baseurl("new_url1");
    EXPECT_EQ(repositories.get("repo1").get_baseurl(), "url1");
}

TEST(ApiRepositoriesTest, MoveConstructorTransfersOwnership) {
    Repositories repositories;

    Repository repository1;
    repository1.set_id("repo1");
    Repository repository2;
    repository2.set_id("repo2");

    repositories.add(repository1);
    repositories.add(repository2);

    Repositories moved_repositories(std::move(repositories));

    std::vector<std::string> ids;
    for (auto repository : moved_repositories) {
        ids.push_back(repository.get_id());
    }

    EXPECT_THAT(ids, ElementsAre("repo1", "repo2"));
}

TEST(ApiRepositoriesTest, MoveAssignmentTransfersOwnership) {
    Repositories repositories;

    Repository repository1;
    repository1.set_id("repo1");
    Repository repository2;
    repository2.set_id("repo2");

    repositories.add(repository1);
    repositories.add(repository2);

    Repositories moved_repositories;
    moved_repositories = std::move(repositories);

    std::vector<std::string> ids;
    for (auto repository : moved_repositories) {
        ids.push_back(repository.get_id());
    }

    EXPECT_THAT(ids, ElementsAre("repo1", "repo2"));
}

}