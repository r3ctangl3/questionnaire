#include "Answer.h"
#include "Exception.h"


namespace quest
{


Answer::Answer(int number) : answers(number)
{
}


void Answer::set_answers(std::vector<int>&& ans)
{
    if (answers.size() != ans.size())
    {
        throw quest::QuestException("Wrong given answers number");
    }

    answers = std::move(ans);
}


const std::vector<int>& Answer::get_answers() const
{
    return answers;
}


}
