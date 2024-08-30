#include <fstream>
#include <map>


#include "Exception.h"
#include "Methodology.h"


namespace
{
    
    
    std::map<const std::string, const std::string> methodics_names_hashes =
    {
        {"beka"  , "47a9bacc5051c49be189d7d051f2c755"},
        {"hanin" , "3e241cb997b341abd86502442b0a8f60"},
        {"mmpi"  , "e2f39eb45ac7ab873f751bde423fb5bb"},
        {"scl"   , "f32305c695d7dc05e9dccfadf8e5e01d"},
        {"tobol" , "98a61ef88202ffe2d5b0feccd273353c"},
        {"zung"  , "1761aba4dcb26fcfe1c80b3513a26ef6"}
    };


    const std::string& get_methodology_filename(const std::string& name)
    {
        return methodics_names_hashes[name];
    }


}


namespace quest
{


    Methodology::Methodology(const char* name) : name(name)
    {
        std::string rawLine;
        std::filesystem::path filepath = dir / get_methodology_filename(name);
        std::ifstream f(filepath);

        if (!f.is_open()) {
            throw quest::QuestException("Failed to open methodolody question file");
        }

        while (std::getline(f, rawLine)) {
            questions.push_back(quest::Question(rawLine, separator));
        }

        f.close();
    }


    const std::string& Methodology::get_name() const
    {
        return name;
    }


    const std::vector<quest::Question>& Methodology::get_questions() const
    {
        return questions;
    }


    Methodology::~Methodology()
    {
    }

    
}
