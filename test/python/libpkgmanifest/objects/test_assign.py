import libpkgmanifest.manifest

import base_test_case


class TestAssign(base_test_case.BaseTestCase):
    def test_replace_subobject(self):
        package = libpkgmanifest.manifest.Package()

        checksum = libpkgmanifest.manifest.Checksum()
        checksum.digest = "a1b2c3d4"

        package.checksum = checksum

        self.assertEqual("a1b2c3d4", package.checksum.digest)

    def test_references(self):
        nevra = libpkgmanifest.manifest.Nevra()
        nevra.name = "foo"

        nevra_copy = nevra
        nevra_copy.name = "bar"

        self.assertEqual("bar", nevra.name)
