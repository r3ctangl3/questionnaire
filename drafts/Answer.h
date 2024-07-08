#pragma once


#include <cstdint>
#include <vector>


namespace quest
{


class Answer
{
private:
    std::vector<std::int8_t> answers;

public:
    Answer() = delete;
    Answer(std::int8_t number);
    void set_answers(std::vector<std::int8_t>&& ans);
};


}
