#include <fstream>


#include "Exception.h"
#include "Methodology.h"


namespace quest
{


    Methodology::Methodology()
    {
        std::string rawLine;
        std::ifstream file(filename);

        if (!file.is_open()) 
        {
            throw quest::QuestException("Failed to open methodolody question file");
        }

        while (std::getline(file, rawLine)) 
        {
            questions.push_back(quest::Question(rawLine, separator));
        }

        file.close();
    }


    const std::vector<quest::Question>& Methodology::get_questions()
    {
        return questions;
    }


}
