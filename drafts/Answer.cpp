#include "Answer.h"
#include "Exception.h"


namespace quest
{


Answer::Answer(std::int8_t number) : answers(number)
{
}


void Answer::set_answers(std::vector<std::int8_t>&& ans)
{
    if (answers.size() != ans.size())
    {
        throw quest::QuestException("Wrong given answers number");
    }

    answers = std::move(ans);
}


}
