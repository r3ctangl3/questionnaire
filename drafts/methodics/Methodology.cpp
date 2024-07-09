#include <fstream>


#include "Exception.h"
#include "Methodology.h"


namespace quest
{

    const std::string MethodologyName::BEKA     = "47a9bacc5051c49be189d7d051f2c755";
    const std::string MethodologyName::HANIN    = "3e241cb997b341abd86502442b0a8f60";
    const std::string MethodologyName::MMPI     = "e2f39eb45ac7ab873f751bde423fb5bb";
    const std::string MethodologyName::SCL      = "f32305c695d7dc05e9dccfadf8e5e01d";
    const std::string MethodologyName::TOBOL    = "98a61ef88202ffe2d5b0feccd273353c";
    const std::string MethodologyName::ZUNG     = "1761aba4dcb26fcfe1c80b3513a26ef6";


    Methodology::Methodology(const std::filesystem::path file)
    {
        std::string rawLine;
        std::filesystem::path filepath = dir / file;
        std::ifstream f(filepath);

        if (!f.is_open()) {
            throw quest::QuestException("Failed to open methodolody question file");
        }

        while (std::getline(f, rawLine)) {
            questions.push_back(quest::Question(rawLine, separator));
        }

        f.close();
    }


    const std::vector<quest::Question>& Methodology::get_questions()
    {
        return questions;
    }


    Methodology::~Methodology()
    {
    }
}
