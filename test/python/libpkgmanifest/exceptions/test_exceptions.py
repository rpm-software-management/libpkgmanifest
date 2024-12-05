import libpkgmanifest.manifest

import base_test_case


class TestExceptions(base_test_case.BaseTestCase):
    def test_parse_nonexisting_file(self):
        parser = libpkgmanifest.manifest.Parser()
        self.assertRaises(RuntimeError, parser.parse, "non-existing-file")

    def test_parse_invalid_file(self):
        parser = libpkgmanifest.manifest.Parser()
        self.assertRaises(RuntimeError, parser.parse, self.test_invalid_manifest_file)

    def test_serialize_invalid_location(self):
        manifest = libpkgmanifest.manifest.Manifest()
        serializer = libpkgmanifest.manifest.Serializer()
        self.assertRaises(RuntimeError, serializer.serialize, manifest, "/invalid-path/file")
