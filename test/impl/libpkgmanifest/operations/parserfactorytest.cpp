#include "impl/libpkgmanifest/operations/parserfactory.hpp"
#include "impl/libpkgmanifest/operations/prototypeinfileconverter.hpp"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace {

using namespace libpkgmanifest::internal;

using ::testing::ElementsAre;

TEST(ParserFactoryTest, ParseSimpleManifest) {
    auto file_path = std::string(getenv("PROJECT_SOURCE_DIR")) + "/test/data/manifest/simple.yaml";

    ParserFactory parser_factory;
    auto parser = parser_factory.create();
    auto manifest = parser->parse_manifest(file_path);

    EXPECT_EQ("rpm-package-manifest", manifest->get_document());
    EXPECT_EQ(1, manifest->get_version().get_major());
    EXPECT_EQ(2, manifest->get_version().get_minor());
    EXPECT_EQ(3, manifest->get_version().get_patch());

    auto & repositories = manifest->get_repositories().get();
    EXPECT_EQ(3, repositories.size());

    auto & repository1 = repositories.at("repo1");
    EXPECT_EQ("repo1", repository1->get_id());
    EXPECT_EQ("http://some.server.gov/folder/metalink", repository1->get_metalink());

    auto & repository2 = repositories.at("repo2");
    EXPECT_EQ("repo2", repository2->get_id());
    EXPECT_EQ("http://other.computer.lol/dir/for/pkgs/$arch/", repository2->get_baseurl());

    auto & repository3 = repositories.at("repo3");
    EXPECT_EQ("repo3", repository3->get_id());
    EXPECT_EQ("file:///home/user/my/repository", repository3->get_baseurl());
    EXPECT_EQ("https://my.user.repository.org/metalink", repository3->get_metalink());
    EXPECT_EQ("http://mirrors.user.repository.org/mirrors.txt", repository3->get_mirrorlist());

    EXPECT_EQ(2, manifest->get_packages().get().size());
    EXPECT_EQ(2, manifest->get_packages().get()["i686"].size());
    EXPECT_EQ(1, manifest->get_packages().get()["src"].size());

    auto & package1 = manifest->get_packages().get().at("i686")[0];
    EXPECT_EQ("repo1", package1->get_repo_id());
    EXPECT_EQ(152384, package1->get_size());
    EXPECT_EQ(libpkgmanifest::ChecksumMethod::SHA512, package1->get_checksum().get_method());
    EXPECT_EQ("abcdef", package1->get_checksum().get_digest());
    EXPECT_EQ("", package1->get_module().get_name());
    EXPECT_EQ("", package1->get_module().get_stream());

    auto & package2 = manifest->get_packages().get().at("i686")[1];
    EXPECT_EQ("repo2", package2->get_repo_id());
    EXPECT_EQ("p/package2-3:4.5.6-2.r2.rpm", package2->get_location());
    EXPECT_EQ(378124894, package2->get_size());
    EXPECT_EQ(libpkgmanifest::ChecksumMethod::MD5, package2->get_checksum().get_method());
    EXPECT_EQ("fedcba", package2->get_checksum().get_digest());
    EXPECT_EQ("name2", package2->get_module().get_name());
    EXPECT_EQ("stream2", package2->get_module().get_stream());

    auto & package3 = manifest->get_packages().get().at("src")[0];
    EXPECT_EQ("repo3", package3->get_repo_id());
    EXPECT_EQ("another/dir/file.here", package3->get_location());
    EXPECT_EQ(97643154, package3->get_size());
    EXPECT_EQ(libpkgmanifest::ChecksumMethod::SHA256, package3->get_checksum().get_method());
    EXPECT_EQ("qpwoeiru", package3->get_checksum().get_digest());
    EXPECT_EQ("", package3->get_module().get_name());
    EXPECT_EQ("", package3->get_module().get_stream());
}

TEST(ParserFactoryTest, ParseSimpleInput) {
    auto file_path = std::string(getenv("PROJECT_SOURCE_DIR")) + "/test/data/input/simple.yaml";

    ParserFactory parser_factory;
    auto parser = parser_factory.create();
    auto input = parser->parse_input(file_path);

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

    EXPECT_THAT(input->get_packages()["install"], ElementsAre("bootc", "dnf", "podman"));

    EXPECT_EQ(3, input->get_archs().size());
    EXPECT_THAT(input->get_archs(), ElementsAre("i686", "x86_64", "aarch64"));
}

TEST(ParserFactoryTest, ParseSimplePrototypeInput) {
    auto file_path = std::string(getenv("PROJECT_SOURCE_DIR")) + "/test/data/input/prototype.yaml";

    ParserFactory parser_factory;
    auto parser = parser_factory.create();
    auto input = parser->parse_input_from_prototype(file_path);

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

    EXPECT_THAT(input->get_packages()["install"], ElementsAre("gettext", "hostname", "nss_wrapper", "bind-utils", "varnish", "gcc"));

    EXPECT_EQ(4, input->get_archs().size());
    EXPECT_THAT(input->get_archs(), ElementsAre("x86_64", "aarch64", "ppc64le", "s390x"));
}

}