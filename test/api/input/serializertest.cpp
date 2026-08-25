// Copyright The libpkgmanifest Authors
// SPDX-License-Identifier: LGPL-2.1-or-later

#include "libpkgmanifest/input/serializer.hpp"

#include <gtest/gtest.h>

#include <filesystem>
#include <fstream>

namespace {

using namespace libpkgmanifest::input;

using ::testing::Test;

class ApiInputSerializerTest : public Test {
protected:
    virtual void SetUp() { file_path = std::filesystem::temp_directory_path() / "ApiInputSerializerTest.yaml"; }

    virtual void TearDown() {
        std::error_code ec;
        std::filesystem::remove(file_path, ec);
    }

    std::filesystem::path file_path;
};

TEST_F(ApiInputSerializerTest, SerializeSimpleInput) {
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

    Repository repository1;
    repository1.set_id("main");
    repository1.set_metalink("https://community.server.org/metalink");

    Repository repository2;
    repository2.set_id("sources");
    repository2.set_baseurl("https://src.location.lol/content/public/dist/lol2/source/SRPMS");

    Input input;
    input.set_document("rpm-package-input");
    input.get_version().set_major(6);
    input.get_version().set_minor(6);
    input.get_version().set_patch(5);
    input.get_repositories().add(repository1);
    input.get_repositories().add(repository2);
    input.get_packages().get_installs().push_back("bootc");
    input.get_packages().get_installs().push_back("dnf");
    input.get_packages().get_installs().push_back("podman");
    input.get_archs().push_back("i686");
    input.get_archs().push_back("x86_64");
    input.get_archs().push_back("aarch64");

    Serializer serializer;
    serializer.serialize(input, file_path);

    std::ifstream output_file(file_path);
    std::stringstream read_file_buffer;
    read_file_buffer << output_file.rdbuf();

    EXPECT_EQ(read_file_buffer.str(), simple_input_yaml);
}

TEST_F(ApiInputSerializerTest, SerializeInputWithAllFields) {
    const std::string full_input_yaml = R"(document: rpm-package-input
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

    Repository repository1;
    repository1.set_id("repo1");
    repository1.set_baseurl("http://example.com/repo");

    Input input;
    input.set_document("rpm-package-input");
    input.get_version().set_major(1);
    input.get_version().set_minor(0);
    input.get_version().set_patch(0);
    input.get_repositories().add(repository1);
    input.get_packages().get_installs().push_back("pkg1");
    input.get_packages().get_reinstalls().push_back("pkg2");
    input.get_modules().get_enables().push_back("mod1:stream1");
    input.get_modules().get_disables().push_back("mod2");
    input.get_archs().push_back("x86_64");
    input.get_options().set_allow_erasing(true);

    Serializer serializer;
    serializer.serialize(input, file_path);

    std::ifstream output_file(file_path);
    std::stringstream read_file_buffer;
    read_file_buffer << output_file.rdbuf();

    EXPECT_EQ(read_file_buffer.str(), full_input_yaml);
}

TEST_F(ApiInputSerializerTest, SerializeEmptyInput) {
    const std::string empty_input_yaml = R"(document: rpm-package-input
version: 0.0.2
repositories: ~
packages:
  install: ~
archs: ~
)";

    Input input;
    Serializer serializer;
    serializer.serialize(input, file_path);

    std::ifstream output_file(file_path);
    std::stringstream read_file_buffer;
    read_file_buffer << output_file.rdbuf();

    EXPECT_EQ(read_file_buffer.str(), empty_input_yaml);
}

}  // namespace
