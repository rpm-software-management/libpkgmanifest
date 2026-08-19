// Copyright The libpkgmanifest Authors
// SPDX-License-Identifier: LGPL-2.1-or-later

#include "impl/common/mocks/objects/repositories/repositoriesmock.hpp"
#include "impl/common/mocks/objects/repository/repositorymock.hpp"
#include "impl/common/mocks/objects/version/versionmock.hpp"
#include "impl/input/mocks/objects/input/inputmock.hpp"
#include "impl/input/mocks/objects/modules/modulesmock.hpp"
#include "impl/input/mocks/objects/options/optionsmock.hpp"
#include "impl/input/mocks/objects/packages/packagesmock.hpp"
#include "impl/input/operations/serializer/serializerfactory.hpp"

#include <gtest/gtest.h>

#include <filesystem>
#include <fstream>

namespace {

using namespace libpkgmanifest::internal::input;

using ::testing::NiceMock;
using ::testing::Return;
using ::testing::ReturnPointee;
using ::testing::Test;

class InputSerializerFactoryTest : public Test {
protected:
    virtual void SetUp() { file_path = std::filesystem::temp_directory_path() / "InputSerializerFactoryTest.yaml"; }

    virtual void TearDown() {
        std::error_code ec;
        std::filesystem::remove(file_path, ec);
    }

    std::filesystem::path file_path;
};

TEST_F(InputSerializerFactoryTest, SerializeSimpleInput) {
    const std::string simple_input_yaml = R"(document: rpm-package-input
version: 6.6.5
repositories:
  - id: main
    metalink: https://community.server.org/metalink
  - id: sources
    baseurl: https://src.location.lol/content/public/dist/lol2/source/SRPMS
packages:
  install:
    - bootc
    - dnf
    - podman
archs:
  - i686
  - x86_64
  - aarch64
)";

    auto repository1 = std::make_unique<NiceMock<RepositoryMock>>();
    EXPECT_CALL(*repository1, get_id()).WillRepeatedly(Return("main"));
    EXPECT_CALL(*repository1, get_metalink()).WillOnce(Return("https://community.server.org/metalink"));

    auto repository2 = std::make_unique<NiceMock<RepositoryMock>>();
    EXPECT_CALL(*repository2, get_id()).WillRepeatedly(Return("sources"));
    EXPECT_CALL(*repository2, get_baseurl())
        .WillOnce(Return("https://src.location.lol/content/public/dist/lol2/source/SRPMS"));

    std::map<std::string, std::unique_ptr<IRepository>> repository_map;
    repository_map["main"] = std::move(repository1);
    repository_map["sources"] = std::move(repository2);

    NiceMock<RepositoriesMock> repositories;
    EXPECT_CALL(Const(repositories), get()).WillRepeatedly(ReturnPointee(&repository_map));

    NiceMock<VersionMock> version;
    EXPECT_CALL(version, get_major()).WillOnce(Return(6));
    EXPECT_CALL(version, get_minor()).WillOnce(Return(6));
    EXPECT_CALL(version, get_patch()).WillOnce(Return(5));

    std::vector<std::string> installs = {"bootc", "dnf", "podman"};
    std::vector<std::string> reinstalls;
    NiceMock<PackagesMock> packages;
    EXPECT_CALL(Const(packages), get_installs()).WillOnce(ReturnPointee(&installs));
    EXPECT_CALL(Const(packages), get_reinstalls()).WillOnce(ReturnPointee(&reinstalls));

    std::vector<std::string> enables;
    std::vector<std::string> disables;
    NiceMock<ModulesMock> modules;
    EXPECT_CALL(Const(modules), get_enables()).WillRepeatedly(ReturnPointee(&enables));
    EXPECT_CALL(Const(modules), get_disables()).WillRepeatedly(ReturnPointee(&disables));

    NiceMock<OptionsMock> options;
    EXPECT_CALL(options, get_allow_erasing()).WillRepeatedly(Return(false));

    std::vector<std::string> archs = {"i686", "x86_64", "aarch64"};

