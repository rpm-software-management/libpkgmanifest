// Copyright The libpkgmanifest Authors
// SPDX-License-Identifier: LGPL-2.1-or-later

#include "impl/input/operations/parser/parserfactory.hpp"
#include "impl/input/operations/prototypefileconverter/prototypefileconverter.hpp"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace {

using namespace libpkgmanifest::internal::input;

using ::testing::ElementsAre;

TEST(ParserFactoryTest, ParseSimpleInput) {
    auto file_path = std::string(getenv("PROJECT_SOURCE_DIR")) + "/test/data/input/simple.yaml";

    ParserFactory parser_factory;
    auto parser = parser_factory.create();
    auto input = parser->parse(file_path);

    EXPECT_EQ("rpm-package-input", input->get_document());
    EXPECT_EQ(6, input->get_version().get_major());
    EXPECT_EQ(6, input->get_version().get_minor());
    EXPECT_EQ(5, input->get_version().get_patch());

    auto & repositories = input->get_repositories().get();
    EXPECT_EQ(2, repositories.size());

    auto & repository1 = repositories.at("main");
    EXPECT_EQ("main", repository1->get_id());
    EXPECT_EQ("https://community.server.org/metalink", repository1->get_metalink());

    auto & repository2 = repositories.at("sources");
    EXPECT_EQ("sources", repository2->get_id());
    EXPECT_EQ("https://src.location.lol/content/public/dist/lol2/source/SRPMS", repository2->get_baseurl());

    EXPECT_THAT(input->get_packages().get_installs(), ElementsAre("bootc", "dnf", "podman"));

    EXPECT_EQ(3, input->get_archs().size());
    EXPECT_THAT(input->get_archs(), ElementsAre("i686", "x86_64", "aarch64"));
}

TEST(ParserFactoryTest, ParseSimplePrototypeInput) {
    auto file_path = std::string(getenv("PROJECT_SOURCE_DIR")) + "/test/data/input/prototype.yaml";

    ParserFactory parser_factory;
    auto parser = parser_factory.create();
    auto input = parser->parse_from_prototype(file_path);

    EXPECT_EQ(INPUT_PROTOTYPE_DOCUMENT_ID, input->get_document());
    EXPECT_EQ(INPUT_PROTOTYPE_DOCUMENT_VERSION_MAJOR, input->get_version().get_major());
    EXPECT_EQ(INPUT_PROTOTYPE_DOCUMENT_VERSION_MINOR, input->get_version().get_minor());
    EXPECT_EQ(INPUT_PROTOTYPE_DOCUMENT_VERSION_PATCH, input->get_version().get_patch());

    auto & repositories = input->get_repositories().get();
    EXPECT_EQ(6, repositories.size());

    auto & repository1 = repositories.at("ubi-9-baseos-rpms");
    EXPECT_EQ("ubi-9-baseos-rpms", repository1->get_id());
    EXPECT_EQ("https://cdn-ubi.redhat.com/content/public/ubi/dist/ubi9/9/$basearch/baseos/os", repository1->get_baseurl());

    auto & repository2 = repositories.at("ubi-9-baseos-source");
    EXPECT_EQ("ubi-9-baseos-source", repository2->get_id());
    EXPECT_EQ("https://cdn-ubi.redhat.com/content/public/ubi/dist/ubi9/9/$basearch/baseos/source/SRPMS", repository2->get_baseurl());

    auto & repository3 = repositories.at("ubi-9-appstream-rpms");
    EXPECT_EQ("ubi-9-appstream-rpms", repository3->get_id());
    EXPECT_EQ("https://cdn-ubi.redhat.com/content/public/ubi/dist/ubi9/9/$basearch/appstream/os", repository3->get_baseurl());

    auto & repository4 = repositories.at("ubi-9-appstream-source");
    EXPECT_EQ("ubi-9-appstream-source", repository4->get_id());
    EXPECT_EQ("https://cdn-ubi.redhat.com/content/public/ubi/dist/ubi9/9/$basearch/appstream/source/SRPMS", repository4->get_baseurl());

    auto & repository5 = repositories.at("ubi-9-codeready-builder-rpms");
    EXPECT_EQ("ubi-9-codeready-builder-rpms", repository5->get_id());
    EXPECT_EQ("https://cdn-ubi.redhat.com/content/public/ubi/dist/ubi9/9/$basearch/codeready-builder/os", repository5->get_baseurl());

    auto & repository6 = repositories.at("ubi-9-codeready-builder-source");
    EXPECT_EQ("ubi-9-codeready-builder-source", repository6->get_id());
    EXPECT_EQ("https://cdn-ubi.redhat.com/content/public/ubi/dist/ubi9/9/$basearch/codeready-builder/source/SRPMS", repository6->get_baseurl());

    EXPECT_THAT(input->get_packages().get_installs(), ElementsAre("gettext", "hostname", "nss_wrapper", "bind-utils", "varnish", "gcc"));

    EXPECT_EQ(4, input->get_archs().size());
    EXPECT_THAT(input->get_archs(), ElementsAre("x86_64", "aarch64", "ppc64le", "s390x"));
}

}