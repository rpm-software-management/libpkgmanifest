import os
import shutil
import tempfile
import unittest


PROJECT_BINARY_DIR = os.environ["PROJECT_BINARY_DIR"]
PROJECT_SOURCE_DIR = os.environ["PROJECT_SOURCE_DIR"]


class BaseTestCase(unittest.TestCase):
    def setUp(self):
        self.test_file = os.path.join(PROJECT_SOURCE_DIR, "test/data/simple.yaml")
        self.big_test_file = os.path.join(PROJECT_SOURCE_DIR, "test/data/big.yaml")
        self.invalid_file = os.path.join(PROJECT_SOURCE_DIR, "test/data/invalid.yaml")
        self.temp_dir = tempfile.mkdtemp(prefix="libpkgmanifest_python_unittest.")
    
    def tearDown(self):
        shutil.rmtree(self.temp_dir)
