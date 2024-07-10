#pragma once


#include <iostream>     // TODO: remove


#include <filesystem>
#include <string>
#include <vector>


#include "Question.h"


namespace quest
{


/// @brief Constants to be used in Methodology abstract class implementations
struct MethodicsNameHash
{
    static const std::string BEKA   ;
    static const std::string HANIN  ;
    static const std::string MMPI   ;
    static const std::string SCL    ;
    static const std::string TOBOL  ;
    static const std::string ZUNG   ;
};


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
    Methodology(const char* name, const std::filesystem::path file);
    const std::vector<quest::Question>& get_questions();
    virtual void get_results() = 0;
    virtual ~Methodology();

// #ifdef DEBUG
// private:
//     virtual void check_questions() = 0;
// #endif
};


}
