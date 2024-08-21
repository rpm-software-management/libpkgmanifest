import libpkgmanifest

import base_test_case


class TestParser(base_test_case.BaseTestCase):
    def test_parse_simple_file(self):
        manifest = libpkgmanifest.Parser().parse(self.test_file)

        self.assertEqual('rpm-manifest', manifest.document)
        self.assertEqual(1, manifest.version.major)
        self.assertEqual(2, manifest.version.minor)
        self.assertEqual(3, manifest.version.patch)

        packages = manifest.packages
        self.assertEqual(2, len(packages['i686']))
        self.assertEqual(1, len(packages['src']))

        package1 = packages['i686'][0]
        self.assertEqual('i686', package1.arch)
        self.assertEqual('repo1', package1.repo_id)
        self.assertEqual('url1', package1.url)
        self.assertEqual(libpkgmanifest.ChecksumMethod_SHA512, package1.checksum.method)
        self.assertEqual('abcdef', package1.checksum.digest)
        self.assertEqual(152384, package1.size)
        self.assertEqual('nevra1', package1.nevra)
        self.assertEqual('srpm1', package1.srpm)

        package2 = packages['i686'][1]
        self.assertEqual('i686', package2.arch)
        self.assertEqual('repo2', package2.repo_id)
        self.assertEqual('url2', package2.url)
        self.assertEqual(libpkgmanifest.ChecksumMethod_MD5, package2.checksum.method)
        self.assertEqual('fedcba', package2.checksum.digest)
        self.assertEqual(378124894, package2.size)
        self.assertEqual('nevra2', package2.nevra)
        self.assertEqual('srpm2', package2.srpm)

        package3 = packages['src'][0]
        self.assertEqual('src', package3.arch)
        self.assertEqual('repo3', package3.repo_id)
        self.assertEqual('http://some.server.org/folder/nevra3.rpm', package3.url)
        self.assertEqual(libpkgmanifest.ChecksumMethod_SHA256, package3.checksum.method)
        self.assertEqual('qpwoeiru', package3.checksum.digest)
        self.assertEqual(97643154, package3.size)
        self.assertEqual('nevra3', package3.nevra)
        self.assertEqual('srpm3', package3.srpm)

    def test_modify_parsed_object(self):
        manifest = libpkgmanifest.Parser().parse(self.test_file)
        manifest.version.major = 6
        self.assertEqual(6, manifest.version.major)

    def test_replace_parsed_object(self):
        manifest = libpkgmanifest.Parser().parse(self.test_file)

        version = libpkgmanifest.Version()
        version.major = 6

        manifest.version = version

        self.assertEqual(6, manifest.version.major)
