#include "impl/common/mocks/objects/repositories/repositoriesmock.hpp"
#include "impl/common/mocks/objects/repositories/repositoriesfactorymock.hpp"
#include "impl/common/mocks/objects/version/versionmock.hpp"
#include "impl/common/mocks/objects/version/versionfactorymock.hpp"
#include "impl/input/mocks/objects/packages/packagesmock.hpp"
#include "impl/input/mocks/objects/packages/packagesfactorymock.hpp"
#include "impl/input/mocks/objects/modules/modulesmock.hpp"
#include "impl/input/mocks/objects/modules/modulesfactorymock.hpp"
#include "impl/input/mocks/objects/options/optionsmock.hpp"
#include "impl/input/mocks/objects/options/optionsfactorymock.hpp"

#include "impl/input/objects/input/inputfactory.hpp"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace {

using namespace libpkgmanifest::internal::input;

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

        auto packages_wrapper = std::make_unique<NiceMock<PackagesMock>>();
        packages = packages_wrapper.get();

        auto modules_wrapper = std::make_unique<NiceMock<ModulesMock>>();
        modules = modules_wrapper.get();

        auto options_wrapper = std::make_unique<NiceMock<OptionsMock>>();
        options = options_wrapper.get();

        auto repositories_factory = std::make_shared<NiceMock<RepositoriesFactoryMock>>();
        EXPECT_CALL(*repositories_factory, create()).WillOnce(Return(std::move(repositories_wrapper)));

        auto version_factory = std::make_shared<NiceMock<VersionFactoryMock>>();
        EXPECT_CALL(*version_factory, create()).WillOnce(Return(std::move(version_wrapper)));

        auto packages_factory = std::make_shared<NiceMock<PackagesFactoryMock>>();
        EXPECT_CALL(*packages_factory, create()).WillOnce(Return(std::move(packages_wrapper)));

        auto modules_factory = std::make_shared<NiceMock<ModulesFactoryMock>>();
        EXPECT_CALL(*modules_factory, create()).WillOnce(Return(std::move(modules_wrapper)));

        auto options_factory = std::make_shared<NiceMock<OptionsFactoryMock>>();
        EXPECT_CALL(*options_factory, create()).WillOnce(Return(std::move(options_wrapper)));

        factory = std::make_unique<InputFactory>(
            repositories_factory, 
            version_factory,
            packages_factory,
            modules_factory,
            options_factory);
    }

    NiceMock<RepositoriesMock> * repositories;
    NiceMock<VersionMock> * version;
    NiceMock<PackagesMock> * packages;
    NiceMock<ModulesMock> * modules;
    NiceMock<OptionsMock> * options;

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

TEST_F(InputFactoryTest, CreateReturnsAnObjectWithAnInstanceOfPackages) {
    auto input = factory->create();
    EXPECT_EQ(&input->get_packages(), packages);
}

TEST_F(InputFactoryTest, CreateReturnsAnObjectWithAnInstanceOfModules) {
    auto input = factory->create();
    EXPECT_EQ(&input->get_modules(), modules);
}

TEST_F(InputFactoryTest, CreateReturnsAnObjectWithAnInstanceOfOptions) {
    auto input = factory->create();
    EXPECT_EQ(&input->get_options(), options);
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

TEST_F(InputFactoryTest, CreatedObjectReturnsAnEmptyArchsList) {
    EXPECT_EQ(0, factory->create()->get_archs().size());
}

}