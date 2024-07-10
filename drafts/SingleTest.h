#pragma once


#include <vector>


#include "Answer.h"
#include "Question.h"
#include "Methodology.h"


namespace quest 
{


/// @brief Owns test answers for a single methodology
class SingleTest
{
private:
    const std::vector<quest::Question>& questions;
    std::vector<quest::Answer> answers;

public:
    SingleTest() = delete;
    SingleTest(const quest::Methodology* methodology);

private:
    using Qiter = std::vector<quest::Question>::const_iterator;
    using Aiter = std::vector<quest::Answer>::iterator; 

    class Iterator
    {
    private:
        Qiter qiter;
        Aiter aiter;

    public:
        Iterator(Qiter&& q, Aiter&& a);
        void operator++();
        bool operator!=(const Iterator& other);
        const quest::Question& get_current_question();
        void set_current_answer(std::vector<int>&& ans);
        const std::vector<int>& get_current_answer();        // TODO: remove, just for debug
    };

public:
    Iterator begin();
    Iterator end();
};


}
