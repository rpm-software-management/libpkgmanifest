#pragma once

#include "imodulefactory.hpp"
#include "imoduleparser.hpp"

#include "libpkgmanifest/tools/istringsplitter.hpp"

namespace libpkgmanifest::internal {

class ModuleParser : public IModuleParser {
public:
    ModuleParser(std::shared_ptr<IModuleFactory> module_factory, std::shared_ptr<IStringSplitter> string_splitter);

    virtual std::unique_ptr<IModule> parse(const IYamlNode & node) const override;

private:
    std::shared_ptr<IModuleFactory> module_factory;
    std::shared_ptr<IStringSplitter> string_splitter;
};

}