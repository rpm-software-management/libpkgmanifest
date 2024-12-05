import libpkgmanifest.manifest

import base_test_case


# Not run by default
# Just rename the test to be run to start with "test_"
class TestPerformance(base_test_case.BaseTestCase):
    def parse_big_yaml(self):
        manifest = libpkgmanifest.manifest.Parser().parse(self.test_big_manifest_file)
