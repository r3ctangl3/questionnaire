#include "Exception.h"


namespace quest 
{


QuestException::QuestException(const std::string& message) : std::runtime_error(message) 
{
}


const char* QuestException::what() const noexcept
{
    return std::runtime_error::what();
}


}
