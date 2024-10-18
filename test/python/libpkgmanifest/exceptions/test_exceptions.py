import libpkgmanifest

import base_test_case


class TestExceptions(base_test_case.BaseTestCase):
    def test_parse_nonexisting_file(self):
        parser = libpkgmanifest.Parser()
        self.assertRaises(RuntimeError, parser.parse_manifest, "non-existing-file")

    def test_parse_invalid_file(self):
        parser = libpkgmanifest.Parser()
        self.assertRaises(RuntimeError, parser.parse_manifest, self.test_invalid_manifest_file)

    def test_serialize_invalid_location(self):
        manifest = libpkgmanifest.Manifest()
        serializer = libpkgmanifest.Serializer()
        self.assertRaises(RuntimeError, serializer.serialize_manifest, manifest, "/invalid-path/file")
