#pragma once

#include "imodulefactory.hpp"
#include "imoduleparser.hpp"

#include "impl/common/tools/stringsplitter/istringsplitter.hpp"

namespace libpkgmanifest::internal::manifest {

using namespace libpkgmanifest::internal::common;

class ModuleParser : public IModuleParser {
public:
    ModuleParser(std::shared_ptr<IModuleFactory> module_factory, std::shared_ptr<IStringSplitter> string_splitter);

    virtual std::unique_ptr<IModule> parse(const IYamlNode & node) const override;

private:
    std::shared_ptr<IModuleFactory> module_factory;
    std::shared_ptr<IStringSplitter> string_splitter;
};

}