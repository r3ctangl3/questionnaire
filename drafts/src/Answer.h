#pragma once


#include <vector>


namespace quest
{


class Answer
{
private:
    std::vector<int> answers;

public:
    Answer() = delete;
    Answer(int number);
    void set_answers(std::vector<int>&& ans);
    const std::vector<int>& get_answers() const;
};


}
