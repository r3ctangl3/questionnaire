#pragma once


#include <filesystem>
#include <string>
#include <vector>


#include "Question.h"


namespace quest
{


/// @brief Represents single methodology along with its questions
class Methodology
{
private:
    const char separator = '@';
    const std::filesystem::path filename = "Questions";
    std::vector<quest::Question> questions;

public:
    Methodology();
    const std::vector<quest::Question>& get_questions();
//     virtual void get_results() = 0;

// #ifdef DEBUG
// private:
//     virtual void check_questions() = 0;
// #endif
};


}
