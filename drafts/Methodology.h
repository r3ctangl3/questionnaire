#pragma once


#include <filesystem>
#include <string>
#include <vector>


#include "Question.h"


namespace quest
{


class Methodology
{
private:
    const char separator = '@';
    const std::filesystem::path filename = "Questions";
    std::vector<quest::Question> questions;

public:
    Methodology();
    const std::vector<quest::Question>& get_questions();
};


}
