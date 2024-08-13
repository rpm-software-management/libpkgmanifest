%global version_major 0
%global version_minor 0
%global version_patch 1

Name:       liblockfile
Version:    %{version_major}.%{version_minor}.%{version_patch}
Release:    1%{?dist}
Summary:    Library for working with RPM lockfiles
License:    GPL-2.0-or-later
URL:        https://github.com/rpm-software-management/liblockfile
Source0:    %{url}/archive/%{version}/liblockfile-%{version}.tar.gz

%bcond_with    clang
%bcond_without docs
%bcond_without python
%bcond_without tests

%if %{with clang}
%global toolchain clang
BuildRequires:  clang
%else
BuildRequires:  gcc-c++ >= 10.1
%endif

BuildRequires:  cmake
BuildRequires:  pkgconfig(yaml-cpp)

%if %{with tests}
BuildRequires:  pkgconfig(gmock)
BuildRequires:  pkgconfig(gtest)
%endif

%if %{with python}
BuildRequires:  python3-devel
BuildRequires:  swig >= 4.2.0
%endif

%description
liblockfile is a library for parsing and creating RPM lockfiles.
It provides a native C++ API and Python bindings.

%files -n liblockfile
%{_libdir}/liblockfile.so

%package -n liblockfile-devel
Summary:        Development files for liblockfile
License:        LGPL-2.1-or-later
Requires:       liblockfile%{?_isa} = %{version}-%{release}

%description -n liblockfile-devel
Development files for liblockfile.

%files -n liblockfile-devel
%{_includedir}/liblockfile/
%{_libdir}/liblockfile.so
%{_libdir}/pkgconfig/liblockfile.pc

%if %{with python}
%package -n python3-liblockfile
%{?python_provide:%python_provide python3-liblockfile}
Summary:        Python 3 bindings for the liblockfile library
License:        LGPL-2.1-or-later
Requires:       liblockfile%{?_isa} = %{version}-%{release}

%description -n python3-liblockfile
Python 3 bindings for the liblockfile library.

%files -n python3-liblockfile
%pycached %{python3_sitearch}/liblockfile.py
%{python3_sitearch}/_liblockfile.so*
%{python3_sitearch}/liblockfile-*.dist-info
%endif

%prep
%autosetup -p1 -n liblockfile-%{version}

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

%install
%cmake_install

%changelog
%autochangelog