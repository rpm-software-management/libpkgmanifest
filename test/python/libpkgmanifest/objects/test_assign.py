import libpkgmanifest

import base_test_case


class TestAssign(base_test_case.BaseTestCase):
    def test_replace_subobject(self):
        package = libpkgmanifest.Package()

        checksum = libpkgmanifest.Checksum()
        checksum.digest = "a1b2c3d4"

        package.checksum = checksum

        self.assertEqual("a1b2c3d4", package.checksum.digest)