import libpkgmanifest

import base_test_case


class TestExceptions(base_test_case.BaseTestCase):
    def test_parse_nonexisting_file(self):
        parser = libpkgmanifest.Parser()
        self.assertRaises(RuntimeError, parser.parse, "non-existing-file")

    def test_parse_invalid_file(self):
        parser = libpkgmanifest.Parser()
        self.assertRaises(RuntimeError, parser.parse, self.invalid_file)

    def test_serialize_invalid_location(self):
        manifest = libpkgmanifest.Manifest()
        serializer = libpkgmanifest.Serializer()
        self.assertRaises(RuntimeError, serializer.serialize, manifest, "/invalid-path/file")
