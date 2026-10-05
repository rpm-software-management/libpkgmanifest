import libpkgmanifest.input
import libpkgmanifest.manifest

import base_test_case


class TestSchemaConstants(base_test_case.BaseTestCase):
    def test_input_metadata_constants(self):
        self.assertEqual("rpm-package-input", libpkgmanifest.input.INPUT_DOCUMENT_IDENTIFIER)
        version = libpkgmanifest.input.CURRENT_INPUT_SCHEMA_VERSION
        self.assertEqual((0, 0, 2), (version.major, version.minor, version.patch))

    def test_manifest_metadata_constants(self):
        self.assertEqual("rpm-package-manifest", libpkgmanifest.manifest.MANIFEST_DOCUMENT_IDENTIFIER)
        version = libpkgmanifest.manifest.CURRENT_MANIFEST_SCHEMA_VERSION
        self.assertEqual((0, 2, 3), (version.major, version.minor, version.patch))
