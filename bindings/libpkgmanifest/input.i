%module input
#pragma SWIG nowarn=362,509

%include "common.i"

%{
    #include "libpkgmanifest/input/input.hpp"
    #include "libpkgmanifest/input/parser.hpp"
%}

%include "libpkgmanifest/input/input.hpp"
%include "libpkgmanifest/input/parser.hpp"

%pythoncode %{
add_property_accessors(Input)
%}
