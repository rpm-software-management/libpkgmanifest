libpkgmanifest
==============

This library provides functionality for parsing and serializing RPM package manifest files.

Written in C++ with TDD, the library offers a simple, ABI-compatible API layer for users.
Python bindings are also available, automatically generated from the C++ API.

Manifest Files
--------------

Manifest files contain a list of RPM package metadata, categorized by architecture, along
with repository metadata for all listed package sources. The provided information uniquely
identifies each package and where to download its payload.

Example manifest file:

```
document: rpm-package-manifest
version: 0.1.0
data:
    repositories:
        - id: fedora
          url: https://mirror.karneval.cz/pub/linux/fedora/linux/releases/40/Everything/$arch/os/
        - id: fedora-source
          url: https://mirror.karneval.cz/pub/linux/fedora/linux/releases/40/Everything/source/tree/
    packages:
        x86_64:
            - name: bash
              repo_id: fedora
              location: Packages/b/bash-5.2.26-3.fc40.x86_64.rpm
              checksum: sha256:7a87c64087b2ad362f4ad8721f3c95ae61e86d204ee3d93917608a55cf24a2be
              size: 1893870
              evr: 5.2.26-3.fc40
              srpm: bash-5.2.26-3.fc40.src
            - name: zsh
              repo_id: fedora
              location: Packages/z/zsh-5.9-13.fc40.x86_64.rpm
              checksum: sha256:26aafbf8b0f5e3080752912179b1d3348643123918d5ee5c6074f424689b57b4
              size: 3412259
              evr: 5.9-13.fc40
              srpm: zsh-5.9-13.fc40.src
        src:
            - name: bash
              repo_id: fedora-source
              location: Packages/b/bash-5.2.26-3.fc40.src.rpm
              checksum: sha256:87fe52b454280d08f1621398175c1f778bbe998c80c8c2ba4baeeaf56d9e8c39
              size: 11213719
              evr: 5.2.26-3.fc40
            - name: zsh
              repo_id: fedora-source
              url: Packages/z/zsh-5.9-13.fc40.src.rpm
              checksum: sha256:92d9cebf37ad5c589d3e7e25429f601519d59fad0c477ba792c8e9ae75f5cd86
              size: 3396538
              evr: 5.9-13.fc40
```

These files can be used for purposes such as reproducible builds, capturing system snapshots,
or documenting packages used for an image composition.

Installation
------------

Currently, the only way to obtain an RPM package is through the COPR repository, which offers nightly builds of our packages.

You can enable the [libpkgmanifest-nightly](https://copr.fedorainfracloud.org/coprs/rpmsoftwaremanagement/libpkgmanifest-nightly)
repository with:

```
sudo dnf copr enable rpmsoftwaremanagement/libpkgmanifest-nightly
```

Then, install the packages using:
```
sudo dnf install <package>
```

The library provides several sub-packages:
- **libpkgmanifest**: The `.so` library
- **libpkgmanifest-devel**: The library with header and pkgconfig files
- **python3-libpkgmanifest**: Python bindings

Build
-----

To compile the project, follow these steps:

1. Clone the repository and navigate to the directory.
2. Install dependencies using:

```
sudo dnf builddep libpkgmanifest.spec
```

3. Build the project with the following command:

```
mkdir build && pushd build && cmake .. && make -j`nproc` && ctest -V --test-dir test && popd
```

This creates a build directory, compiles the project, and runs the unit tests.

Build RPM
---------

To produce an RPM package, use the `tito` tool:

```
tito build --test --rpm
```

API Examples
------------

To see how to use the library in C++ or Python applications, check out the unit test suite in the
`test` subdirectory.

For example, you can find how to parse a manifest file and access its items in C++ [here](https://github.com/rpm-software-management/libpkgmanifest/blob/main/test/api/libpkgmanifest/parsertest.cpp) and in Python [here](https://github.com/rpm-software-management/libpkgmanifest/blob/main/test/python/libpkgmanifest/parser/test_parser.py).

Contribution
------------

We welcome contributions from the community!

The project is still in development, so the contribution guide is yet to be defined.
However, you can already report bugs or request features on GitHub, and we will try to respond promptly.