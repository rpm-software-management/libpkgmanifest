// Copyright The libpkgmanifest Authors
// SPDX-License-Identifier: LGPL-2.1-or-later

#include "libpkgmanifest/common/repositories.hpp"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace {

using namespace libpkgmanifest::common;

using ::testing::ElementsAre;

TEST(ApiRepositoriesIteratorTest, Iterating) {
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

TEST(ApiRepositoriesIteratorTest, CopyConstructorCreatesIndependentCopy) {
    Repositories repositories;

    Repository repository1;
    repository1.set_id("repo1");
    Repository repository2;
    repository2.set_id("repo2");

    repositories.add(repository1);
    repositories.add(repository2);

    RepositoriesIterator it = repositories.begin();
    RepositoriesIterator it_copy(it);

    EXPECT_EQ((*it).get_id(), "repo1");
    EXPECT_EQ((*it_copy).get_id(), "repo1");
    ++it_copy;
    EXPECT_EQ((*it).get_id(), "repo1");
    EXPECT_EQ((*it_copy).get_id(), "repo2");
}

TEST(ApiRepositoriesIteratorTest, CopyAssignmentCreatesIndependentCopy) {
    Repositories repositories;

    Repository repository1;
    repository1.set_id("repo1");
    Repository repository2;
    repository2.set_id("repo2");

    repositories.add(repository1);
    repositories.add(repository2);

    RepositoriesIterator it = repositories.begin();
    RepositoriesIterator it_copy(nullptr);
    it_copy = it;

    EXPECT_EQ((*it).get_id(), "repo1");
    EXPECT_EQ((*it_copy).get_id(), "repo1");
    ++it_copy;
    EXPECT_EQ((*it).get_id(), "repo1");
    EXPECT_EQ((*it_copy).get_id(), "repo2");
}

TEST(ApiRepositoriesIteratorTest, MoveConstructorTransfersOwnership) {
    Repositories repositories;

    Repository repository1;
    repository1.set_id("repo1");
    Repository repository2;
    repository2.set_id("repo2");

    repositories.add(repository1);
    repositories.add(repository2);

    RepositoriesIterator it = repositories.begin();
    RepositoriesIterator it_move(std::move(it));
    EXPECT_EQ((*it_move).get_id(), "repo1");
    ++it_move;
    EXPECT_EQ((*it_move).get_id(), "repo2");
}

TEST(ApiRepositoriesIteratorTest, MoveAssignmentTransfersOwnership) {
    Repositories repositories;

    Repository repository1;
    repository1.set_id("repo1");
    Repository repository2;
    repository2.set_id("repo2");

    repositories.add(repository1);
    repositories.add(repository2);

    RepositoriesIterator it = repositories.begin();
    RepositoriesIterator it_move(nullptr);
    it_move = std::move(it);
    EXPECT_EQ((*it_move).get_id(), "repo1");
    ++it_move;
    EXPECT_EQ((*it_move).get_id(), "repo2");
}

}