    NiceMock<InputMock> input;
    EXPECT_CALL(input, get_document()).WillOnce(Return("rpm-package-input"));
    EXPECT_CALL(Const(input), get_version()).WillOnce(ReturnPointee(&version));
    EXPECT_CALL(Const(input), get_packages()).WillOnce(ReturnPointee(&packages));
    EXPECT_CALL(Const(input), get_repositories()).WillOnce(ReturnPointee(&repositories));
    EXPECT_CALL(Const(input), get_modules()).WillRepeatedly(ReturnPointee(&modules));
    EXPECT_CALL(Const(input), get_options()).WillRepeatedly(ReturnPointee(&options));
    EXPECT_CALL(Const(input), get_archs()).WillOnce(ReturnPointee(&archs));

    SerializerFactory serializer_factory;
    auto serializer = serializer_factory.create();
    serializer->serialize_input(input, file_path);

    std::ifstream output_file(file_path);
    std::stringstream read_file_buffer;
    read_file_buffer << output_file.rdbuf();

    EXPECT_EQ(read_file_buffer.str(), simple_input_yaml);
}

TEST_F(InputSerializerFactoryTest, SerializeInputWithModulesAndOptions) {
    const std::string input_yaml = R"(document: rpm-package-input
version: 1.0.0
repositories:
  - id: repo1
    baseurl: http://example.com/repo
packages:
  install:
    - pkg1
  reinstall:
    - pkg2
modules:
  enable:
    - mod1:stream1
  disable:
    - mod2
archs:
  - x86_64
options:
  allow_erasing: true
)";

    auto repository1 = std::make_unique<NiceMock<RepositoryMock>>();
    EXPECT_CALL(*repository1, get_id()).WillRepeatedly(Return("repo1"));
    EXPECT_CALL(*repository1, get_baseurl()).WillOnce(Return("http://example.com/repo"));

    std::map<std::string, std::unique_ptr<IRepository>> repository_map;
    repository_map["repo1"] = std::move(repository1);

    NiceMock<RepositoriesMock> repositories;
    EXPECT_CALL(Const(repositories), get()).WillRepeatedly(ReturnPointee(&repository_map));

    NiceMock<VersionMock> version;
    EXPECT_CALL(version, get_major()).WillOnce(Return(1));
    EXPECT_CALL(version, get_minor()).WillOnce(Return(0));
    EXPECT_CALL(version, get_patch()).WillOnce(Return(0));

    std::vector<std::string> installs = {"pkg1"};
    std::vector<std::string> reinstalls = {"pkg2"};
    NiceMock<PackagesMock> packages;
    EXPECT_CALL(Const(packages), get_installs()).WillOnce(ReturnPointee(&installs));
    EXPECT_CALL(Const(packages), get_reinstalls()).WillRepeatedly(ReturnPointee(&reinstalls));

    std::vector<std::string> enables = {"mod1:stream1"};
    std::vector<std::string> disables = {"mod2"};
    NiceMock<ModulesMock> modules;
    EXPECT_CALL(Const(modules), get_enables()).WillRepeatedly(ReturnPointee(&enables));
    EXPECT_CALL(Const(modules), get_disables()).WillRepeatedly(ReturnPointee(&disables));

    NiceMock<OptionsMock> options;
    EXPECT_CALL(options, has_allow_erasing()).WillRepeatedly(Return(true));
    EXPECT_CALL(options, get_allow_erasing()).WillRepeatedly(Return(true));

    std::vector<std::string> archs = {"x86_64"};

    NiceMock<InputMock> input;
    EXPECT_CALL(input, get_document()).WillOnce(Return("rpm-package-input"));
    EXPECT_CALL(Const(input), get_version()).WillOnce(ReturnPointee(&version));
    EXPECT_CALL(Const(input), get_packages()).WillOnce(ReturnPointee(&packages));
    EXPECT_CALL(Const(input), get_repositories()).WillOnce(ReturnPointee(&repositories));
    EXPECT_CALL(Const(input), get_modules()).WillRepeatedly(ReturnPointee(&modules));
    EXPECT_CALL(Const(input), get_options()).WillRepeatedly(ReturnPointee(&options));
    EXPECT_CALL(Const(input), get_archs()).WillOnce(ReturnPointee(&archs));

    SerializerFactory serializer_factory;
    auto serializer = serializer_factory.create();
    serializer->serialize_input(input, file_path);

    std::ifstream output_file(file_path);
    std::stringstream read_file_buffer;
    read_file_buffer << output_file.rdbuf();

    EXPECT_EQ(read_file_buffer.str(), input_yaml);
}

}  // namespace
