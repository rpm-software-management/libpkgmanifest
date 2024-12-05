import libpkgmanifest.manifest

import base_test_case


class TestNevra(base_test_case.BaseTestCase):
    def test_nevra_as_string(self):
        nevra = libpkgmanifest.manifest.Nevra()
        nevra.name = 'package'
        nevra.version = '1.2.3'
        nevra.release = '1.rel5'
        nevra.arch = 'aarch64'

        self.assertEqual('package-1.2.3-1.rel5.aarch64', str(nevra))
