%module libpkgmanifest
#pragma SWIG nowarn=362,509

// The following adds Python attribute shortcuts for getters and setters
// from C++ structures that act as plain data objects.
//
// E.g. object.get_value() -> object.value
//
%pythoncode %{
def create_attributes_from_getters_and_setters(cls):
    getter_prefix = 'get_'
    setter_prefix = 'set_'
    attrs = {method[len(getter_prefix):] for method in dir(cls) if method.startswith(getter_prefix) or method.startswith(setter_prefix)}
    for attr in attrs:
        getter_name = getter_prefix + attr
        setter_name = setter_prefix + attr
        setattr(cls, attr, property(
            lambda self, getter_name=getter_name: getattr(self, getter_name)() if getter_name in dir(cls) else None,
            lambda self, value, setter_name=setter_name: getattr(self, setter_name)(value) if setter_name in dir(cls) else None
        ))
%}

%include <exception.i>
%include <stdint.i>
%include <std_map.i>
%include <std_string.i>
%include <std_vector.i>

%exception {
    try {
        $action
    } catch (const std::runtime_error & e) {
        SWIG_exception(SWIG_RuntimeError, e.what());
    }
}

%ignore std::vector::vector(size_type);
%ignore std::vector::vector(unsigned int);
%ignore std::vector::resize;

%{
    #include "libpkgmanifest/checksum.hpp"
    #include "libpkgmanifest/manifest.hpp"
    #include "libpkgmanifest/package.hpp"
    #include "libpkgmanifest/packages.hpp"
    #include "libpkgmanifest/parser.hpp"
    #include "libpkgmanifest/serializer.hpp"
    #include "libpkgmanifest/version.hpp"
%}

%include "libpkgmanifest/checksum.hpp"
%include "libpkgmanifest/version.hpp"

%include "libpkgmanifest/package.hpp"
%template(VectorPackage) std::vector<libpkgmanifest::Package>;

%include "libpkgmanifest/packages.hpp"
%template(MapPackages) std::map<std::string, std::vector<libpkgmanifest::Package>>;

%include "libpkgmanifest/manifest.hpp"
%include "libpkgmanifest/parser.hpp"
%include "libpkgmanifest/serializer.hpp"

%pythoncode %{
create_attributes_from_getters_and_setters(Checksum)
create_attributes_from_getters_and_setters(Manifest)
create_attributes_from_getters_and_setters(Package)
create_attributes_from_getters_and_setters(Version)
%}

%extend libpkgmanifest::Packages {
    std::vector<libpkgmanifest::Package> __getitem__(const std::string & key) const {
        return self->get(key);
    }
}