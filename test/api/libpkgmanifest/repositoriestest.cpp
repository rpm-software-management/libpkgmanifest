#include "libpkgmanifest/objects/repositories.hpp"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace {

using namespace libpkgmanifest;

using ::testing::ElementsAre;

TEST(ApiRepositoriesTest, IteratorTest) {
    Repositories repositories;

    Repository repository1;
    repository1.set_id("repo1");
    Repository repository2;
    repository2.set_id("repo2");

    repositories.add(repository1);
    repositories.add(repository2);

    std::vector<std::string> ids;
    for (auto repository : repositories) {
        ids.push_back(repository.get_id());
    }

    EXPECT_THAT(ids, ElementsAre("repo1", "repo2"));
}

}