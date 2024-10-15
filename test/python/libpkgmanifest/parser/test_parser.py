import libpkgmanifest

import base_test_case


class TestParser(base_test_case.BaseTestCase):
    def test_parse_simple_file(self):
        manifest = libpkgmanifest.Parser().parse(self.test_file)

        self.assertEqual('rpm-package-manifest', manifest.document)
        self.assertEqual(1, manifest.version.major)
        self.assertEqual(2, manifest.version.minor)
        self.assertEqual(3, manifest.version.patch)

        repositories = manifest.repositories
        self.assertEqual(3, repositories.size())

        repository1 = repositories['repo1']
        self.assertEqual('repo1', repository1.id)
        self.assertEqual('http://some.server.gov/folder/metalink', repository1.metalink)

        repository2 = repositories['repo2']
        self.assertEqual('repo2', repository2.id)
        self.assertEqual('http://other.computer.lol/dir/for/pkgs/$arch/', repository2.baseurl)

        repository3 = repositories['repo3']
        self.assertEqual('repo3', repository3.id)
        self.assertEqual('file:///home/user/my/repository', repository3.baseurl)
        self.assertEqual('https://my.user.repository.org/metalink', repository3.metalink)
        self.assertEqual('http://mirrors.user.repository.org/mirrors.txt', repository3.mirrorlist)

        packages = manifest.packages
        self.assertEqual(3, len(packages.values()))
        self.assertEqual(2, len(packages['i686']))
        self.assertEqual(1, len(packages['src']))

        package1 = packages['i686'][0]
        self.assertEqual('repo1', package1.repo_id)
        self.assertEqual('', package1.url)
        self.assertEqual(152384, package1.size)
        self.assertEqual('repo1', package1.repository.id)
        self.assertEqual('http://some.server.gov/folder/metalink', package1.repository.metalink)
        self.assertEqual(libpkgmanifest.ChecksumMethod_SHA512, package1.checksum.method)
        self.assertEqual('abcdef', package1.checksum.digest)
        self.assertEqual('package1', package1.nevra.name)
        self.assertEqual('', package1.nevra.epoch)
        self.assertEqual('1.2.3', package1.nevra.version)
        self.assertEqual('1.r1', package1.nevra.release)
        self.assertEqual('i686', package1.nevra.arch)
        self.assertEqual('package1', package1.srpm.name)
        self.assertEqual('', package1.srpm.epoch)
        self.assertEqual('1.2.3', package1.srpm.version)
        self.assertEqual('1.r1', package1.srpm.release)
        self.assertEqual('src', package1.srpm.arch)
        self.assertEqual('', package1.module.name)
        self.assertEqual('', package1.module.stream)

        package2 = packages['i686'][1]
        self.assertEqual('repo2', package2.repo_id)
        self.assertEqual('p/package2-3:4.5.6-2.r2.rpm', package2.location)
        self.assertEqual('http://other.computer.lol/dir/for/pkgs/i686/p/package2-3:4.5.6-2.r2.rpm', package2.url)
        self.assertEqual(378124894, package2.size)
        self.assertEqual('repo2', package2.repository.id)
        self.assertEqual('http://other.computer.lol/dir/for/pkgs/$arch/', package2.repository.baseurl)
        self.assertEqual(libpkgmanifest.ChecksumMethod_MD5, package2.checksum.method)
        self.assertEqual('fedcba', package2.checksum.digest)
        self.assertEqual('package2', package2.nevra.name)
        self.assertEqual('3', package2.nevra.epoch)
        self.assertEqual('4.5.6', package2.nevra.version)
        self.assertEqual('2.r2', package2.nevra.release)
        self.assertEqual('i686', package2.nevra.arch)
        self.assertEqual('name2', package2.module.name)
        self.assertEqual('stream2', package2.module.stream)

        package3 = packages['src'][0]
        self.assertEqual('repo3', package3.repo_id)
        self.assertEqual('another/dir/file.here', package3.location)
        self.assertEqual('file:///home/user/my/repository/another/dir/file.here', package3.url)
        self.assertEqual(97643154, package3.size)
        self.assertEqual('repo3', package3.repository.id)
        self.assertEqual('file:///home/user/my/repository', package3.repository.baseurl)
        self.assertEqual('https://my.user.repository.org/metalink', package3.repository.metalink)
        self.assertEqual('http://mirrors.user.repository.org/mirrors.txt', package3.repository.mirrorlist)
        self.assertEqual(libpkgmanifest.ChecksumMethod_SHA256, package3.checksum.method)
        self.assertEqual('qpwoeiru', package3.checksum.digest)
        self.assertEqual('package3', package3.nevra.name)
        self.assertEqual('', package3.nevra.epoch)
        self.assertEqual('9.9', package3.nevra.version)
        self.assertEqual('1.r3', package3.nevra.release)
        self.assertEqual('src', package3.nevra.arch)
        self.assertEqual('', package3.module.name)
        self.assertEqual('', package3.module.stream)

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
