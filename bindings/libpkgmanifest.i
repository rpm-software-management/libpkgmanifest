%module libpkgmanifest
#pragma SWIG nowarn=362,509

%pythoncode %{
def add_property_accessors(target_cls, src_cls=None, src_getter=None):
    """
    Dynamically creates attributes in the target class based on the getter and setter
    methods of a source class.

    This method inspects the source class for methods with 'get_' and 'set_' prefixes,
    and creates corresponding properties in the target class. If a `src_getter` is provided,
    it is used to obtain an instance of the source class, allowing for delegation of property
    access.

    Args:
        target_cls (type): The class where the properties will be added.
        src_cls (type, optional): The class to inspect for getter and setter methods.
                                  If not provided, the target class is used.
        src_getter (callable, optional): A callable that takes an instance of the target class
                                          and returns an instance of the source class.
                                          This is used for delegating property access.

    Example:
        1. Simplifying Access in the Package Class
        - Before: package.get_size()
        - After calling add_property_accessors(Package): package.size

        2. Delegating Access of Internal Objects
        - Before: package.get_nevra().get_name()
        - After calling add_property_accessors(Package, Nevra, Package.get_nevra): package.name
    """
    def create_getter(getter_name):
        def getter(self):
            getter_target = src_getter(self) if src_getter else self
            return getattr(getter_target, getter_name)() if getter_name in dir(getter_target) else None
        return getter

    def create_setter(setter_name):
        def setter(self, value):
            setter_target = src_getter(self) if src_getter else self
            return getattr(setter_target, setter_name)(value) if setter_name in dir(setter_target) else None
        return setter

    if not src_cls:
        src_cls = target_cls

    getter_prefix = 'get_'
    setter_prefix = 'set_'
    attrs = {method[len(getter_prefix):] for method in dir(src_cls) if method.startswith(getter_prefix) or method.startswith(setter_prefix)}
    for attr in attrs:
        getter_name = getter_prefix + attr
        setter_name = setter_prefix + attr
        setattr(target_cls, attr, property(
            create_getter(getter_name),
            create_setter(setter_name)
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
    #include "libpkgmanifest/module.hpp"
    #include "libpkgmanifest/nevra.hpp"
    #include "libpkgmanifest/package.hpp"
    #include "libpkgmanifest/packages.hpp"
    #include "libpkgmanifest/parser.hpp"
    #include "libpkgmanifest/repository.hpp"
    #include "libpkgmanifest/repositories.hpp"
    #include "libpkgmanifest/serializer.hpp"
    #include "libpkgmanifest/version.hpp"
%}

%include "libpkgmanifest/checksum.hpp"
%include "libpkgmanifest/module.hpp"
%include "libpkgmanifest/nevra.hpp"
%include "libpkgmanifest/version.hpp"

%include "libpkgmanifest/repository.hpp"
%include "libpkgmanifest/repositories.hpp"
%template(MapRepositories) std::map<std::string, libpkgmanifest::Repository>;

%include "libpkgmanifest/package.hpp"
%template(VectorPackage) std::vector<libpkgmanifest::Package>;

%include "libpkgmanifest/packages.hpp"
%template(MapPackages) std::map<std::string, std::vector<libpkgmanifest::Package>>;

%include "libpkgmanifest/manifest.hpp"
%include "libpkgmanifest/parser.hpp"
%include "libpkgmanifest/serializer.hpp"

%pythoncode %{
add_property_accessors(Checksum)
add_property_accessors(Manifest)
add_property_accessors(Module)
add_property_accessors(Nevra)
add_property_accessors(Package)
add_property_accessors(Repository)
add_property_accessors(Version)
add_property_accessors(Package, Nevra, Package.get_nevra)
%}

// Allow nevra to be convertible to string
%extend libpkgmanifest::Nevra {
    std::string __str__() {
        return self->to_string();
    }
}

// Make Packages to act like a dictionary
%extend libpkgmanifest::Packages {
    std::vector<libpkgmanifest::Package> __getitem__(const std::string & key) const {
        return self->get(key);
    }
}

// Make Repositories to act like a dictionary
%extend libpkgmanifest::Repositories {
    libpkgmanifest::Repository __getitem__(const std::string & id) const {
        return self->get(id);
    }
}