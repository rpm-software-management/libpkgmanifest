%global version_major 0
%global version_minor 5
%global version_patch 6

Name:       libpkgmanifest
Version:    %{version_major}.%{version_minor}.%{version_patch}
Release:    1%{?dist}
Summary:    Library for working with RPM manifests
License:    LGPL-2.1-or-later
URL:        https://github.com/rpm-software-management/libpkgmanifest
Source0:    %{url}/archive/%{version}/libpkgmanifest-%{version}.tar.gz

%bcond_with    clang
%bcond_with    docs
%bcond_without python
%bcond_without tests

%if %{with clang}
%global toolchain clang
BuildRequires:  clang
%else
BuildRequires:  gcc-c++ >= 10.1
%endif

BuildRequires:  cmake >= 3.13
BuildRequires:  pkgconfig(yaml-cpp) >= 0.7.0

%if %{with tests}
BuildRequires:  pkgconfig(gmock)
BuildRequires:  pkgconfig(gtest)
%endif

%if %{with python}
BuildRequires:  python3-devel
BuildRequires:  swig >= 4.2.0
%endif

%if %{with docs}
BuildRequires:  python3dist(breathe)
BuildRequires:  python3dist(sphinx)
BuildRequires:  python3dist(sphinx-rtd-theme)
%endif

%description
libpkgmanifest is a library for parsing and creating RPM manifests.
It provides a native C++ API and Python bindings.

%files -n libpkgmanifest
%{_libdir}/libpkgmanifest.so.0
%license LICENSE

%package -n libpkgmanifest-devel
Summary:        Development files for libpkgmanifest
License:        LGPL-2.1-or-later
Requires:       libpkgmanifest%{?_isa} = %{version}-%{release}

%description -n libpkgmanifest-devel
Development files for libpkgmanifest.

%files -n libpkgmanifest-devel
%{_includedir}/libpkgmanifest/
%{_libdir}/libpkgmanifest.so
%{_libdir}/pkgconfig/libpkgmanifest.pc
%license LICENSE

%if %{with python}
%package -n python3-libpkgmanifest
%{?python_provide:%python_provide python3-libpkgmanifest}
Summary:        Python 3 bindings for the libpkgmanifest library
License:        LGPL-2.1-or-later
Requires:       libpkgmanifest%{?_isa} = %{version}-%{release}

%description -n python3-libpkgmanifest
Python 3 bindings for the libpkgmanifest library.

%files -n python3-libpkgmanifest
%{python3_sitearch}/libpkgmanifest
%{python3_sitearch}/libpkgmanifest-*.dist-info
%license LICENSE
%endif

%prep
%autosetup -p1 -n libpkgmanifest-%{version}

%build
%cmake \
    -DWITH_DOCS=%{?with_docs:ON}%{!?with_docs:OFF} \
    -DWITH_PYTHON=%{?with_python:ON}%{!?with_python:OFF} \
    -DWITH_TESTS=%{?with_tests:ON}%{!?with_tests:OFF} \
    \
    -DVERSION_MAJOR=%{version_major} \
    -DVERSION_MINOR=%{version_minor} \
    -DVERSION_PATCH=%{version_patch}
%cmake_build

%check
%if %{with tests}
    %ctest
%endif

%install
%cmake_install

%changelog
%autochangelog