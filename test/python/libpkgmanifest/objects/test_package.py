import libpkgmanifest

import base_test_case


class TestPackage(base_test_case.BaseTestCase):
    def test_nevra_fields_delegation(self):
        package = libpkgmanifest.Package()

        package.nevra.name = 'package'
        package.nevra.epoch = '3'
        package.nevra.version = '1.0'
        package.nevra.release = 'a2'
        package.nevra.arch = 'i386'
        self.assertEqual('package', package.name)
        self.assertEqual('3', package.epoch)
        self.assertEqual('1.0', package.version)
        self.assertEqual('a2', package.release)
        self.assertEqual('i386', package.arch)

        package.name = 'pkg'
        package.nevra.epoch = '2'
        package.nevra.version = '5.6'
        package.nevra.release = 'b1'
        package.nevra.arch = 'x86_64'
        self.assertEqual('pkg', package.nevra.name)
        self.assertEqual('2', package.nevra.epoch)
        self.assertEqual('5.6', package.nevra.version)
        self.assertEqual('b1', package.nevra.release)
        self.assertEqual('x86_64', package.nevra.arch)
