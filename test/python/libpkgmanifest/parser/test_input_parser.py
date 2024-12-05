import libpkgmanifest.input

import base_test_case


class TestInputParser(base_test_case.BaseTestCase):
    def test_parse_simple_input(self):
        input = libpkgmanifest.input.Parser().parse(self.test_input_file)

        self.assertEqual('rpm-package-input', input.document)
        self.assertEqual(6, input.version.major)
        self.assertEqual(6, input.version.minor)
        self.assertEqual(5, input.version.patch)

        repositories = input.repositories
        self.assertEqual(2, repositories.size())

        repository1 = repositories['main']
        self.assertEqual('main', repository1.id)
        self.assertEqual('https://community.server.org/metalink', repository1.metalink)

        repository2 = repositories['sources']
        self.assertEqual('sources', repository2.id)
        self.assertEqual('https://src.location.lol/content/public/dist/lol2/source/SRPMS', repository2.baseurl)

        self.assertEqual(3, len(input.packages))
        self.assertEqual('bootc', input.packages[0])
        self.assertEqual('dnf', input.packages[1])
        self.assertEqual('podman', input.packages[2])

        self.assertEqual(3, len(input.archs))
        self.assertEqual('i686', input.archs[0])
        self.assertEqual('x86_64', input.archs[1])
        self.assertEqual('aarch64', input.archs[2])

    def test_parse_simple_prototype_input(self):
        input = libpkgmanifest.input.Parser().parse_prototype(self.test_input_prototype_file)

        self.assertEqual('rpm-package-input-prototype', input.document)
        self.assertEqual(0, input.version.major)
        self.assertEqual(0, input.version.minor)
        self.assertEqual(1, input.version.patch)

        repositories = input.repositories
        self.assertEqual(6, repositories.size())

        repository1 = repositories['ubi-9-baseos-rpms']
        self.assertEqual('ubi-9-baseos-rpms', repository1.id)
        self.assertEqual('https://cdn-ubi.redhat.com/content/public/ubi/dist/ubi9/9/$basearch/baseos/os', repository1.baseurl)

        repository2 = repositories['ubi-9-baseos-source']
        self.assertEqual('ubi-9-baseos-source', repository2.id)
        self.assertEqual('https://cdn-ubi.redhat.com/content/public/ubi/dist/ubi9/9/$basearch/baseos/source/SRPMS', repository2.baseurl)

        repository3 = repositories['ubi-9-appstream-rpms']
        self.assertEqual('ubi-9-appstream-rpms', repository3.id)
        self.assertEqual('https://cdn-ubi.redhat.com/content/public/ubi/dist/ubi9/9/$basearch/appstream/os', repository3.baseurl)

        repository4 = repositories['ubi-9-appstream-source']
        self.assertEqual('ubi-9-appstream-source', repository4.id)
        self.assertEqual('https://cdn-ubi.redhat.com/content/public/ubi/dist/ubi9/9/$basearch/appstream/source/SRPMS', repository4.baseurl)

        repository5 = repositories['ubi-9-codeready-builder-rpms']
        self.assertEqual('ubi-9-codeready-builder-rpms', repository5.id)
        self.assertEqual('https://cdn-ubi.redhat.com/content/public/ubi/dist/ubi9/9/$basearch/codeready-builder/os', repository5.baseurl)

        repository6 = repositories['ubi-9-codeready-builder-source']
        self.assertEqual('ubi-9-codeready-builder-source', repository6.id)
        self.assertEqual('https://cdn-ubi.redhat.com/content/public/ubi/dist/ubi9/9/$basearch/codeready-builder/source/SRPMS', repository6.baseurl)

        self.assertEqual(6, len(input.packages))
        self.assertEqual('gettext', input.packages[0])
        self.assertEqual('hostname', input.packages[1])
        self.assertEqual('nss_wrapper', input.packages[2])
        self.assertEqual('bind-utils', input.packages[3])
        self.assertEqual('varnish', input.packages[4])
        self.assertEqual('gcc', input.packages[5])

        self.assertEqual(4, len(input.archs))
        self.assertEqual('x86_64', input.archs[0])
        self.assertEqual('aarch64', input.archs[1])
        self.assertEqual('ppc64le', input.archs[2])
        self.assertEqual('s390x', input.archs[3])
