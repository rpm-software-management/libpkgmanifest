libpkgmanifest
==============

This library provides functionality for parsing and serializing RPM package manifest files.

Written in C++ with TDD, the library offers a simple, ABI-compatible API layer for users.
Python bindings are also available, automatically generated from the C++ API.

Manifest Files
--------------

Manifest files contain a list of RPM package metadata, categorized by architecture. The provided
information uniquely identifies each package and where to download its payload.

Example manifest file:

```
document: rpm-package-manifest
version: 0.0.1
data:
    packages:
        x86_64:
            - repoid: fedora
              url: https://mirror.karneval.cz/pub/linux/fedora/linux/releases/40/Everything/x86_64/os/Packages/b/bash-5.2.26-3.fc40.x86_64.rpm
              checksum: md5:1254011a2ce1245f0b528b1190fa3cb6
              size: 1893870
              nevra: bash-5.2.26-3.fc40.x86_64
              srpm: bash-5.2.26-3.fc40.src
            - repoid: fedora
              url: https://mirror.karneval.cz/pub/linux/fedora/linux/releases/40/Everything/x86_64/os/Packages/z/zsh-5.9-13.fc40.x86_64.rpm
              checksum: md5:fec50044e73fcdae342722818ff88525
              size: 3412259
              nevra: zsh-0:5.9-13.fc40.x86_64
              srpm: zsh-0:5.9-13.fc40.src
        src:
            - repoid: fedora-source
              url: https://mirror.karneval.cz/pub/linux/fedora/linux/releases/40/Everything/source/tree/Packages/b/bash-5.2.26-3.fc40.src.rpm
              checksum: md5:9cfb6d31ccd42da1cf4f3a728aec4453
              size: 11213719
              nevra: bash-5.2.26-3.fc40.src
              srpm: bash-5.2.26-3.fc40.src
            - repoid: fedora-source
              url: https://mirror.karneval.cz/pub/linux/fedora/linux/releases/40/Everything/source/tree/Packages/z/zsh-5.9-13.fc40.src.rpm
              checksum: md5:bf4915d9e17e058d01affcb4505b6f63
              size: 3396538
              nevra: zsh-5.9-13.fc40.src
              srpm: zsh-5.9-13.fc40.src
```

These files can be used for purposes such as reproducible builds, capturing system snapshots,
or documenting packages used for an image composition.

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

Contribution
------------

We welcome contributions from the community!

The project is still in development, so the contribution guide is yet to be defined.
However, you can already report bugs or request features on GitHub, and we will try to respond promptly.