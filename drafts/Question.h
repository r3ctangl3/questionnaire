#pragma once


#include <span>
#include <string>


namespace quest
{


/// @brief Represents single question along with its answers 
class Question
{
private:
    std::vector<std::string> rawTokens;
    std::string text;
    int answersNumber;
    std::span<const std::string> answers;

public:
    Question() = delete;
    Question(const std::string& rawData, char separator);

public:
    const std::string& get_text() const;
    const int get_answers_number() const;
    const std::span<const std::string> get_answers() const;
};


}
