%global pkg_name libpkgmanifest

%global forgeurl https://github.com/rpm-software-management/%{pkg_name}

%global version_major 0
%global version_minor 5
%global version_patch 8

Name:       %{pkg_name}
Version:    %{version_major}.%{version_minor}.%{version_patch}
Release:    %{autorelease}

%forgemeta

Summary:    Library for working with RPM manifests
License:    LGPL-2.1-or-later
URL:        %{forgeurl}
Source:     %{forgesource}

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
%{name} is a library for parsing and creating RPM manifests.
It provides a native C++ API and Python bindings.

%files -n %{name}
%{_libdir}/%{name}.so.0
%license LICENSE

%package -n %{name}-devel
Summary:        Development files for %{name}
License:        LGPL-2.1-or-later
Requires:       %{name}%{?_isa} = %{version}-%{release}

%description -n %{name}-devel
Development files for %{name}.

%files -n %{name}-devel
%{_includedir}/%{name}/
%{_libdir}/%{name}.so
%{_libdir}/pkgconfig/%{name}.pc
%license LICENSE

%if %{with python}
%package -n python3-%{name}
%{?python_provide:%python_provide python3-%{name}}
Summary:        Python 3 bindings for the %{name} library
License:        LGPL-2.1-or-later
Requires:       %{name}%{?_isa} = %{version}-%{release}

%description -n python3-%{name}
Python 3 bindings for the %{name} library.

%files -n python3-%{name}
%{python3_sitearch}/%{name}
%{python3_sitearch}/%{name}-*.dist-info
%license LICENSE
%endif

%prep
%autosetup -p1 -n %{name}-%{version}

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