#include "MethodicsLoader.h"


#include "Beka.h"
#include "Hanin.h"
#include "Mmpi.h"
#include "Scl.h"
#include "Tobol.h"
#include "Zung.h"


namespace quest
{


MethodicsLoader::MethodicsLoader()
{
    methodics["beka"]   = new quest::Beka();
    methodics["hanin"]  = new quest::Hanin();
    methodics["mmpi"]   = new quest::Mmpi();
    methodics["scl"]    = new quest::Scl();
    methodics["tobol"]  = new quest::Tobol();
    methodics["zung"]   = new quest::Zung();
}


std::vector<const quest::Methodology*> MethodicsLoader::get_methodics(const std::vector<std::string>& methodicsNames)
{
    std::vector<const quest::Methodology*> reqMethodics;
    for (const auto& name : methodicsNames) {
        reqMethodics.push_back(methodics[name]);    
    }

    return std::move(reqMethodics);
}


MethodicsLoader::~MethodicsLoader()
{
    for (auto& [name, meth] : methodics)
    {
        delete meth;
    }
}


}
