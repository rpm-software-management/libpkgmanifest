#include "impl/libpkgmanifest/mocks/objects/repositories/repositoriesmock.hpp"
#include "impl/libpkgmanifest/mocks/objects/repositories/repositoriesfactorymock.hpp"
#include "impl/libpkgmanifest/mocks/objects/version/versionmock.hpp"
#include "impl/libpkgmanifest/mocks/objects/version/versionfactorymock.hpp"

#include "impl/libpkgmanifest/objects/input/inputfactory.hpp"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace {

using namespace libpkgmanifest::internal;

using ::testing::NiceMock;
using ::testing::Return;
using ::testing::Test;

class InputFactoryTest : public Test {
protected:
    virtual void SetUp() {
        auto repositories_wrapper = std::make_unique<NiceMock<RepositoriesMock>>();
        repositories = repositories_wrapper.get();

        auto version_wrapper = std::make_unique<NiceMock<VersionMock>>();
        version = version_wrapper.get();

        auto repositories_factory = std::make_shared<NiceMock<RepositoriesFactoryMock>>();
        EXPECT_CALL(*repositories_factory, create()).WillOnce(Return(std::move(repositories_wrapper)));

        auto version_factory = std::make_shared<NiceMock<VersionFactoryMock>>();
        EXPECT_CALL(*version_factory, create()).WillOnce(Return(std::move(version_wrapper)));

        factory = std::make_unique<InputFactory>(repositories_factory, version_factory);
    }

    NiceMock<RepositoriesMock> * repositories;
    NiceMock<VersionMock> * version;

    std::unique_ptr<InputFactory> factory;
};

TEST_F(InputFactoryTest, CreateReturnsAnObjectWithAnInstanceOfRepositories) {
    auto input = factory->create();
    EXPECT_EQ(&input->get_repositories(), repositories);
}

TEST_F(InputFactoryTest, CreateReturnsAnObjectWithAnInstanceOfVersion) {
    auto input = factory->create();
    EXPECT_EQ(&input->get_version(), version);
}

TEST_F(InputFactoryTest, CreatedObjectReturnsDocumentIdConstant) {
    auto input = factory->create();
    EXPECT_EQ(INPUT_DOCUMENT_ID, input->get_document());
}

TEST_F(InputFactoryTest, CreatedObjectReturnsDocumentVersionConstant) {
    EXPECT_CALL(*version, set_major(INPUT_DOCUMENT_VERSION_MAJOR));
    EXPECT_CALL(*version, set_minor(INPUT_DOCUMENT_VERSION_MINOR));
    EXPECT_CALL(*version, set_patch(INPUT_DOCUMENT_VERSION_PATCH));

    auto input = factory->create();
}

TEST_F(InputFactoryTest, CreatedObjectReturnsAnEmptyPackagesList) {
    EXPECT_EQ(0, factory->create()->get_packages().size());
}

TEST_F(InputFactoryTest, CreatedObjectReturnsAnEmptyArchsList) {
    EXPECT_EQ(0, factory->create()->get_archs().size());
}

}