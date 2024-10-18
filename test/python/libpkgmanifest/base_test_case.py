import os
import shutil
import tempfile
import unittest


PROJECT_BINARY_DIR = os.environ["PROJECT_BINARY_DIR"]
PROJECT_SOURCE_DIR = os.environ["PROJECT_SOURCE_DIR"]


class BaseTestCase(unittest.TestCase):
    def setUp(self):
        self.test_manifest_file = os.path.join(PROJECT_SOURCE_DIR, "test/data/manifest/simple.yaml")
        self.test_big_manifest_file = os.path.join(PROJECT_SOURCE_DIR, "test/data/manifest/big.yaml")
        self.test_invalid_manifest_file = os.path.join(PROJECT_SOURCE_DIR, "test/data/manifest/invalid.yaml")
        self.test_input_file = os.path.join(PROJECT_SOURCE_DIR, "test/data/input/simple.yaml")
        self.test_input_prototype_file = os.path.join(PROJECT_SOURCE_DIR, "test/data/input/prototype.yaml")
        self.temp_dir = tempfile.mkdtemp(prefix="libpkgmanifest_python_unittest.")
    
    def tearDown(self):
        shutil.rmtree(self.temp_dir)
