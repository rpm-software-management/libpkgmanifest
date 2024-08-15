%module liblockfile

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

%include <std_map.i>
%include <std_string.i>
%include <std_vector.i>

%ignore std::vector::vector(size_type);
%ignore std::vector::vector(unsigned int);
%ignore std::vector::resize;

%{
    #include "liblockfile/checksum.hpp"
    #include "liblockfile/lockfile.hpp"
    #include "liblockfile/package.hpp"
    #include "liblockfile/packages.hpp"
    #include "liblockfile/parser.hpp"
    #include "liblockfile/serializer.hpp"
    #include "liblockfile/version.hpp"
%}

%include "liblockfile/checksum.hpp"
%include "liblockfile/version.hpp"

%include "liblockfile/package.hpp"
%template(VectorPackage) std::vector<liblockfile::Package>;

%include "liblockfile/packages.hpp"
%template(MapPackages) std::map<std::string, std::vector<liblockfile::Package>>;

%include "liblockfile/lockfile.hpp"
%include "liblockfile/parser.hpp"
%include "liblockfile/serializer.hpp"

%pythoncode %{
create_attributes_from_getters_and_setters(Checksum)
create_attributes_from_getters_and_setters(LockFile)
create_attributes_from_getters_and_setters(Package)
create_attributes_from_getters_and_setters(Version)
%}

%extend liblockfile::Packages {
    std::vector<liblockfile::Package> __getitem__(const std::string & key) const {
        return self->get(key);
    }
}