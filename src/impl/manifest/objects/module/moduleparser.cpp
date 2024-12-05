#include "moduleparser.hpp"

namespace libpkgmanifest::internal::manifest {

using namespace libpkgmanifest::internal::common;

ModuleParser::ModuleParser(
    std::shared_ptr<IModuleFactory> module_factory,
    std::shared_ptr<IStringSplitter> string_splitter)
    : module_factory(module_factory) 
    , string_splitter(string_splitter) {}

std::unique_ptr<IModule> ModuleParser::parse(const IYamlNode & node) const {
    auto module = module_factory->create();
    auto module_string = node.as_string();

    auto module_parts = string_splitter->split(module_string, ':');
    auto & name = module_parts[0];
    auto & stream = module_parts[1];

    module->set_name(name);
    module->set_stream(stream);
    
    return module;
}

}