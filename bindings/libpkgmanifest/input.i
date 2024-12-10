%module input
#pragma SWIG nowarn=362,509

%include "common.i"

%{
    #include "libpkgmanifest/input/input.hpp"
    #include "libpkgmanifest/input/modules.hpp"
    #include "libpkgmanifest/input/options.hpp"
    #include "libpkgmanifest/input/packages.hpp"
    #include "libpkgmanifest/input/parser.hpp"
%}

%include "libpkgmanifest/input/packages.hpp"
%include "libpkgmanifest/input/modules.hpp"
%include "libpkgmanifest/input/options.hpp"

%include "libpkgmanifest/input/input.hpp"
%include "libpkgmanifest/input/parser.hpp"

%pythoncode %{
add_property_accessors(Input)
add_property_accessors(Modules)
add_property_accessors(Options)
add_property_accessors(Packages)
%}
