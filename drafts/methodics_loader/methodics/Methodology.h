#pragma once


#include <iostream>     // TODO: remove


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
    const std::filesystem::path dir = "./tmp/";
    std::vector<quest::Question> questions;
    const std::string name;

public:
    Methodology() = delete;
    Methodology(const char* name);
    const std::vector<quest::Question>& get_questions() const;
    virtual void get_results() = 0;
    virtual ~Methodology();

// #ifdef DEBUG
// private:
//     virtual void check_questions() = 0;
// #endif
};


}
