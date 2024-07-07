#pragma once


#include <stdexcept>
#include <string>


namespace quest
{


class QuestException : public std::runtime_error 
{
public:
    QuestException() = delete;
    QuestException(const std::string& message);
    const char* what() const noexcept override;
};


}
