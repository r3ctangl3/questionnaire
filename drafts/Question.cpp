#include <iostream>
#include <sstream>
#include <vector>


#include "Exception.h"
#include "Question.h"


namespace quest
{


Question::Question(const std::string& rawData, char separator)
{
    std::string token;
    std::stringstream ss(rawData);

    while (std::getline(ss, token, separator)) 
    {
        rawTokens.push_back(std::move(token));            
    }

// Question files are provided as a part of the product
// and therefore all the bugs in these files are perfectly
// fixed before release are done. Exceptions which have
// been thrown should not be catched in order to allow
// the programm to be immidiately and properly terminated.  
#ifdef DEBUG

    if (rawTokens.size() < 4)
    {
        throw quest::QuestException("Error tokens number in question: " + rawData);
    }

    try
    {
        answersNumber = static_cast<std::int8_t>(std::stoi(rawTokens[1]));
    }
    catch (const std::exception& e)
    {
        throw quest::QuestException("Error format of answers number: " + std::string(e.what()));        
    }

#endif // DEBUG

    text = std::move(rawTokens[0]);
    answersNumber = static_cast<std::int8_t>(std::stoi(rawTokens[1]));
    answers = std::span<const std::string> {rawTokens.begin() + 2, rawTokens.size() - 2};
}

const std::string& Question::get_text() const
{
    return text;
}

const std::int8_t Question::get_answers_number() const
{
    return answersNumber;
}

const std::span<const std::string> Question::get_answers() const
{
    return answers;
}


}
