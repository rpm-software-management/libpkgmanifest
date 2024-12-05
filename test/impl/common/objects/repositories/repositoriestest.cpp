#include "impl/common/mocks/objects/repository/repositorymock.hpp"

#include "impl/common/objects/repositories/repositories.hpp"

#include <gtest/gtest.h>

namespace {

using namespace libpkgmanifest::internal::common;

using ::testing::NiceMock;
using ::testing::Return;

TEST(RepositoriesTest, DefaultRepositoriesAreEmpty) {
    EXPECT_EQ(0, Repositories().get().size());
}

TEST(RepositoriesTest, AddedRepositoryIsReturned) {
    auto repository = std::make_unique<NiceMock<RepositoryMock>>();
    auto repository_ptr = repository.get();
    EXPECT_CALL(*repository, get_id()).WillOnce(Return("id"));

    Repositories repositories;
    repositories.add(std::move(repository));

    auto & repositories_map = repositories.get();
    EXPECT_EQ(1, repositories_map.size());
    EXPECT_EQ(repository_ptr, repositories_map.begin()->second.get());

    const auto & const_repositories_map = repositories_map;
    EXPECT_EQ(1, const_repositories_map.size());
    EXPECT_EQ(repository_ptr, const_repositories_map.begin()->second.get());
}

TEST(RepositoriesTest, AddedRepositoryIsReturnedByItsId) {
    auto repository = std::make_unique<NiceMock<RepositoryMock>>();
    auto repository_ptr = repository.get();
    EXPECT_CALL(*repository, get_id()).WillOnce(Return("id"));

    Repositories repositories;
    repositories.add(std::move(repository));

    auto & repositories_map = repositories.get();
    auto & id_repository = repositories_map.at("id");
    EXPECT_EQ(repository_ptr, id_repository.get());
}

TEST(RepositoriesTest, ClonedObjectHasSameValuesAsOriginal) {
    auto repository1 = std::make_unique<NiceMock<RepositoryMock>>();
    EXPECT_CALL(*repository1, get_id()).WillRepeatedly(Return("repo_id_1"));

    auto repository2 = std::make_unique<NiceMock<RepositoryMock>>();
    EXPECT_CALL(*repository2, get_id()).WillRepeatedly(Return("repo_id_2"));

    auto cloned_repository1 = std::make_unique<NiceMock<RepositoryMock>>();
    auto cloned_repository2 = std::make_unique<NiceMock<RepositoryMock>>();
    EXPECT_CALL(*cloned_repository1, get_id()).WillOnce(Return(repository1->get_id()));
    EXPECT_CALL(*cloned_repository2, get_id()).WillOnce(Return(repository2->get_id()));
    EXPECT_CALL(*repository1, clone()).WillOnce(Return(std::move(cloned_repository1)));
    EXPECT_CALL(*repository2, clone()).WillOnce(Return(std::move(cloned_repository2)));

    Repositories repositories;
    repositories.add(std::move(repository1));
    repositories.add(std::move(repository2));

    auto clone(repositories.clone());
    EXPECT_EQ(repositories.get().size(), clone->get().size());
    EXPECT_EQ(repositories.get()["repo_id_1"]->get_id(), clone->get()["repo_id_1"]->get_id());
    EXPECT_EQ(repositories.get()["repo_id_2"]->get_id(), clone->get()["repo_id_2"]->get_id());
}

}