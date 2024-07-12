#include "SingleTest.h"


namespace quest
{


SingleTest::SingleTest(const quest::Methodology* methodology) 
    : questions(methodology->get_questions())
    , name(methodology->get_name())
{
    for (const auto& q : questions)
    {
        answers.push_back(quest::Answer(q.get_answers_number()));
    }
}


const std::string& SingleTest::get_name()
{
    return name;
}


SingleTest::Iterator SingleTest::begin()
{
    return SingleTest::Iterator(std::move(questions.begin()), std::move(answers.begin()));
}


SingleTest::Iterator::Iterator(Qiter&& q, Aiter&& a)
{
    qiter = q;
    aiter = a;
}


SingleTest::Iterator SingleTest::end()
{
    return SingleTest::Iterator(std::move(questions.end()), std::move(answers.end()));
}


bool SingleTest::Iterator::operator!=(const Iterator& other)
{
    return (this->qiter != other.qiter) && (this->aiter != other.aiter);
}


void SingleTest::Iterator::operator++ ()
{
    ++qiter;
    ++aiter;
}


const quest::Question& SingleTest::Iterator::get_current_question()
{
    return *qiter;
}


void SingleTest::Iterator::set_current_answer(std::vector<int>&& ans)
{
    aiter->set_answers(std::forward<std::vector<int>>(ans));
}


const std::vector<int>& SingleTest::Iterator::get_current_answer()
{
    return aiter->get_answers();
}


}
