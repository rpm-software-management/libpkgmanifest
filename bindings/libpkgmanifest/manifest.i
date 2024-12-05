%module manifest
#pragma SWIG nowarn=362,509

%include "common.i"

%{
    #include "libpkgmanifest/manifest/checksum.hpp"
    #include "libpkgmanifest/manifest/manifest.hpp"
    #include "libpkgmanifest/manifest/module.hpp"
    #include "libpkgmanifest/manifest/nevra.hpp"
    #include "libpkgmanifest/manifest/package.hpp"
    #include "libpkgmanifest/manifest/packages.hpp"
    #include "libpkgmanifest/manifest/parser.hpp"
    #include "libpkgmanifest/manifest/serializer.hpp"
%}

%include "libpkgmanifest/manifest/checksum.hpp"
%include "libpkgmanifest/manifest/module.hpp"
%include "libpkgmanifest/manifest/nevra.hpp"

%include "libpkgmanifest/manifest/package.hpp"
%template(VectorPackage) std::vector<libpkgmanifest::manifest::Package>;

%include "libpkgmanifest/manifest/packages.hpp"
%template(MapPackages) std::map<std::string, std::vector<libpkgmanifest::manifest::Package>>;

%include "libpkgmanifest/manifest/manifest.hpp"

%include "libpkgmanifest/manifest/parser.hpp"
%include "libpkgmanifest/manifest/serializer.hpp"

%pythoncode %{
add_property_accessors(Checksum)
add_property_accessors(Manifest)
add_property_accessors(Module)
add_property_accessors(Nevra)
add_property_accessors(Package)
add_property_accessors(Package, Nevra, Package.get_nevra)
%}

// Allow Nevra to be convertible to string
%extend libpkgmanifest::manifest::Nevra {
    std::string __str__() {
        return self->to_string();
    }
}

// Adjust Packages for a more convenient Python API
%extend libpkgmanifest::manifest::Packages {
    std::vector<libpkgmanifest::manifest::Package> __getitem__(const std::string & key) const {
        return self->get(key);
    }

    std::vector<libpkgmanifest::manifest::Package> values() {
        return self->get();
    }
}
